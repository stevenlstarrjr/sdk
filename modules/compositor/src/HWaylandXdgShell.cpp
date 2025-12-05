#include "HWaylandXdgShell.h"
#include "private/HWaylandXdgShell_p.h"

extern "C" {
#include <wayland-server-core.h>
}

namespace Ht {

namespace {

void handle_new_xdg_surface(struct wl_listener* listener, void* data) {
    auto* impl = wl_container_of(listener, static_cast<HWaylandXdgShell::Impl*>(nullptr), newSurfaceListener);
    // Recompute impl from listener using standard container pattern
    impl = reinterpret_cast<HWaylandXdgShell::Impl*>(
        reinterpret_cast<char*>(listener) -
        offsetof(HWaylandXdgShell::Impl, newSurfaceListener));

    auto* wlrSurface = static_cast<wlr_xdg_surface*>(data);
    if (!impl || !wlrSurface) {
        return;
    }

    auto surface = std::make_unique<HWaylandXdgSurface>();
    surface->impl()->surface = wlrSurface;
    impl->surfaces.push_back(std::move(surface));
}

void handle_new_xdg_toplevel(struct wl_listener* listener, void* data) {
    auto* impl = reinterpret_cast<HWaylandXdgShell::Impl*>(
        reinterpret_cast<char*>(listener) -
        offsetof(HWaylandXdgShell::Impl, newToplevelListener));

    auto* wlrToplevel = static_cast<wlr_xdg_toplevel*>(data);
    if (!impl || !wlrToplevel) {
        return;
    }

    auto toplevel = std::make_unique<HWaylandXdgToplevel>();
    toplevel->impl()->toplevel = wlrToplevel;
    impl->toplevels.push_back(std::move(toplevel));
}

} // namespace

// HWaylandXdgShell
HWaylandXdgShell::HWaylandXdgShell(HWaylandCompositor* compositor)
    : m_impl(std::make_unique<Impl>()) {
    m_impl->compositor = compositor;
    if (!compositor || !compositor->impl() || !compositor->impl()->display) {
        throw std::runtime_error("HWaylandXdgShell requires a valid HWaylandCompositor");
    }

    // Create the xdg_wm_base global with a reasonable protocol version (e.g. 3).
    m_impl->shell = wlr_xdg_shell_create(compositor->impl()->display, 3);
    if (!m_impl->shell) {
        throw std::runtime_error("Failed to create wlr_xdg_shell");
    }
    m_impl->shell->data = this;

    // Hook wlroots events so we can wrap new xdg surfaces/toplevels
    m_impl->newSurfaceListener.notify = handle_new_xdg_surface;
    wl_signal_add(&m_impl->shell->events.new_surface, &m_impl->newSurfaceListener);

    m_impl->newToplevelListener.notify = handle_new_xdg_toplevel;
    wl_signal_add(&m_impl->shell->events.new_toplevel, &m_impl->newToplevelListener);
}

HWaylandXdgShell::~HWaylandXdgShell() = default;

HWaylandXdgShell::HWaylandXdgShell(HWaylandXdgShell&&) noexcept = default;
HWaylandXdgShell& HWaylandXdgShell::operator=(HWaylandXdgShell&&) noexcept = default;

// HWaylandXdgSurface
HWaylandXdgSurface::HWaylandXdgSurface()
    : m_impl(std::make_unique<Impl>()) {
}

HWaylandXdgSurface::~HWaylandXdgSurface() = default;

HWaylandXdgSurface::HWaylandXdgSurface(HWaylandXdgSurface&&) noexcept = default;
HWaylandXdgSurface& HWaylandXdgSurface::operator=(HWaylandXdgSurface&&) noexcept = default;

bool HWaylandXdgSurface::isToplevel() const {
    return m_impl && m_impl->surface && m_impl->surface->role == WLR_XDG_SURFACE_ROLE_TOPLEVEL;
}

bool HWaylandXdgSurface::isPopup() const {
    return m_impl && m_impl->surface && m_impl->surface->role == WLR_XDG_SURFACE_ROLE_POPUP;
}

// HWaylandXdgToplevel
HWaylandXdgToplevel::HWaylandXdgToplevel()
    : m_impl(std::make_unique<Impl>()) {
}

HWaylandXdgToplevel::~HWaylandXdgToplevel() = default;

HWaylandXdgToplevel::HWaylandXdgToplevel(HWaylandXdgToplevel&&) noexcept = default;
HWaylandXdgToplevel& HWaylandXdgToplevel::operator=(HWaylandXdgToplevel&&) noexcept = default;

const char* HWaylandXdgToplevel::title() const {
    return (m_impl && m_impl->toplevel && m_impl->toplevel->title)
        ? m_impl->toplevel->title
        : nullptr;
}

const char* HWaylandXdgToplevel::appId() const {
    return (m_impl && m_impl->toplevel && m_impl->toplevel->app_id)
        ? m_impl->toplevel->app_id
        : nullptr;
}

} // namespace Ht
