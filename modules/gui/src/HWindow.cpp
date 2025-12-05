#include "HWindow.h"
#include "private/HWindow_p.h"
#include "HShmBuffer.h"
#include "HInput.h"
#include "HApplication.h"
#include "private/HApplication_p.h"

#include <yoga/Yoga.h>

// graphics2d (HPainter, HImage)
#include "HImage.h"
#include "HPainter.h"
#include "HRectF.h"
#include "HPen.h"
#include "HColor.h"
#include "HRect.h"

// Primitives
#include "HItem.h"
#include "private/HItem_p.h"
#include "HLayout.h"
#include "HMouseArea.h"
#include "HPoint.h"

extern "C" {
#include <wayland-client.h>
#include "xdg-shell-client-protocol.h"
}

#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>

namespace Ht {

namespace {

// Forward declaration of internal helper.
struct RenderContext;


static void xdg_surface_handle_configure(void* data, xdg_surface* surface, uint32_t serial) {
    auto* impl = static_cast<HWindow::Impl*>(data);
    if (!impl || !surface) {
        return;
    }
    // Acknowledge configure; size handling will be added later when needed.
    xdg_surface_ack_configure(surface, serial);
}

static const xdg_surface_listener xdg_surface_listener = {
    .configure = xdg_surface_handle_configure,
};

// Helper to calculate margins reserved for shadows/effects
static void get_shadow_margins(HWindow::Impl* impl, int& left, int& top, int& right, int& bottom) {
    left = top = right = bottom = 0;
    if (impl->dropShadowEnabled) {
        const float blurMargin = impl->dropShadowBlurRadius;
        left = static_cast<int>(std::ceil(std::max(0.0f, blurMargin - impl->dropShadowOffsetX)));
        top = static_cast<int>(std::ceil(std::max(0.0f, blurMargin - impl->dropShadowOffsetY)));
        right = static_cast<int>(std::ceil(std::max(0.0f, blurMargin + impl->dropShadowOffsetX)));
        bottom = static_cast<int>(std::ceil(std::max(0.0f, blurMargin + impl->dropShadowOffsetY)));
    }
}

// Helper to calculate total margins (shadow + padding)
static void get_total_margins(HWindow::Impl* impl, int& left, int& top, int& right, int& bottom) {
    get_shadow_margins(impl, left, top, right, bottom);
    left += impl->paddingLeft;
    top += impl->paddingTop;
    right += impl->paddingRight;
    bottom += impl->paddingBottom;
}

// Internal helper: render current window contents and commit to Wayland.
static void render_frame(HWindow::Impl* impl) {
    std::cout << "render_frame: Start" << std::endl;
    if (!impl || !impl->surface || !impl->app || !impl->app->impl()->display) {
        return;
    }

    // Ensure layout is up-to-date before rendering
    if (impl->centralItem) {
        // We assume layout was updated during configure or resize.
        // But if content changed dynamically, we might need to trigger it here.
        // For now, let's trust the event loop or explicit update() calls.
    }


    const int w = impl->width;
    const int h = impl->height;

    if (w <= 0 || h <= 0) {
        return;
    }

    // 1) Render the window contents using graphics2d (HPainter + HImage).
    HImage image(w, h, HImage::Format::ARGB32_Premul);
    {
        HPainter painter(&image);
        painter.setAntialiasing(true);

        // Start with transparent background.
        image.fill(HColor::Transparent());

        // If custom paint callback is set, use it instead of default rendering
        if (impl->paintCallback) {
            impl->paintCallback(painter, w, h);
        } else {
            // Default rendering: draw styled window with optional drop shadow

            // Calculate margins needed for drop shadow visibility + content margins
            int iml, imt, imr, imb;
            get_total_margins(impl, iml, imt, imr, imb);
            float marginLeft = static_cast<float>(iml);
            float marginTop = static_cast<float>(imt);
            float marginRight = static_cast<float>(imr);
            float marginBottom = static_cast<float>(imb);

            if (impl->dropShadowEnabled) {
                // Draw shadow behind the main window rect with blur
                HRectF shadowRect(
                    marginLeft + impl->dropShadowOffsetX,
                    marginTop + impl->dropShadowOffsetY,
                    static_cast<float>(w) - marginLeft - marginRight,
                    static_cast<float>(h) - marginTop - marginBottom
                );

                // Enable blur for shadow
                painter.setBlurRadius(impl->dropShadowBlurRadius);
                painter.setBlurEnabled(true);

                painter.setPen(HPen(HPen::Style::NoPen));
                painter.setBrush(impl->dropShadowColor);
                painter.drawRoundedRect(shadowRect, impl->borderRadius, impl->borderRadius);

                // Disable blur for main window drawing
                painter.setBlurEnabled(false);
            }

            // Draw main rounded rectangle with margins to show shadow
            // Note: We use shadow margins ONLY for the background rect, so padding is drawn inside the window.
            int sml, smt, smr, smb;
            get_shadow_margins(impl, sml, smt, smr, smb);
            
            HRectF windowRect(
                static_cast<float>(sml),
                static_cast<float>(smt),
                static_cast<float>(w) - static_cast<float>(sml) - static_cast<float>(smr),
                static_cast<float>(h) - static_cast<float>(smt) - static_cast<float>(smb)
            );

            painter.setPen(impl->borderPen);
            painter.setBrush(impl->backgroundColor);
            painter.drawRoundedRect(windowRect, impl->borderRadius, impl->borderRadius);
        }

        // Paint the central item tree if set
        if (impl->centralItem && impl->centralItem->isVisible()) {
            painter.save();
            // Translate to central item's position (which includes margins)
            painter.translate(static_cast<float>(impl->centralItem->x()), 
                              static_cast<float>(impl->centralItem->y()));
            impl->centralItem->paint(painter);
            painter.restore();
        }

        // HPainter destructor will call end() and update the image.
    }

    // 2) Copy the rendered image into a shared memory buffer for Wayland.
    HShmBuffer buffer(impl->app, w, h);

    const uint8_t* src = static_cast<const uint8_t*>(image.constBits());
    const int srcStride = image.bytesPerLine();
    uint8_t* dst = static_cast<uint8_t*>(buffer.data());
    const int dstStride = buffer.stride();

    const int rowBytesToCopy = std::min(srcStride, dstStride);
    for (int y = 0; y < h; ++y) {
        std::memcpy(dst + static_cast<size_t>(y) * static_cast<size_t>(dstStride),
                    src + static_cast<size_t>(y) * static_cast<size_t>(srcStride),
                    static_cast<size_t>(rowBytesToCopy));
    }

    wl_buffer* wlBuf = static_cast<wl_buffer*>(buffer.wlBuffer());
    wl_surface_attach(impl->surface, wlBuf, 0, 0);
    wl_surface_damage_buffer(impl->surface, 0, 0, w, h);
    wl_surface_commit(impl->surface);
    wl_display_flush(impl->app->impl()->display);
}

static void xdg_toplevel_handle_configure(
    void* data,
    xdg_toplevel* /*toplevel*/,
    int32_t width,
    int32_t height,
    wl_array* /*states*/) {
    auto* impl = static_cast<HWindow::Impl*>(data);
    if (!impl) {
        return;
    }

    if (width > 0) {
        impl->width = width;
    }
    if (height > 0) {
        impl->height = height;
    }

    impl->configured = true;

    // Repaint on resize if the window is visible.
    if (impl->visible) {
        render_frame(impl);
    }
}

static void xdg_toplevel_handle_close(void* data, xdg_toplevel* /*toplevel*/) {
    auto* impl = static_cast<HWindow::Impl*>(data);
    if (!impl || !impl->app) {
        return;
    }

    impl->visible = false;
    impl->app->exit(0);
}

static const xdg_toplevel_listener xdg_toplevel_listener = {
    .configure = xdg_toplevel_handle_configure,
    .close = xdg_toplevel_handle_close,
};

static void xdg_wm_base_ping(void* data, xdg_wm_base* shell, uint32_t serial) {
    (void)data;
    if (shell) {
        xdg_wm_base_pong(shell, serial);
    }
}

static const xdg_wm_base_listener xdg_wm_base_listener = {
    .ping = xdg_wm_base_ping,
};

} // namespace

HWindow::HWindow(HApplication* app)
    : m_impl(std::make_unique<Impl>()) {
    m_impl->window = this;
    m_impl->app = app;
    if (!app || !app->impl() || !app->impl()->compositor) {
        throw std::runtime_error("HWindow requires a connected HApplication with wl_compositor");
    }

    // Ensure xdg_wm_base is available and has a listener for ping/pong.
    if (!app->impl()->xdgWmBase) {
        throw std::runtime_error("HWindow requires xdg_wm_base (XDG shell) from compositor");
    }
    xdg_wm_base_add_listener(app->impl()->xdgWmBase, &xdg_wm_base_listener, app->impl());

    // Create a basic wl_surface and attach XDG roles.
    m_impl->surface = wl_compositor_create_surface(app->impl()->compositor);
    if (!m_impl->surface) {
        throw std::runtime_error("Failed to create wl_surface for HWindow");
    }
    wl_surface_set_user_data(m_impl->surface, m_impl.get());

    m_impl->xdgSurface = xdg_wm_base_get_xdg_surface(app->impl()->xdgWmBase, m_impl->surface);
    if (!m_impl->xdgSurface) {
        throw std::runtime_error("Failed to create xdg_surface for HWindow");
    }

    xdg_surface_add_listener(m_impl->xdgSurface, &xdg_surface_listener, m_impl.get());

    m_impl->xdgToplevel = xdg_surface_get_toplevel(m_impl->xdgSurface);
    if (!m_impl->xdgToplevel) {
        throw std::runtime_error("Failed to create xdg_toplevel for HWindow");
    }

    xdg_toplevel_add_listener(m_impl->xdgToplevel, &xdg_toplevel_listener, m_impl.get());

    // Register as primary window for simple drag support.
    if (app && app->impl()) {
        app->impl()->primaryWindow = this;
    }
}

HWindow::~HWindow() {
    if (m_impl && m_impl->app && m_impl->app->impl() &&
        m_impl->app->impl()->primaryWindow == this) {
        m_impl->app->impl()->primaryWindow = nullptr;
    }
    if (m_impl && m_impl->xdgToplevel) {
        xdg_toplevel_destroy(m_impl->xdgToplevel);
        m_impl->xdgToplevel = nullptr;
    }
    if (m_impl && m_impl->xdgSurface) {
        xdg_surface_destroy(m_impl->xdgSurface);
        m_impl->xdgSurface = nullptr;
    }
    if (m_impl && m_impl->surface && m_impl->app && m_impl->app->impl()->display) {
        wl_surface_destroy(m_impl->surface);
        m_impl->surface = nullptr;
    }
}

HWindow::HWindow(HWindow&&) noexcept = default;
HWindow& HWindow::operator=(HWindow&&) noexcept = default;

void HWindow::setTitle(const std::string& title) {
    m_impl->windowTitle = title;
    if (m_impl->xdgToplevel) {
        xdg_toplevel_set_title(m_impl->xdgToplevel, m_impl->windowTitle.c_str());
    }
}

const std::string& HWindow::title() const {
    return m_impl->windowTitle;
}

int HWindow::width() const {
    return m_impl->width;
}

int HWindow::height() const {
    return m_impl->height;
}

void HWindow::resize(int width, int height) {
    if (width <= 0 || height <= 0) {
        return;
    }

    m_impl->width = width;
    m_impl->height = height;

    // Update central item layout
    // Update central item layout
    // Layout update removed

    if (m_impl->visible) {
        render_frame(m_impl.get());
    }
}

void HWindow::show() {
    m_impl->visible = true;

    // Ensure layout is calculated before first render
    if (m_impl->centralItem) {
        m_impl->centralItem->updateLayout();
    }

    render_frame(m_impl.get());
}

void HWindow::hide() {
    m_impl->visible = false;
    // Future: detach buffers / mark as hidden.
}

void HWindow::update() {
    if (m_impl->visible) {
        render_frame(m_impl.get());
    }
}

// Visual customization methods

void HWindow::setBorderRadius(float radius) {
    m_impl->borderRadius = radius;
    if (m_impl->visible) {
        render_frame(m_impl.get());
    }
}

float HWindow::borderRadius() const {
    return m_impl->borderRadius;
}

void HWindow::setBorderPen(const HPen& pen) {
    m_impl->borderPen = pen;
    if (m_impl->visible) {
        render_frame(m_impl.get());
    }
}

const HPen& HWindow::borderPen() const {
    return m_impl->borderPen;
}

void HWindow::setBackgroundColor(const HColor& color) {
    m_impl->backgroundColor = color;
    if (m_impl->visible) {
        render_frame(m_impl.get());
    }
}

const HColor& HWindow::backgroundColor() const {
    return m_impl->backgroundColor;
}

// Drop shadow methods

void HWindow::setDropShadowEnabled(bool enabled) {
    m_impl->dropShadowEnabled = enabled;
    if (m_impl->visible) {
        render_frame(m_impl.get());
    }
}

bool HWindow::dropShadowEnabled() const {
    return m_impl->dropShadowEnabled;
}

void HWindow::setDropShadowOffset(float x, float y) {
    m_impl->dropShadowOffsetX = x;
    m_impl->dropShadowOffsetY = y;
    if (m_impl->visible) {
        render_frame(m_impl.get());
    }
}

float HWindow::dropShadowOffsetX() const {
    return m_impl->dropShadowOffsetX;
}

float HWindow::dropShadowOffsetY() const {
    return m_impl->dropShadowOffsetY;
}

void HWindow::setDropShadowBlurRadius(float radius) {
    m_impl->dropShadowBlurRadius = radius;
    if (m_impl->visible) {
        render_frame(m_impl.get());
    }
}

float HWindow::dropShadowBlurRadius() const {
    return m_impl->dropShadowBlurRadius;
}

void HWindow::setDropShadowColor(const HColor& color) {
    m_impl->dropShadowColor = color;
    if (m_impl->visible) {
        render_frame(m_impl.get());
    }
}

const HColor& HWindow::dropShadowColor() const {
    return m_impl->dropShadowColor;
}

// Custom paint callback

void HWindow::setPaintCallback(PaintCallback callback) {
    m_impl->paintCallback = std::move(callback);
    if (m_impl->visible) {
        render_frame(m_impl.get());
    }
}

void HWindow::clearPaintCallback() {
    m_impl->paintCallback = nullptr;
    if (m_impl->visible) {
        render_frame(m_impl.get());
    }
}

// Draggable regions

void HWindow::setDraggableRegion(const HRect& region) {
    m_impl->draggableRegions.clear();
    m_impl->draggableRegions.push_back(region);
}

void HWindow::addDraggableRegion(const HRect& region) {
    m_impl->draggableRegions.push_back(region);
}

void HWindow::clearDraggableRegions() {
    m_impl->draggableRegions.clear();
}

// Content item

void HWindow::setContent(HItem* item) {
    m_impl->centralItem = item;
    if (m_impl->visible) {
        render_frame(m_impl.get());
    }
}

HItem* HWindow::content() const {
    return m_impl->centralItem;
}

// Mouse event routing helper (static) - internal with offset
static HMouseArea* findMouseAreaAtOffset(HItem* item, int x, int y, int offsetX, int offsetY) {
    if (!item || !item->isVisible()) {
        return nullptr;
    }

    // Calculate absolute item bounds
    const int absX = offsetX + item->x();
    const int absY = offsetY + item->y();
    const HRect itemBounds(absX, absY, item->width(), item->height());

    // Check if point is even within this item's bounds first
    if (!itemBounds.contains(HPoint(x, y))) {
        return nullptr;
    }

    // Check children first (they're on top) - pass accumulated offset
    for (HItem* child : item->childItems()) {
        HMouseArea* found = findMouseAreaAtOffset(child, x, y, absX, absY);
        if (found) {
            return found;
        }
    }

    // Check if this item is a HMouseArea
    HMouseArea* mouseArea = dynamic_cast<HMouseArea*>(item);
    if (mouseArea && mouseArea->enabled()) {
        return mouseArea;
    }

    return nullptr;
}

// Mouse event routing helper (static) - public entry point
HMouseArea* HWindow::findMouseAreaAt(HItem* item, int x, int y) {
    return findMouseAreaAtOffset(item, x, y, 0, 0);
}

void HWindow::setPadding(int left, int top, int right, int bottom) {
    m_impl->paddingLeft = left;
    m_impl->paddingTop = top;
    m_impl->paddingRight = right;
    m_impl->paddingBottom = bottom;
    // Layout update removed
    update();
}

void HWindow::setPadding(int padding) {
    setPadding(padding, padding, padding, padding);
}

void HWindow::getPadding(int* left, int* top, int* right, int* bottom) const {
    if (left) *left = m_impl->paddingLeft;
    if (top) *top = m_impl->paddingTop;
    if (right) *right = m_impl->paddingRight;
    if (bottom) *bottom = m_impl->paddingBottom;
}

void HWindow::setFocusItem(HItem* item) {
    std::cout << "HWindow::setFocusItem() item=" << item << " current=" << m_impl->focusItem << std::endl;
    if (m_impl->focusItem == item) return;

    if (m_impl->focusItem) {
        std::cout << "HWindow::setFocusItem() removing focus from old item" << std::endl;
        m_impl->focusItem->setFocus(false);
    }

    m_impl->focusItem = item;

    if (m_impl->focusItem) {
        std::cout << "HWindow::setFocusItem() setting focus on new item" << std::endl;
        m_impl->focusItem->setFocus(true);
    }
}

HItem* HWindow::focusItem() const {
    return m_impl->focusItem;
}

void HWindow::dispatchKeyEvent(HKeyEvent& event) {
    std::cout << "HWindow::dispatchKeyEvent() focusItem=" << m_impl->focusItem << " key=" << (int)event.key << " pressed=" << event.pressed << std::endl;
    if (m_impl->focusItem) {
        if (event.pressed) {
            std::cout << "HWindow::dispatchKeyEvent() calling onKeyPress on focusItem" << std::endl;
            m_impl->focusItem->onKeyPress(event);
        } else {
            m_impl->focusItem->onKeyRelease(event);
        }
    } else {
        std::cout << "HWindow::dispatchKeyEvent() no focus item!" << std::endl;
    }
}

} // namespace Ht