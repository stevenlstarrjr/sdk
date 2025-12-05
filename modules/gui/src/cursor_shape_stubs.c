#include <wayland-client-protocol.h>

// Stub interface required by cursor-shape-v1 protocol C file.
// We don't use tablet tools yet, but the generated code references
// zwp_tablet_tool_v2_interface, so provide a minimal definition.
const struct wl_interface zwp_tablet_tool_v2_interface = {
    "zwp_tablet_tool_v2",
    2,
    0, NULL,
    0, NULL
};

