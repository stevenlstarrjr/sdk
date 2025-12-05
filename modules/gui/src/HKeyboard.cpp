#include "HKeyboard.h"
#include "private/HKeyboard_p.h"
#include "HWindow.h"
#include "private/HWindow_p.h"
#include "HInput.h"

#include <sys/mman.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

namespace Ht {

namespace {

// Helper: Map XKB keysym to HKey
// This is a partial mapping. Full mapping would be extensive.
HKey mapKeysym(xkb_keysym_t sym) {
    switch (sym) {
        case XKB_KEY_Escape: return HKey::Escape;
        case XKB_KEY_Tab: return HKey::Tab;
        case XKB_KEY_ISO_Left_Tab: return HKey::Backtab;
        case XKB_KEY_BackSpace: return HKey::Backspace;
        case XKB_KEY_Return: return HKey::Return;
        case XKB_KEY_KP_Enter: return HKey::Enter;
        case XKB_KEY_Insert: return HKey::Insert;
        case XKB_KEY_Delete: return HKey::Delete;
        case XKB_KEY_Pause: return HKey::Pause;
        case XKB_KEY_Print: return HKey::Print;
        case XKB_KEY_Sys_Req: return HKey::SysReq;
        case XKB_KEY_Clear: return HKey::Clear;
        case XKB_KEY_Home: return HKey::Home;
        case XKB_KEY_End: return HKey::End;
        case XKB_KEY_Left: return HKey::Left;
        case XKB_KEY_Up: return HKey::Up;
        case XKB_KEY_Right: return HKey::Right;
        case XKB_KEY_Down: return HKey::Down;
        case XKB_KEY_Page_Up: return HKey::PageUp;
        case XKB_KEY_Page_Down: return HKey::PageDown;
        case XKB_KEY_Shift_L: 
        case XKB_KEY_Shift_R: return HKey::Shift;
        case XKB_KEY_Control_L:
        case XKB_KEY_Control_R: return HKey::Control;
        case XKB_KEY_Meta_L:
        case XKB_KEY_Meta_R: return HKey::Meta;
        case XKB_KEY_Alt_L:
        case XKB_KEY_Alt_R: return HKey::Alt;
        case XKB_KEY_Caps_Lock: return HKey::CapsLock;
        case XKB_KEY_Num_Lock: return HKey::NumLock;
        case XKB_KEY_Scroll_Lock: return HKey::ScrollLock;
        case XKB_KEY_space: return HKey::Space;
        
        // Letters
        case XKB_KEY_A: case XKB_KEY_a: return HKey::A;
        case XKB_KEY_B: case XKB_KEY_b: return HKey::B;
        case XKB_KEY_C: case XKB_KEY_c: return HKey::C;
        case XKB_KEY_D: case XKB_KEY_d: return HKey::D;
        case XKB_KEY_E: case XKB_KEY_e: return HKey::E;
        case XKB_KEY_F: case XKB_KEY_f: return HKey::F;
        case XKB_KEY_G: case XKB_KEY_g: return HKey::G;
        case XKB_KEY_H: case XKB_KEY_h: return HKey::H;
        case XKB_KEY_I: case XKB_KEY_i: return HKey::I;
        case XKB_KEY_J: case XKB_KEY_j: return HKey::J;
        case XKB_KEY_K: case XKB_KEY_k: return HKey::K;
        case XKB_KEY_L: case XKB_KEY_l: return HKey::L;
        case XKB_KEY_M: case XKB_KEY_m: return HKey::M;
        case XKB_KEY_N: case XKB_KEY_n: return HKey::N;
        case XKB_KEY_O: case XKB_KEY_o: return HKey::O;
        case XKB_KEY_P: case XKB_KEY_p: return HKey::P;
        case XKB_KEY_Q: case XKB_KEY_q: return HKey::Q;
        case XKB_KEY_R: case XKB_KEY_r: return HKey::R;
        case XKB_KEY_S: case XKB_KEY_s: return HKey::S;
        case XKB_KEY_T: case XKB_KEY_t: return HKey::T;
        case XKB_KEY_U: case XKB_KEY_u: return HKey::U;
        case XKB_KEY_V: case XKB_KEY_v: return HKey::V;
        case XKB_KEY_W: case XKB_KEY_w: return HKey::W;
        case XKB_KEY_X: case XKB_KEY_x: return HKey::X;
        case XKB_KEY_Y: case XKB_KEY_y: return HKey::Y;
        case XKB_KEY_Z: case XKB_KEY_z: return HKey::Z;

        // Function keys
        case XKB_KEY_F1: return HKey::F1;
        case XKB_KEY_F2: return HKey::F2;
        case XKB_KEY_F3: return HKey::F3;
        case XKB_KEY_F4: return HKey::F4;
        case XKB_KEY_F5: return HKey::F5;
        case XKB_KEY_F6: return HKey::F6;
        case XKB_KEY_F7: return HKey::F7;
        case XKB_KEY_F8: return HKey::F8;
        case XKB_KEY_F9: return HKey::F9;
        case XKB_KEY_F10: return HKey::F10;
        case XKB_KEY_F11: return HKey::F11;
        case XKB_KEY_F12: return HKey::F12;

        default: return HKey::Unknown;
    }
}

// wl_keyboard listeners

static void keyboard_handle_keymap(void* data, wl_keyboard* /*keyboard*/,
                                   uint32_t format, int32_t fd, uint32_t size) {
    auto* impl = static_cast<HKeyboard::Impl*>(data);
    if (!impl) return;
    
    std::cout << "Keyboard: keymap received, format=" << format << " size=" << size << std::endl;

    if (format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1) {
        close(fd);
        return;
    }

    char* map_str = static_cast<char*>(mmap(nullptr, size, PROT_READ, MAP_PRIVATE, fd, 0));
    if (map_str == MAP_FAILED) {
        close(fd);
        return;
    }
    
    std::cout << "Keyboard: mapped keymap" << std::endl;

    // Create xkb context if not exists
    if (!impl->xkbContext) {
        impl->xkbContext = xkb_context_new(XKB_CONTEXT_NO_FLAGS);
    }

    if (impl->xkbKeymap) {
        xkb_keymap_unref(impl->xkbKeymap);
    }

    impl->xkbKeymap = xkb_keymap_new_from_string(impl->xkbContext, map_str,
                                                 XKB_KEYMAP_FORMAT_TEXT_V1,
                                                 XKB_KEYMAP_COMPILE_NO_FLAGS);
    
    munmap(map_str, size);
    close(fd);

    if (impl->xkbKeymap) {
        std::cout << "Keyboard: xkb keymap created successfully" << std::endl;
        if (impl->xkbState) {
            xkb_state_unref(impl->xkbState);
        }
        impl->xkbState = xkb_state_new(impl->xkbKeymap);

        // Update modifier indices
        impl->modShift = xkb_keymap_mod_get_index(impl->xkbKeymap, XKB_MOD_NAME_SHIFT);
        impl->modCaps = xkb_keymap_mod_get_index(impl->xkbKeymap, XKB_MOD_NAME_CAPS);
        impl->modCtrl = xkb_keymap_mod_get_index(impl->xkbKeymap, XKB_MOD_NAME_CTRL);
        impl->modAlt = xkb_keymap_mod_get_index(impl->xkbKeymap, XKB_MOD_NAME_ALT);
        impl->modMeta = xkb_keymap_mod_get_index(impl->xkbKeymap, XKB_MOD_NAME_LOGO); // Often Logo/Super
    }
}

static void keyboard_handle_enter(void* data, wl_keyboard* /*keyboard*/,
                                  uint32_t serial, wl_surface* surface, wl_array* /*keys*/) {
    auto* impl = static_cast<HKeyboard::Impl*>(data);
    if (!impl) return;

    std::cout << "Keyboard: Enter surface " << surface << std::endl;
    impl->focusSurface = surface;
    impl->enterSerial = serial;
}

static void keyboard_handle_leave(void* data, wl_keyboard* /*keyboard*/,
                                  uint32_t /*serial*/, wl_surface* /*surface*/) {
    auto* impl = static_cast<HKeyboard::Impl*>(data);
    if (!impl) return;

    std::cout << "Keyboard: Leave surface" << std::endl;
    impl->focusSurface = nullptr;
}

static void keyboard_handle_key(void* data, wl_keyboard* /*keyboard*/,
                                uint32_t /*serial*/, uint32_t /*time*/, uint32_t key, uint32_t state) {
    auto* impl = static_cast<HKeyboard::Impl*>(data);
    if (!impl) {
        std::cerr << "Keyboard: impl is null" << std::endl;
        return;
    }
    if (!impl->focusSurface) {
        std::cerr << "Keyboard: no focus surface" << std::endl;
        return;
    }
    if (!impl->xkbState) {
        std::cerr << "Keyboard: no xkb state" << std::endl;
        return;
    }

    // Key is raw scancode - 8 (X11 bias)
    xkb_keycode_t keycode = key + 8;
    xkb_keysym_t sym = xkb_state_key_get_one_sym(impl->xkbState, keycode);
    
    HKey hKey = mapKeysym(sym);
    bool pressed = (state == WL_KEYBOARD_KEY_STATE_PRESSED);
    
    std::cout << "Keyboard: key " << key << " -> sym " << sym << " pressed=" << pressed << std::endl;

    // Get UTF-8 text
    char buffer[64];
    int len = xkb_state_key_get_utf8(impl->xkbState, keycode, buffer, sizeof(buffer));
    std::string text(buffer, len > 0 ? len : 0);

    HKeyEvent event;
    event.key = hKey;
    event.modifiers = impl->getCurrentModifiers();
    event.text = text;
    event.pressed = pressed;
    event.isAutoRepeat = false; // Wayland handles repeat in client usually, simplified here
    event.nativeScanCode = key;
    event.nativeVirtualKey = sym;

    // Dispatch to window
    auto* winImpl = static_cast<HWindow::Impl*>(wl_surface_get_user_data(impl->focusSurface));
    if (winImpl && winImpl->window) {
        winImpl->window->dispatchKeyEvent(event);
    }
}

static void keyboard_handle_modifiers(void* data, wl_keyboard* /*keyboard*/,
                                      uint32_t /*serial*/, uint32_t mods_depressed,
                                      uint32_t mods_latched, uint32_t mods_locked,
                                      uint32_t group) {
    auto* impl = static_cast<HKeyboard::Impl*>(data);
    if (!impl || !impl->xkbState) return;

    xkb_state_update_mask(impl->xkbState, mods_depressed, mods_latched, mods_locked, 0, 0, group);
}

static void keyboard_handle_repeat_info(void* data, wl_keyboard* /*keyboard*/,
                                        int32_t rate, int32_t delay) {
    auto* impl = static_cast<HKeyboard::Impl*>(data);
    if (!impl) return;
    
    impl->repeatRate = rate;
    impl->repeatDelay = delay;
}

static const wl_keyboard_listener keyboard_listener = {
    .keymap = keyboard_handle_keymap,
    .enter = keyboard_handle_enter,
    .leave = keyboard_handle_leave,
    .key = keyboard_handle_key,
    .modifiers = keyboard_handle_modifiers,
    .repeat_info = keyboard_handle_repeat_info,
};

} // namespace

HKeyboard::HKeyboard(HApplication* app)
    : m_impl(std::make_unique<Impl>(app)) {
}

HKeyboard::~HKeyboard() = default;

HModifier HKeyboard::modifiers() const {
    return m_impl->getCurrentModifiers();
}

bool HKeyboard::isShiftPressed() const {
    return (modifiers() & HModifier::ShiftModifier) != HModifier::NoModifier;
}

bool HKeyboard::isControlPressed() const {
    return (modifiers() & HModifier::ControlModifier) != HModifier::NoModifier;
}

bool HKeyboard::isAltPressed() const {
    return (modifiers() & HModifier::AltModifier) != HModifier::NoModifier;
}

bool HKeyboard::isMetaPressed() const {
    return (modifiers() & HModifier::MetaModifier) != HModifier::NoModifier;
}

bool HKeyboard::isKeyPressed(HKey key) const {
    // TODO: Implement key state tracking if needed (using xkb_state_key_get_one_sym check or internal set)
    return false;
}

int HKeyboard::repeatRate() const {
    return m_impl->repeatRate;
}

int HKeyboard::repeatDelay() const {
    return m_impl->repeatDelay;
}

void HKeyboard::setSeat(void* wlSeat) {
    wl_seat* seat = static_cast<wl_seat*>(wlSeat);
    if (!seat) return;

    if (m_impl->wlKeyboard) {
        // Handle capability loss if needed, or just re-bind
        if (m_impl->xkbState) xkb_state_unref(m_impl->xkbState);
        if (m_impl->xkbKeymap) xkb_keymap_unref(m_impl->xkbKeymap);
        if (m_impl->xkbContext) xkb_context_unref(m_impl->xkbContext);
        m_impl->xkbState = nullptr;
        m_impl->xkbKeymap = nullptr;
        m_impl->xkbContext = nullptr;

        wl_keyboard_destroy(m_impl->wlKeyboard);
        m_impl->wlKeyboard = nullptr;
    }

    m_impl->wlKeyboard = wl_seat_get_keyboard(seat);
    if (m_impl->wlKeyboard) {
        wl_keyboard_add_listener(m_impl->wlKeyboard, &keyboard_listener, m_impl.get());
    }
}

// Impl methods

HModifier HKeyboard::Impl::getCurrentModifiers() const {
    uint32_t mask = 0;
    if (!xkbState) return HModifier::NoModifier;

    if (xkb_state_mod_index_is_active(xkbState, modShift, XKB_STATE_MODS_EFFECTIVE))
        mask |= static_cast<uint32_t>(HModifier::ShiftModifier);
    if (xkb_state_mod_index_is_active(xkbState, modCtrl, XKB_STATE_MODS_EFFECTIVE))
        mask |= static_cast<uint32_t>(HModifier::ControlModifier);
    if (xkb_state_mod_index_is_active(xkbState, modAlt, XKB_STATE_MODS_EFFECTIVE))
        mask |= static_cast<uint32_t>(HModifier::AltModifier);
    if (xkb_state_mod_index_is_active(xkbState, modMeta, XKB_STATE_MODS_EFFECTIVE))
        mask |= static_cast<uint32_t>(HModifier::MetaModifier);

    return static_cast<HModifier>(mask);
}

} // namespace Ht
