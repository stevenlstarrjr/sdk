#include "HWaylandSeat.h"
#include "private/HWaylandSeat_p.h"

namespace Ht {

HWaylandSeat::HWaylandSeat(HWaylandCompositor* compositor, const char* name)
    : m_impl(std::make_unique<Impl>()) {
    m_impl->compositor = compositor;
    if (!compositor || !compositor->impl() || !compositor->impl()->display) {
        throw std::runtime_error("HWaylandSeat requires a valid HWaylandCompositor");
    }

    const char* seatName = name ? name : "seat0";
    m_impl->seat = wlr_seat_create(compositor->impl()->display, seatName);
    if (!m_impl->seat) {
        throw std::runtime_error("Failed to create wlr_seat");
    }
}

HWaylandSeat::~HWaylandSeat() = default;

HWaylandSeat::HWaylandSeat(HWaylandSeat&&) noexcept = default;
HWaylandSeat& HWaylandSeat::operator=(HWaylandSeat&&) noexcept = default;

const char* HWaylandSeat::name() const {
    return (m_impl && m_impl->seat && m_impl->seat->name)
        ? m_impl->seat->name
        : nullptr;
}

bool HWaylandSeat::hasPointer() const {
    return m_impl && m_impl->seat && (m_impl->seat->capabilities & WL_SEAT_CAPABILITY_POINTER);
}

bool HWaylandSeat::hasKeyboard() const {
    return m_impl && m_impl->seat && (m_impl->seat->capabilities & WL_SEAT_CAPABILITY_KEYBOARD);
}

bool HWaylandSeat::hasTouch() const {
    return m_impl && m_impl->seat && (m_impl->seat->capabilities & WL_SEAT_CAPABILITY_TOUCH);
}

} // namespace Ht
