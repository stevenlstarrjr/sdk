#pragma once

#include "HWaylandXdgShell.h"
#include "HWaylandCompositor.h"
#include "private/HWaylandCompositor_p.h"

extern "C" {
#include <wayland-server-core.h>
#include <wlroots/wlroots-0.20/wlr/types/wlr_xdg_shell.h>
}

#include <vector>

namespace Ht {

struct HWaylandXdgShell::Impl {
    HWaylandCompositor* compositor = nullptr;
    wlr_xdg_shell* shell = nullptr;
    wl_listener newSurfaceListener;
    wl_listener newToplevelListener;

    std::vector<std::unique_ptr<HWaylandXdgSurface>> surfaces;
    std::vector<std::unique_ptr<HWaylandXdgToplevel>> toplevels;
};

struct HWaylandXdgSurface::Impl {
    wlr_xdg_surface* surface = nullptr;
};

struct HWaylandXdgToplevel::Impl {
    wlr_xdg_toplevel* toplevel = nullptr;
};

} // namespace Ht
