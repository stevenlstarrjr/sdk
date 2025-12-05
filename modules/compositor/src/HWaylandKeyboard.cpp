#include "HWaylandKeyboard.h"
#include "private/HWaylandKeyboard_p.h"

namespace Ht {

HWaylandKeyboard::HWaylandKeyboard()
    : m_impl(std::make_unique<Impl>()) {
}

HWaylandKeyboard::~HWaylandKeyboard() = default;

HWaylandKeyboard::HWaylandKeyboard(HWaylandKeyboard&&) noexcept = default;
HWaylandKeyboard& HWaylandKeyboard::operator=(HWaylandKeyboard&&) noexcept = default;

bool HWaylandKeyboard::isValid() const {
    return m_impl && m_impl->keyboard;
}

} // namespace Ht

