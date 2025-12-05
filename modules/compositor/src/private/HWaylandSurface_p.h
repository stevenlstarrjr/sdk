#pragma once

#include "HWaylandSurface.h"

extern "C" {
#include <wlroots/wlroots-0.20/wlr/types/wlr_compositor.h> // defines wlr_surface
}

namespace Ht {

/**
 * @brief Private implementation for HWaylandSurface.
 * Wraps wlr_surface directly.
 */
struct HWaylandSurface::Impl {
    wlr_surface* surface = nullptr;
};

} // namespace Ht

