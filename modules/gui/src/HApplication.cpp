#include "HApplication.h"
#include "private/HApplication_p.h"
#include "HWindow.h"
#include "private/HWindow_p.h"
#include "HPoint.h"
#include "HMouseArea.h"
#include "HKeyboard.h"

extern "C" {
#include <wayland-client.h>
#include "xdg-shell-client-protocol.h"
#include "cursor-shape-v1-client-protocol.h"
}

#include <cstring>
#include <stdexcept>
#include <iostream>

namespace Ht {

// Static instance
HApplication* HApplication::s_instance = nullptr;

namespace {

// Hit-test regions for resize vs move, in surface-local coordinates.
enum class PointerHit {
    None,
    MoveArea,
    ResizeTop,
    ResizeBottom,
    ResizeLeft,
    ResizeRight,
    ResizeTopLeft,
    ResizeTopRight,
    ResizeBottomLeft,
    ResizeBottomRight,
};

static PointerHit hit_test(HWindow::Impl* win, double x, double y) {
    if (!win) {
        return PointerHit::None;
    }

    HPoint point(static_cast<int>(x), static_cast<int>(y));

    // If draggable regions are defined, check them FIRST (they take priority over edges)
    if (!win->draggableRegions.empty()) {
        for (const auto& region : win->draggableRegions) {
            if (region.contains(point)) {
                return PointerHit::MoveArea;
            }
        }
        // Not in a draggable region, now check edges for resize
        const int edge = 24;
        bool left = x < edge;
        bool right = x >= (win->width - edge);
        bool top = y < edge;
        bool bottom = y >= (win->height - edge);

        if (left && top) return PointerHit::ResizeTopLeft;
        if (right && top) return PointerHit::ResizeTopRight;
        if (left && bottom) return PointerHit::ResizeBottomLeft;
        if (right && bottom) return PointerHit::ResizeBottomRight;
        if (top) return PointerHit::ResizeTop;
        if (bottom) return PointerHit::ResizeBottom;
        if (left) return PointerHit::ResizeLeft;
        if (right) return PointerHit::ResizeRight;

        // Not in draggable region and not on edge
        return PointerHit::None;
    }

    // Legacy behavior: no draggable regions set
    // Check edges first, then treat rest as draggable
    const int edge = 24;
    bool left = x < edge;
    bool right = x >= (win->width - edge);
    bool top = y < edge;
    bool bottom = y >= (win->height - edge);

    if (left && top) return PointerHit::ResizeTopLeft;
    if (right && top) return PointerHit::ResizeTopRight;
    if (left && bottom) return PointerHit::ResizeBottomLeft;
    if (right && bottom) return PointerHit::ResizeBottomRight;
    if (top) return PointerHit::ResizeTop;
    if (bottom) return PointerHit::ResizeBottom;
    if (left) return PointerHit::ResizeLeft;
    if (right) return PointerHit::ResizeRight;

    // Entire window is draggable (legacy)
    return PointerHit::MoveArea;
}

static uint32_t to_xdg_edge(PointerHit hit) {
    switch (hit) {
        case PointerHit::ResizeTop: return XDG_TOPLEVEL_RESIZE_EDGE_TOP;
        case PointerHit::ResizeBottom: return XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM;
        case PointerHit::ResizeLeft: return XDG_TOPLEVEL_RESIZE_EDGE_LEFT;
        case PointerHit::ResizeRight: return XDG_TOPLEVEL_RESIZE_EDGE_RIGHT;
        case PointerHit::ResizeTopLeft: return XDG_TOPLEVEL_RESIZE_EDGE_TOP_LEFT;
        case PointerHit::ResizeTopRight: return XDG_TOPLEVEL_RESIZE_EDGE_TOP_RIGHT;
        case PointerHit::ResizeBottomLeft: return XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_LEFT;
        case PointerHit::ResizeBottomRight: return XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_RIGHT;
        default: return XDG_TOPLEVEL_RESIZE_EDGE_NONE;
    }
}

// Forward declaration for cursor shape helper.
static void set_cursor_shape_for_hit(HApplication::Impl* impl, PointerHit hit);

// Minimal pointer listener: used to start interactive move/resize.
static void pointer_handle_enter(void* data,
                                 wl_pointer* pointer,
                                 uint32_t serial,
                                 wl_surface* surface,
                                 wl_fixed_t sx,
                                 wl_fixed_t sy) {
    auto* impl = static_cast<HApplication::Impl*>(data);
    if (!impl) {
        return;
    }
    (void)pointer;
    impl->pointerX = wl_fixed_to_double(sx);
    impl->pointerY = wl_fixed_to_double(sy);
    impl->pointerEnterSerial = serial;

    // Update cursor shape when entering our primary window.
    if (impl->primaryWindow && surface) {
        auto* winImpl = impl->primaryWindow->impl();
        PointerHit hit = hit_test(winImpl, impl->pointerX, impl->pointerY);
        set_cursor_shape_for_hit(impl, hit);

        // Route initial hover event to HMouseArea if there's a central item
        if (winImpl->centralItem) {
            HMouseArea* hoveredArea = HWindow::findMouseAreaAt(
                winImpl->centralItem,
                static_cast<int>(impl->pointerX),
                static_cast<int>(impl->pointerY)
            );

            if (hoveredArea) {
                hoveredArea->handleHover(true);
                impl->currentHoveredArea = hoveredArea;
            }
        }
    }
}

static void pointer_handle_leave(void* data,
                                 wl_pointer* /*pointer*/,
                                 uint32_t /*serial*/,
                                 wl_surface* /*surface*/) {
    auto* impl = static_cast<HApplication::Impl*>(data);
    if (!impl) {
        return;
    }

    // Clear hover state when pointer leaves window
    HMouseArea* hoveredArea = static_cast<HMouseArea*>(impl->currentHoveredArea);
    if (hoveredArea) {
        hoveredArea->handleHover(false);
        impl->currentHoveredArea = nullptr;
    }
}

static void pointer_handle_motion(void* data,
                                  wl_pointer* /*pointer*/,
                                  uint32_t /*time*/,
                                  wl_fixed_t sx,
                                  wl_fixed_t sy) {
    auto* impl = static_cast<HApplication::Impl*>(data);
    if (!impl) {
        return;
    }
    impl->pointerX = wl_fixed_to_double(sx);
    impl->pointerY = wl_fixed_to_double(sy);

    if (impl->primaryWindow) {
        auto* winImpl = impl->primaryWindow->impl();

        // Update cursor shape for window drag/resize
        PointerHit hit = hit_test(winImpl, impl->pointerX, impl->pointerY);
        set_cursor_shape_for_hit(impl, hit);

        // Route hover events to HMouseArea if there's a central item
        if (winImpl->centralItem) {
            HMouseArea* newHoveredArea = HWindow::findMouseAreaAt(
                winImpl->centralItem,
                static_cast<int>(impl->pointerX),
                static_cast<int>(impl->pointerY)
            );

            HMouseArea* oldHoveredArea = static_cast<HMouseArea*>(impl->currentHoveredArea);

            // Handle hover exit
            if (oldHoveredArea && oldHoveredArea != newHoveredArea) {
                oldHoveredArea->handleHover(false);
            }

            // Handle hover enter
            if (newHoveredArea && newHoveredArea != oldHoveredArea) {
                newHoveredArea->handleHover(true);
            }

            impl->currentHoveredArea = newHoveredArea;
        }
    }
}

static void pointer_handle_button(void* data,
                                  wl_pointer* /*pointer*/,
                                  uint32_t serial,
                                  uint32_t /*time*/,
                                  uint32_t button,
                                  uint32_t state) {
    auto* impl = static_cast<HApplication::Impl*>(data);
    if (!impl || !impl->seat || !impl->primaryWindow) {
        return;
    }

    constexpr uint32_t BTN_LEFT = 0x110; // linux/input-event-codes.h
    if (button != BTN_LEFT) {
        return;
    }

    auto* winImpl = impl->primaryWindow->impl();
    if (!winImpl || !winImpl->xdgToplevel) {
        return;
    }

    const int x = static_cast<int>(impl->pointerX);
    const int y = static_cast<int>(impl->pointerY);
    
    std::cout << "Click at " << x << "," << y << std::endl;

    // First, try to route the event to a HMouseArea if there's a central item
    bool eventHandledByMouseArea = false;
    if (winImpl->centralItem) {
        HMouseArea* mouseArea = HWindow::findMouseAreaAt(winImpl->centralItem, x, y);
        if (mouseArea) {
            std::cout << "Found MouseArea!" << std::endl;
            if (state == WL_POINTER_BUTTON_STATE_PRESSED) {
                mouseArea->handlePress(x, y);
            } else {
                mouseArea->handleRelease(x, y);
            }
            eventHandledByMouseArea = true;
        } else {
             std::cout << "No MouseArea found at " << x << "," << y << std::endl;
        }
    }

    // If not handled by a mouse area and it's a press, handle window drag/resize
    if (!eventHandledByMouseArea && state == WL_POINTER_BUTTON_STATE_PRESSED) {
        PointerHit hit = hit_test(winImpl, impl->pointerX, impl->pointerY);
        if (hit == PointerHit::MoveArea) {
            xdg_toplevel_move(winImpl->xdgToplevel, impl->seat, serial);
        } else if (hit != PointerHit::None) {
            uint32_t edge = to_xdg_edge(hit);
            if (edge != XDG_TOPLEVEL_RESIZE_EDGE_NONE) {
                xdg_toplevel_resize(winImpl->xdgToplevel, impl->seat, serial, edge);
            }
        }
    }
}

static void pointer_handle_axis(void* /*data*/,
                                wl_pointer* /*pointer*/,
                                uint32_t /*time*/,
                                uint32_t /*axis*/,
                                wl_fixed_t /*value*/) {
    // Scroll not handled yet.
}

static void pointer_handle_frame(void* /*data*/,
                                 wl_pointer* /*pointer*/) {
    // Grouping of pointer events; not used yet.
}

static void pointer_handle_axis_source(void* /*data*/,
                                       wl_pointer* /*pointer*/,
                                       uint32_t /*axis_source*/) {
}

static void pointer_handle_axis_stop(void* /*data*/,
                                     wl_pointer* /*pointer*/,
                                     uint32_t /*time*/,
                                     uint32_t /*axis*/) {
}

static void pointer_handle_axis_discrete(void* /*data*/,
                                         wl_pointer* /*pointer*/,
                                         uint32_t /*axis*/,
                                         int32_t /*discrete*/) {
}

// Map pointer hit to cursor-shape-v1 shape value.
static uint32_t shape_for_hit(PointerHit hit) {
    switch (hit) {
        case PointerHit::ResizeLeft:
            return WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_W_RESIZE;
        case PointerHit::ResizeRight:
            return WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_E_RESIZE;
        case PointerHit::ResizeTop:
            return WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_N_RESIZE;
        case PointerHit::ResizeBottom:
            return WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_S_RESIZE;
        case PointerHit::ResizeTopLeft:
            return WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NWSE_RESIZE;
        case PointerHit::ResizeBottomRight:
            return WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NWSE_RESIZE;
        case PointerHit::ResizeTopRight:
            return WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NESW_RESIZE;
        case PointerHit::ResizeBottomLeft:
            return WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_NESW_RESIZE;
        case PointerHit::MoveArea:
        case PointerHit::None:
        default:
            return WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
    }
}

static void set_cursor_shape_for_hit(HApplication::Impl* impl, PointerHit hit) {
    if (!impl || !impl->cursorShapeDevice || impl->pointerEnterSerial == 0) {
        return;
    }

    uint32_t shape = shape_for_hit(hit);
    wp_cursor_shape_device_v1_set_shape(impl->cursorShapeDevice,
                                        impl->pointerEnterSerial,
                                        shape);
}

static const wl_pointer_listener pointer_listener = {
    .enter = pointer_handle_enter,
    .leave = pointer_handle_leave,
    .motion = pointer_handle_motion,
    .button = pointer_handle_button,
    .axis = pointer_handle_axis,
    .frame = pointer_handle_frame,
    .axis_source = pointer_handle_axis_source,
    .axis_stop = pointer_handle_axis_stop,
    .axis_discrete = pointer_handle_axis_discrete,
};

static void seat_handle_capabilities(void* data, wl_seat* seat, uint32_t caps) {
    auto* impl = static_cast<HApplication::Impl*>(data);
    if (!impl) return;

    std::cout << "HApplication: Seat capabilities changed: " << caps << std::endl;

    // Pointer
    if ((caps & WL_SEAT_CAPABILITY_POINTER) && !impl->pointer) {
        std::cout << "HApplication: Initializing pointer" << std::endl;
        impl->pointer = wl_seat_get_pointer(seat);
        wl_pointer_add_listener(impl->pointer, &pointer_listener, impl);

        if (impl->cursorShapeManager && !impl->cursorShapeDevice) {
            impl->cursorShapeDevice =
                wp_cursor_shape_manager_v1_get_pointer(impl->cursorShapeManager,
                                                       impl->pointer);
        }
    } else if (!(caps & WL_SEAT_CAPABILITY_POINTER) && impl->pointer) {
        if (impl->cursorShapeDevice) {
            wp_cursor_shape_device_v1_destroy(impl->cursorShapeDevice);
            impl->cursorShapeDevice = nullptr;
        }
        wl_pointer_destroy(impl->pointer);
        impl->pointer = nullptr;
    }

    // Keyboard
    if ((caps & WL_SEAT_CAPABILITY_KEYBOARD)) {
        if (impl->keyboard) {
            std::cout << "HApplication: Initializing keyboard seat" << std::endl;
            impl->keyboard->setSeat(seat);
        }
    } else {
        std::cout << "HApplication: Keyboard capability lost or missing" << std::endl;
        // Keyboard lost - handled by HKeyboard internally or we can notify it
        if (impl->keyboard) {
            impl->keyboard->setSeat(nullptr);
        }
    }
}

static void seat_handle_name(void* /*data*/, wl_seat* /*seat*/, const char* /*name*/) {
}

static const wl_seat_listener seat_listener = {
    .capabilities = seat_handle_capabilities,
    .name = seat_handle_name,
};

} // namespace

// Registry listener callbacks
static void registry_handle_global(void* data, wl_registry* registry,
                                   uint32_t name, const char* interface, uint32_t version) {
    auto* impl = static_cast<HApplication::Impl*>(data);

    if (std::strcmp(interface, wl_compositor_interface.name) == 0) {
        impl->compositor = static_cast<wl_compositor*>(
            wl_registry_bind(registry, name, &wl_compositor_interface,
                           version < 4 ? version : 4));
    } else if (std::strcmp(interface, wl_shm_interface.name) == 0) {
        impl->shm = static_cast<wl_shm*>(
            wl_registry_bind(registry, name, &wl_shm_interface,
                           version < 1 ? version : 1));
    } else if (std::strcmp(interface, wl_seat_interface.name) == 0) {
        impl->seat = static_cast<wl_seat*>(
            wl_registry_bind(registry, name, &wl_seat_interface,
                           version < 5 ? version : 5));
        if (impl->seat) {
            wl_seat_add_listener(impl->seat, &seat_listener, impl);
        }
    } else if (std::strcmp(interface, xdg_wm_base_interface.name) == 0) {
        impl->xdgWmBase = static_cast<xdg_wm_base*>(
            wl_registry_bind(registry, name, &xdg_wm_base_interface,
                             version < 3 ? version : 3));
    } else if (std::strcmp(interface, wp_cursor_shape_manager_v1_interface.name) == 0) {
        impl->cursorShapeManager = static_cast<wp_cursor_shape_manager_v1*>(
            wl_registry_bind(registry, name, &wp_cursor_shape_manager_v1_interface,
                             version < 2 ? version : 2));
        if (impl->cursorShapeManager && impl->pointer && !impl->cursorShapeDevice) {
            impl->cursorShapeDevice =
                wp_cursor_shape_manager_v1_get_pointer(impl->cursorShapeManager,
                                                       impl->pointer);
        }
    }
}

static void registry_handle_global_remove(void* /*data*/, wl_registry* /*registry*/,
                                          uint32_t /*name*/) {
    // Handle global removal
}

static const wl_registry_listener registry_listener = {
    .global = registry_handle_global,
    .global_remove = registry_handle_global_remove,
};

// Impl implementation
HApplication::Impl::Impl(int& argc, char** argv)
    : argcPtr(&argc), argv(argv) {}

HApplication::Impl::~Impl() {
    cleanup();
}

bool HApplication::Impl::initialize() {
    // Connect to Wayland display
    display = wl_display_connect(nullptr);
    if (!display) {
        return false;
    }

    setupRegistry();
    return true;
}

void HApplication::Impl::setupRegistry() {
    if (!display) {
        return;
    }

    registry = wl_display_get_registry(display);
    if (!registry) {
        return;
    }

    wl_registry_add_listener(registry, &registry_listener, this);

    // Roundtrip to get all globals
    wl_display_roundtrip(display);
}

void HApplication::Impl::cleanup() {
    if (pointer) {
        wl_pointer_destroy(pointer);
        pointer = nullptr;
    }
    if (cursorShapeDevice) {
        wp_cursor_shape_device_v1_destroy(cursorShapeDevice);
        cursorShapeDevice = nullptr;
    }
    if (cursorShapeManager) {
        wp_cursor_shape_manager_v1_destroy(cursorShapeManager);
        cursorShapeManager = nullptr;
    }
    if (xdgWmBase) {
        xdg_wm_base_destroy(xdgWmBase);
        xdgWmBase = nullptr;
    }
    if (seat) {
        wl_seat_destroy(seat);
        seat = nullptr;
    }
    if (shm) {
        wl_shm_destroy(shm);
        shm = nullptr;
    }
    if (compositor) {
        wl_compositor_destroy(compositor);
        compositor = nullptr;
    }
    if (registry) {
        wl_registry_destroy(registry);
        registry = nullptr;
    }
    if (display) {
        wl_display_disconnect(display);
        display = nullptr;
    }
}

int HApplication::Impl::runEventLoop() {
    running = true;

    while (running && display) {
        // Dispatch pending events
        if (wl_display_dispatch(display) == -1) {
            // Connection lost or error
            break;
        }
    }

    return exitCode;
}

// HApplication implementation
HApplication::HApplication(int& argc, char** argv)
    : m_impl(std::make_unique<Impl>(argc, argv)) {

    if (s_instance) {
        throw std::runtime_error("Only one HApplication instance allowed");
    }

    m_impl->q_ptr = this; // Initialize back pointer
    m_impl->keyboard = std::make_unique<HKeyboard>(this);

    if (!m_impl->initialize()) {
        throw std::runtime_error("Failed to connect to Wayland display");
    }

    s_instance = this;
}

HApplication::~HApplication() {
    if (s_instance == this) {
        s_instance = nullptr;
    }
}

HApplication::HApplication(HApplication&&) noexcept = default;
HApplication& HApplication::operator=(HApplication&&) noexcept = default;

HApplication* HApplication::instance() {
    return s_instance;
}

HKeyboard* HApplication::keyboard() const {
    return m_impl->keyboard.get();
}

int HApplication::exec() {
    return m_impl->runEventLoop();
}

void HApplication::quit() {
    exit(0);
}

void HApplication::exit(int returnCode) {
    m_impl->running = false;
    m_impl->exitCode = returnCode;
}

const std::string& HApplication::applicationName() const {
    return m_impl->appName;
}

void HApplication::setApplicationName(const std::string& name) {
    m_impl->appName = name;
}

const std::string& HApplication::organizationName() const {
    return m_impl->orgName;
}

void HApplication::setOrganizationName(const std::string& name) {
    m_impl->orgName = name;
}

const std::string& HApplication::organizationDomain() const {
    return m_impl->orgDomain;
}

void HApplication::setOrganizationDomain(const std::string& domain) {
    m_impl->orgDomain = domain;
}

const std::string& HApplication::applicationVersion() const {
    return m_impl->appVersion;
}

void HApplication::setApplicationVersion(const std::string& version) {
    m_impl->appVersion = version;
}

void HApplication::processEvents() {
    if (m_impl->display) {
        wl_display_dispatch_pending(m_impl->display);
        wl_display_flush(m_impl->display);
    }
}

bool HApplication::isConnected() const {
    return m_impl->display != nullptr;
}

const char* HApplication::displayName() const {
    if (!m_impl->display) {
        return nullptr;
    }
    // Get the socket name from environment or default
    const char* waylandDisplay = getenv("WAYLAND_DISPLAY");
    return waylandDisplay ? waylandDisplay : "wayland-0";
}

} // namespace Ht