#pragma once

#include <memory>

namespace Ht {

/**
 * @brief HWaylandSurface represents a rectangular area on an output device.
 * Qt Equivalent: QWaylandSurface
 * wlroots Backend: wlr_surface
 */
class HWaylandSurface {
public:
    HWaylandSurface();
    ~HWaylandSurface();

    // Non-copyable, movable
    HWaylandSurface(const HWaylandSurface&) = delete;
    HWaylandSurface& operator=(const HWaylandSurface&) = delete;
    HWaylandSurface(HWaylandSurface&&) noexcept;
    HWaylandSurface& operator=(HWaylandSurface&&) noexcept;

    // Basic dimensions in surface-local coordinates (may be zero if unattached)
    int width() const;
    int height() const;

    bool isMapped() const;

    // Internal wlroots access for compositor internals
    struct Impl;
    Impl* impl() const { return m_impl.get(); }

private:
    std::unique_ptr<Impl> m_impl;
};

} // namespace Ht

