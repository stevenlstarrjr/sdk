#pragma once

#include <memory>

namespace Ht {

class HWaylandXdgShell {
public:
    /**
     * @brief Create the XDG shell extension for a compositor.
     *
     * Qt Equivalent: QWaylandXdgShell(QWaylandCompositor *compositor)
     */
    explicit HWaylandXdgShell(class HWaylandCompositor* compositor);
    ~HWaylandXdgShell();

    // Non-copyable, movable
    HWaylandXdgShell(const HWaylandXdgShell&) = delete;
    HWaylandXdgShell& operator=(const HWaylandXdgShell&) = delete;
    HWaylandXdgShell(HWaylandXdgShell&&) noexcept;
    HWaylandXdgShell& operator=(HWaylandXdgShell&&) noexcept;

    struct Impl;
    Impl* impl() const { return m_impl.get(); }

private:
    std::unique_ptr<Impl> m_impl;
};

/**
 * @brief Base XDG surface.
 * Qt Equivalent: QWaylandXdgSurface
 * wlroots Backend: wlr_xdg_surface
 */
class HWaylandXdgSurface {
public:
    HWaylandXdgSurface();
    ~HWaylandXdgSurface();

    HWaylandXdgSurface(const HWaylandXdgSurface&) = delete;
    HWaylandXdgSurface& operator=(const HWaylandXdgSurface&) = delete;
    HWaylandXdgSurface(HWaylandXdgSurface&&) noexcept;
    HWaylandXdgSurface& operator=(HWaylandXdgSurface&&) noexcept;

    bool isToplevel() const;
    bool isPopup() const;

    struct Impl;
    Impl* impl() const { return m_impl.get(); }

private:
    std::unique_ptr<Impl> m_impl;
};

/**
 * @brief XDG toplevel surface (application window).
 * Qt Equivalent: QWaylandXdgToplevel
 * wlroots Backend: wlr_xdg_toplevel
 */
class HWaylandXdgToplevel {
public:
    HWaylandXdgToplevel();
    ~HWaylandXdgToplevel();

    HWaylandXdgToplevel(const HWaylandXdgToplevel&) = delete;
    HWaylandXdgToplevel& operator=(const HWaylandXdgToplevel&) = delete;
    HWaylandXdgToplevel(HWaylandXdgToplevel&&) noexcept;
    HWaylandXdgToplevel& operator=(HWaylandXdgToplevel&&) noexcept;

    const char* title() const;
    const char* appId() const;

    struct Impl;
    Impl* impl() const { return m_impl.get(); }

private:
    std::unique_ptr<Impl> m_impl;
};

} // namespace Ht
