#pragma once

#include "HKeyboard.h"
#include "HApplication.h"
#include <xkbcommon/xkbcommon.h>
#include <wayland-client.h>

namespace Ht {

struct HKeyboard::Impl {
    HApplication* app;
    wl_keyboard* wlKeyboard = nullptr;
    
    xkb_context* xkbContext = nullptr;
    xkb_keymap* xkbKeymap = nullptr;
    xkb_state* xkbState = nullptr;

    // Modifier indices
    xkb_mod_index_t modShift = XKB_MOD_INVALID;
    xkb_mod_index_t modCaps = XKB_MOD_INVALID;
    xkb_mod_index_t modCtrl = XKB_MOD_INVALID;
    xkb_mod_index_t modAlt = XKB_MOD_INVALID;
    xkb_mod_index_t modMeta = XKB_MOD_INVALID;

    // Repeat info
    int32_t repeatRate = 25;
    int32_t repeatDelay = 400;
    
    // Current focus
    wl_surface* focusSurface = nullptr;
    uint32_t enterSerial = 0;

    HModifier getCurrentModifiers() const;

    Impl(HApplication* a) : app(a) {}
    ~Impl() {
        if (xkbState) xkb_state_unref(xkbState);
        if (xkbKeymap) xkb_keymap_unref(xkbKeymap);
        if (xkbContext) xkb_context_unref(xkbContext);
        if (wlKeyboard) wl_keyboard_destroy(wlKeyboard);
    }
};

}
