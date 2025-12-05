#pragma once

#include "HWaylandPointer.h"

extern "C" {
#include <wlroots/wlroots-0.20/wlr/types/wlr_pointer.h>
}

namespace Ht {

struct HWaylandPointer::Impl {
    wlr_pointer* pointer = nullptr;
};

} // namespace Ht

