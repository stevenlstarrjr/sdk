#pragma once

#include "HWaylandOutput.h"

extern "C" {
#include <wlroots/wlroots-0.20/wlr/types/wlr_output.h>
}

namespace Ht {

/**
 * @brief Private implementation for HWaylandOutput.
 * Wraps wlr_output directly.
 */
struct HWaylandOutput::Impl {
    wlr_output* output = nullptr;
};

} // namespace Ht

