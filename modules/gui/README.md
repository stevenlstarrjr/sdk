# GUI Module

**Version:** 0.0.1a
**Status:** Initial Setup ✅

Wayland client GUI framework wrapping wayland-client and yoga layout engine.

## Implemented Classes

### Core Application
- ✅ `HApplication` - GUI application lifecycle (wraps wl_display client-side)
  - Wayland connection management
  - Event loop execution
  - Global registry handling
  - Application metadata (name, version, organization)

### Windows
- 🔄 `HWindow` - Top-level window (QWindow analog)
  - Creates `wl_surface`
  - Attaches `xdg_surface` / `xdg_toplevel`
  - Handles XDG ping/pong via `xdg_wm_base`
  - Basic API for title and show/hide (empty commit)

## Architecture

- **Public API:** Clean C++ with no third-party types exposed
- **Backend:** wayland-client + yoga layout wrapped directly
- **Implementation:** Private pimpl idiom in `src/private/`
- **Protocol Generation:** xdg-shell protocols generated at build time

## Building

```bash
mkdir -p build && cd build
cmake ..
make -j$(nproc)
```

## Dependencies

- wayland-client
- wayland-cursor
- xkbcommon
- yoga layout (from thirdparty)
- wayland-protocols (for xdg-shell generation)

## Next Steps

See `TODO.md` for the full class list:
- HWindow - Application windows
- HSurface - Wayland surfaces
- HXdgToplevel, HXdgPopup - Window types
- HKeyboard, HPointer, HTouch - Input handling
- HLayout, HLayoutNode - Flexbox layout engine
- HClipboard - Data transfer
- 70+ more classes...
