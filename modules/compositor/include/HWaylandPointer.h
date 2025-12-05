#pragma once

#include <memory>

namespace Ht {

/**
 * @brief HWaylandPointer represents a pointer device.
 * Qt Equivalent: QWaylandPointer
 * wlroots Backend: wlr_pointer
 */
class HWaylandPointer {
public:
    HWaylandPointer();
    ~HWaylandPointer();

    HWaylandPointer(const HWaylandPointer&) = delete;
    HWaylandPointer& operator=(const HWaylandPointer&) = delete;
    HWaylandPointer(HWaylandPointer&&) noexcept;
    HWaylandPointer& operator=(HWaylandPointer&&) noexcept;

    bool isValid() const;

    struct Impl;
    Impl* impl() const { return m_impl.get(); }

private:
    std::unique_ptr<Impl> m_impl;
};

} // namespace Ht

