#pragma once

#include "HApplication.h"
#include "HKeyboard.h"
#include <string>
#include <memory>
#include <vector>

extern "C" {
#include <wayland-client.h>
#include "xdg-shell-client-protocol.h"
#include "cursor-shape-v1-client-protocol.h"
}

namespace Ht {

class HWindow;

struct HApplication::Impl {
    HApplication* q_ptr = nullptr;
    int* argcPtr = nullptr;
    char** argv = nullptr;

    // Metadata
    std::string appName;
    std::string orgName;
    std::string orgDomain;
    std::string appVersion;

    // Wayland globals
    wl_display* display = nullptr;
    wl_registry* registry = nullptr;
    wl_compositor* compositor = nullptr;
    wl_shm* shm = nullptr;
    wl_seat* seat = nullptr;
    xdg_wm_base* xdgWmBase = nullptr;
    
    // Cursor / Pointer
    wl_pointer* pointer = nullptr;
    wp_cursor_shape_manager_v1* cursorShapeManager = nullptr;
    wp_cursor_shape_device_v1* cursorShapeDevice = nullptr;
    double pointerX = 0.0;
    double pointerY = 0.0;
    uint32_t pointerEnterSerial = 0;

    // Keyboard
    std::unique_ptr<HKeyboard> keyboard;

    // State
    bool running = false;
    int exitCode = 0;

    // Application windows
    // For now, simplistic tracking of primary window
    HWindow* primaryWindow = nullptr;
    
    // Hovered item tracking
    void* currentHoveredArea = nullptr; // HMouseArea*

    Impl(int& argc, char** argv);
    ~Impl();

    bool initialize();
    void setupRegistry();
    int runEventLoop();
    void cleanup();
};

} // namespace Ht
