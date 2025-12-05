#pragma once

#include "HWaylandCompositor.h"

// Forward declare wlroots / Wayland types (no public exposure)
struct wl_display;
struct wl_event_loop;

namespace Ht {

/**
 * @brief Private implementation for HWaylandCompositor.
 * Wraps wl_display directly.
 */
struct HWaylandCompositor::Impl {
    wl_display* display = nullptr;
    wl_event_loop* eventLoop = nullptr;
    const char* socketName = nullptr;

    Impl();
    ~Impl();

    bool initialize();
    void cleanup();
};

} // namespace Ht

