#pragma once

#include "HWaylandSeat.h"
#include "HWaylandCompositor.h"
#include "private/HWaylandCompositor_p.h"

extern "C" {
#include <wayland-server-core.h>
#include <wlroots/wlroots-0.20/wlr/types/wlr_seat.h>
}

namespace Ht {

struct HWaylandSeat::Impl {
    HWaylandCompositor* compositor = nullptr;
    wlr_seat* seat = nullptr;
};

} // namespace Ht

