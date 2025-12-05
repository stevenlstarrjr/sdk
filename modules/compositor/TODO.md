# Compositor Module TODO - wlroots API Mapping

**Version: 0.0.1a**

This document outlines the classes to be created for the compositor module, mapping 1:1 to wlroots API while following the "Wrap Third-Party Only" principle.

---

## Core Compositor Classes

### [ ] HCompositor
**wlroots Equivalent:** `wlr_compositor` + `wlr_server`
- Main compositor instance
- Event loop management (exec/quit)
- Global coordinator for all compositor objects
- Backend initialization
- Renderer setup

### [ ] HWaylandCompositor
**Qt Equivalent:** `QWaylandCompositor`
**wlroots Equivalent:** `wl_display`
- Wayland display server
- Socket management
- Client connection handling
- Event loop integration

### [ ] HBackend
**wlroots Equivalent:** `wlr_backend`
- Hardware abstraction layer
- DRM, X11, Wayland, headless backends
- Multi-backend support
- Auto backend detection

### [ ] HRenderer
**wlroots Equivalent:** `wlr_renderer`
- GPU rendering abstraction
- Vulkan, OpenGL ES, Pixman backends
- Texture management
- Render pass coordination

### [ ] HAllocator
**wlroots Equivalent:** `wlr_allocator`
- Buffer allocation
- DRM buffer management
- Shared memory buffers

---

## Output Management

### [ ] HWaylandOutput
**Qt Equivalent:** `QWaylandOutput`
**wlroots Equivalent:** `wlr_output`
- Physical display/monitor
- Mode setting (resolution, refresh rate)
- Transform (rotation, scaling)
- Damage tracking
- Frame callbacks
- Adaptive sync (VRR)

### [ ] HOutputLayout
**wlroots Equivalent:** `wlr_output_layout`
- Multi-monitor arrangement
- Coordinate space mapping
- Output positioning

### [ ] HOutputMode
**wlroots Equivalent:** `wlr_output_mode`
- Resolution and refresh rate configuration

### [ ] HOutputState
**wlroots Equivalent:** `wlr_output_state`
- Pending output configuration
- Atomic state updates

---

## Surface Management

### [ ] HSurface
**wlroots Equivalent:** `wlr_surface`
- Basic Wayland surface
- Buffer attachment
- Damage tracking
- Frame callbacks
- Subsurface support

### [ ] HSubsurface
**wlroots Equivalent:** `wlr_subsurface`
- Nested surface within parent surface
- Position and stacking order

### [ ] HSurfaceRole
**wlroots Equivalent:** Surface role concept
- XDG, layer-shell, cursor roles

---

## XDG Shell (Application Windows)

### [ ] HXdgShell
**wlroots Equivalent:** `wlr_xdg_shell`
- XDG shell protocol implementation
- Surface management

### [ ] HXdgSurface
**wlroots Equivalent:** `wlr_xdg_surface`
- Base XDG surface
- Configure events
- Ack configure

### [ ] HXdgToplevel
**wlroots Equivalent:** `wlr_xdg_toplevel`
- Application window
- Maximize, minimize, fullscreen states
- Resize, move operations
- Title, app ID
- Parent-child relationships

### [ ] HXdgPopup
**wlroots Equivalent:** `wlr_xdg_popup`
- Context menus, tooltips
- Positioning relative to parent
- Grab handling

### [ ] HXdgPositioner
**wlroots Equivalent:** `xdg_positioner`
- Popup positioning logic
- Constraint resolution

---

## Layer Shell (Desktop Components)

### [ ] HLayerShell
**wlroots Equivalent:** `wlr_layer_shell_v1`
- Layer shell protocol (backgrounds, panels, overlays)

### [ ] HLayerSurface
**wlroots Equivalent:** `wlr_layer_surface_v1`
- Layered surface (background, bottom, top, overlay)
- Anchoring and margins
- Exclusive zones
- Keyboard interactivity

---

## Input Management

### [ ] HSeat
### [ ] HWaylandSeat
**Qt Equivalent:** `QWaylandSeat`
**wlroots Equivalent:** `wlr_seat`
- Input device group (keyboard, pointer, touch)
- Focus management
- Capability advertisement
- Selection (clipboard) handling

