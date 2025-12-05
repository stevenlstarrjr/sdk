#pragma once

#include "HWaylandKeyboard.h"

extern "C" {
#include <wlroots/wlroots-0.20/wlr/types/wlr_keyboard.h>
}

namespace Ht {

struct HWaylandKeyboard::Impl {
    wlr_keyboard* keyboard = nullptr;
};

} // namespace Ht

