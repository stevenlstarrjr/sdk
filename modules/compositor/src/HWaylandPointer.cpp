#include "HWaylandPointer.h"
#include "private/HWaylandPointer_p.h"

namespace Ht {

HWaylandPointer::HWaylandPointer()
    : m_impl(std::make_unique<Impl>()) {
}

HWaylandPointer::~HWaylandPointer() = default;

HWaylandPointer::HWaylandPointer(HWaylandPointer&&) noexcept = default;
HWaylandPointer& HWaylandPointer::operator=(HWaylandPointer&&) noexcept = default;

bool HWaylandPointer::isValid() const {
    return m_impl && m_impl->pointer;
}

} // namespace Ht