### [ ] HKeyboard
### [ ] HWaylandKeyboard
**Qt Equivalent:** `QWaylandKeyboard`
**wlroots Equivalent:** `wlr_keyboard`
- Keyboard device
- Keymap configuration
- Key events
- Modifiers state
- Repeat rate

### [ ] HPointer
### [ ] HWaylandPointer
**Qt Equivalent:** `QWaylandPointer`
**wlroots Equivalent:** `wlr_pointer`
- Pointer/mouse device
- Motion events
- Button events
- Axis (scroll) events

### [ ] HCursor
**wlroots Equivalent:** `wlr_cursor`
- Unified cursor across outputs
- Cursor image management
- Warping and constraints

### [ ] HCursorShape
**wlroots Equivalent:** `wlr_cursor_shape_manager_v1`
- Cursor theme and shape management

### [ ] HTouch
**wlroots Equivalent:** `wlr_touch`
- Touch input device
- Touch down/up/motion events
- Multi-touch support

### [ ] HTablet
**wlroots Equivalent:** `wlr_tablet_tool`, `wlr_tablet_pad`
- Graphics tablet support
- Pen, eraser, brush tools
- Pressure, tilt, rotation

### [ ] HSwitch
**wlroots Equivalent:** `wlr_switch`
- Lid switch, tablet mode switch

---

## Input Method & Text Input

### [ ] HTextInput
**wlroots Equivalent:** `wlr_text_input_v3`
- Text input protocol (IME support)
- Pre-edit strings

### [ ] HInputMethod
**wlroots Equivalent:** `wlr_input_method_v2`
- Input method manager
- Virtual keyboard

### [ ] HVirtualKeyboard
**wlroots Equivalent:** `wlr_virtual_keyboard_v1`
- Software-generated keyboard events

---

## XWayland Support

### [ ] HXWayland
**wlroots Equivalent:** `wlr_xwayland`
- X11 compatibility layer
- X server management

### [ ] HXWaylandSurface
**wlroots Equivalent:** `wlr_xwayland_surface`
- X11 window wrapped as Wayland surface
- X11 properties (class, title, etc.)

---

## Data Transfer & Clipboard

### [ ] HDataDevice
**wlroots Equivalent:** `wlr_data_device_manager`
- Clipboard and drag-and-drop

### [ ] HDataSource
**wlroots Equivalent:** `wlr_data_source`
- Data provider

### [ ] HDataOffer
**wlroots Equivalent:** Part of data device protocol
- Data receiver

### [ ] HClipboard
**wlroots Equivalent:** Clipboard abstraction over data device
- Copy/paste operations
- MIME type handling

### [ ] HPrimarySelection
**wlroots Equivalent:** `wlr_primary_selection_v1`
- Middle-click paste (X11-style)

### [ ] HDragIcon
**wlroots Equivalent:** `wlr_drag_icon`
- Visual feedback during drag operations

---

## Output & Damage Management

### [ ] HSceneGraph
**wlroots Equivalent:** `wlr_scene`
- High-level scene graph API
- Automatic damage tracking
- Render optimization

### [ ] HSceneNode
**wlroots Equivalent:** `wlr_scene_node`
- Base scene node

### [ ] HSceneTree
**wlroots Equivalent:** `wlr_scene_tree`
- Hierarchical scene organization

### [ ] HSceneRect
**wlroots Equivalent:** `wlr_scene_rect`
- Solid color rectangle

### [ ] HSceneBuffer
**wlroots Equivalent:** `wlr_scene_buffer`
- Textured quad from buffer

### [ ] HDamageRing
**wlroots Equivalent:** `wlr_damage_ring`
- Frame damage accumulation
- Age-based damage tracking

---

## Presentation & Timing

### [ ] HPresentation
**wlroots Equivalent:** `wlr_presentation`
- Presentation timing protocol
- Frame feedback

### [ ] HIdleNotify
**wlroots Equivalent:** `wlr_idle_notifier_v1`
- User idle detection

### [ ] HIdleInhibit
**wlroots Equivalent:** `wlr_idle_inhibit_v1`
- Prevent idle (e.g., during video playback)

---

## Pointer Constraints & Relative Pointer

