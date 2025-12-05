#include "HWaylandSurface.h"
#include "private/HWaylandSurface_p.h"

namespace Ht {

HWaylandSurface::HWaylandSurface()
    : m_impl(std::make_unique<Impl>()) {
}

HWaylandSurface::~HWaylandSurface() = default;

HWaylandSurface::HWaylandSurface(HWaylandSurface&&) noexcept = default;
HWaylandSurface& HWaylandSurface::operator=(HWaylandSurface&&) noexcept = default;

int HWaylandSurface::width() const {
    return (m_impl && m_impl->surface) ? m_impl->surface->current.width : 0;
}

int HWaylandSurface::height() const {
    return (m_impl && m_impl->surface) ? m_impl->surface->current.height : 0;
}

bool HWaylandSurface::isMapped() const {
    return m_impl && m_impl->surface && m_impl->surface->mapped;
}

} // namespace Ht

