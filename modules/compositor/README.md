# Compositor Module

**Version:** 0.0.1a
**Status:** Initial Setup ✅

Wayland compositor SDK wrapping wlroots directly.

## Implemented Classes

### Core Display
- ✅ `HWaylandCompositor` - Wayland display server (wraps wl_display)
- 🔄 `HWaylandOutput` - Output wrapper (wlr_output) - skeleton getters only

### Surfaces & Shell
- 🔄 `HWaylandSurface` - Basic surface wrapper (wlr_surface) - width/height/mapped
- 🔄 `HWaylandXdgShell` - XDG shell extension wrapper (wlr_xdg_shell)
- 🔄 `HWaylandXdgSurface` - Base XDG surface wrapper (wlr_xdg_surface)
- 🔄 `HWaylandXdgToplevel` - Toplevel window wrapper (wlr_xdg_toplevel)

### Input
- 🔄 `HWaylandSeat` - Input seat wrapper (wlr_seat) - capabilities only
- 🔄 `HWaylandKeyboard` - Keyboard wrapper (wlr_keyboard) - validity only
- 🔄 `HWaylandPointer` - Pointer wrapper (wlr_pointer) - validity only
  - Socket creation and binding
  - Event loop management
  - Client connection handling
  - Serial generation

## Architecture

- **Public API:** Clean C++ with no third-party types exposed
- **Backend:** wlroots wrapped directly
- **Implementation:** Private pimpl idiom in `src/private/`

## Building

```bash
mkdir -p build && cd build
cmake ..
make -j$(nproc)
```

## Dependencies

- wlroots 0.20 (from thirdparty)
- wayland-server
- libdrm, pixman, EGL, gbm

## Next Steps

See `TODO.md` for the full class list:
- HCompositor - Main compositor entry point
- HBackend, HRenderer - Hardware abstraction
- HOutput - Display management
- HSurface - Surface handling
- HXdgShell, HXdgToplevel - Window management
- HSeat, HKeyboard, HPointer - Input handling
- 70+ more classes...
