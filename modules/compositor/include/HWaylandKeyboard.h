#pragma once

#include <memory>

namespace Ht {

/**
 * @brief HWaylandKeyboard represents a keyboard device.
 * Qt Equivalent: QWaylandKeyboard
 * wlroots Backend: wlr_keyboard
 */
class HWaylandKeyboard {
public:
    HWaylandKeyboard();
    ~HWaylandKeyboard();

    HWaylandKeyboard(const HWaylandKeyboard&) = delete;
    HWaylandKeyboard& operator=(const HWaylandKeyboard&) = delete;
    HWaylandKeyboard(HWaylandKeyboard&&) noexcept;
    HWaylandKeyboard& operator=(HWaylandKeyboard&&) noexcept;

    bool isValid() const;

    struct Impl;
    Impl* impl() const { return m_impl.get(); }

private:
    std::unique_ptr<Impl> m_impl;
};

} // namespace Ht

