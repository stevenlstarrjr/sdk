#pragma once

#include "HWindow.h"
#include "HApplication.h"
#include "private/HApplication_p.h"
#include "HColor.h"
#include "HPen.h"
#include "HRect.h"

#include <vector>

extern "C" {
#include <wayland-client.h>
#include "xdg-shell-client-protocol.h"
}

namespace Ht {

/**
 * @brief Private implementation for HWindow.
 * Wraps wl_surface on the client side. XDG roles (xdg_surface/toplevel)
 * will be added in a later pass.
 */
struct HWindow::Impl {
    HWindow* window = nullptr;
    HApplication* app = nullptr;
    wl_surface* surface = nullptr;
    xdg_surface* xdgSurface = nullptr;
    xdg_toplevel* xdgToplevel = nullptr;
    bool configured = false;
    std::string windowTitle;
    int width = 800;
    int height = 600;
    bool visible = false;

    // Visual properties (Qt-style customization beyond Qt's capabilities)
    float borderRadius = 12.0f;
    HPen borderPen = HPen(HColor(80, 80, 80, 255), 1.0f, HPen::Style::SolidLine);
    HColor backgroundColor = HColor(0x23, 0x23, 0x23, 255);

    // Drop shadow properties
    bool dropShadowEnabled = false;
    float dropShadowOffsetX = 0.0f;
    float dropShadowOffsetY = 4.0f;
    float dropShadowBlurRadius = 10.0f;
    HColor dropShadowColor = HColor(0, 0, 0, 128);

    // Custom paint callback
    HWindow::PaintCallback paintCallback;

    // Draggable regions for window move (titlebar-like behavior)
    std::vector<HRect> draggableRegions;
    bool isDragInProgress = false;

    // Central item for layout-based rendering
    HItem* centralItem = nullptr;

    // Padding
    int paddingLeft = 0;
    int paddingTop = 0;
    int paddingRight = 0;
    int paddingBottom = 0;

    // Input focus
    HItem* focusItem = nullptr;
};

} // namespace Ht
