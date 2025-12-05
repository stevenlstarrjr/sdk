#pragma once

#include <memory>
#include <vector>
#include "HInput.h"

namespace Ht {

class HApplication;

/**
 * @brief HKeyboard represents the physical keyboard device.
 * Wayland Equivalent: wl_keyboard
 */
class HKeyboard {
public:
    explicit HKeyboard(HApplication* app);
    ~HKeyboard();

    HKeyboard(const HKeyboard&) = delete;
    HKeyboard& operator=(const HKeyboard&) = delete;

    // Modifier state
    HModifier modifiers() const;
    bool isShiftPressed() const;
    bool isControlPressed() const;
    bool isAltPressed() const;
    bool isMetaPressed() const;

    // Key state
    bool isKeyPressed(HKey key) const;

    // Repeat info
    int repeatRate() const;
    int repeatDelay() const;

    // Initialization (called by HApplication)
    void setSeat(void* wlSeat);

    // Internal access
    struct Impl;
    Impl* impl() const { return m_impl.get(); }

private:
    std::unique_ptr<Impl> m_impl;
};

} // namespace Ht