### [ ] HPointerConstraints
**wlroots Equivalent:** `wlr_pointer_constraints_v1`
- Lock or confine pointer to region

### [ ] HPointerConstraint
**wlroots Equivalent:** `wlr_pointer_constraint_v1`
- Individual constraint

### [ ] HRelativePointer
**wlroots Equivalent:** `wlr_relative_pointer_manager_v1`
- Raw relative motion (for games, 3D apps)

---

## Output & Screen Capture

### [ ] HScreencopy
**wlroots Equivalent:** `wlr_screencopy_manager_v1`
- Screenshot and screen recording

### [ ] HExportDmabuf
**wlroots Equivalent:** `wlr_export_dmabuf_manager_v1`
- DMA-BUF export for efficient capture

---

## Session Management

### [ ] HSession
**wlroots Equivalent:** `wlr_session`
- Session control (VT switching)
- Device access permissions

### [ ] HSessionLock
**wlroots Equivalent:** `wlr_session_lock_v1`
- Screen locking protocol

---

## Foreign Toplevel Management

### [ ] HForeignToplevelManager
**wlroots Equivalent:** `wlr_foreign_toplevel_manager_v1`
- External window list access (for taskbars)

### [ ] HForeignToplevel
**wlroots Equivalent:** `wlr_foreign_toplevel_handle_v1`
- Individual window handle for external control

---

## Output Power Management

### [ ] HOutputPower
**wlroots Equivalent:** `wlr_output_power_manager_v1`
- DPMS control (display on/off)

---

## Viewporter & Fractional Scale

### [ ] HViewporter
**wlroots Equivalent:** `wlr_viewporter`
- Cropping and scaling surfaces

### [ ] HFractionalScale
**wlroots Equivalent:** `wlr_fractional_scale_manager_v1`
- High-DPI fractional scaling

---

## Buffers & Textures

### [ ] HBuffer
**wlroots Equivalent:** `wlr_buffer`
- Generic buffer interface
- DMA-BUF, SHM buffers

### [ ] HTexture
**wlroots Equivalent:** `wlr_texture`
- GPU texture
- Upload from buffer

### [ ] HRenderPass
**wlroots Equivalent:** `wlr_render_pass`
- Modern rendering API
- Command buffer style

---

## Geometry & Utilities

### [ ] HBox (if not using external lib)
**wlroots Equivalent:** `wlr_box`
- Integer rectangle
- Intersection, union operations

### [ ] HFBox
**wlroots Equivalent:** `wlr_fbox`
- Floating-point rectangle

### [ ] HRegion (if different from graphics2d)
**wlroots Equivalent:** `pixman_region32_t`
- Pixel region operations

---

## Security & Sandboxing

### [ ] HSecurityContext
**wlroots Equivalent:** `wlr_security_context_manager_v1`
- Sandbox context identification

---

## Linux DRM/KMS Integration

### [ ] HDrmLease
**wlroots Equivalent:** `wlr_drm_lease_v1`
- Direct display access (VR, direct mode)

---

## Implementation Priority

**Phase 1: Core Compositor Foundation**
1. HWaylandCompositor
2. HBackend
3. HRenderer, HAllocator
4. HCompositor
5. HOutput, HOutputLayout
6. HSurface

**Phase 2: Basic Window Management**
7. HXdgShell, HXdgSurface, HXdgToplevel, HXdgPopup
8. HSeat, HKeyboard, HPointer, HCursor

**Phase 3: Input & Interaction**
9. HTouch, HTablet
10. HTextInput, HVirtualKeyboard
11. HPointerConstraints, HRelativePointer

**Phase 4: Desktop Shell Features**
12. HLayerShell, HLayerSurface
13. HClipboard, HDataDevice
14. HForeignToplevelManager

**Phase 5: Advanced Features**
15. HSceneGraph (scene API)
16. HXWayland (X11 compatibility)
17. HScreencopy, HPresentation
18. HSessionLock, HOutputPower

---

## Notes

- All classes wrap wlroots directly, never internal legacy APIs
- Use RAII for resource management
- Event-driven architecture with callbacks
- Thread-safe where appropriate
- Follow wlroots lifecycle and ownership semantics
- Private implementation idiom for ABI stability
- Coordinate spaces: output-local, layout-global, surface-local
