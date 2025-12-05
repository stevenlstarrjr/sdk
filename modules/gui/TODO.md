# GUI Module TODO - Wayland Client + Yoga Layout API Mapping

**Version: 0.0.1a**

This document outlines the classes to be created for the gui module, mapping 1:1 to wayland-client protocols and yoga layout engine while following the "Wrap Third-Party Only" principle.

---

## Core Application Classes

### [ ] HGuiApplication
**Wayland Equivalent:** `wl_display` (client-side) + event loop
**Yoga Equivalent:** Layout engine integration
- Application singleton
- Wayland connection management
- Event loop (exec/quit)
- Global registry access
- Screen/output enumeration
- Clipboard integration

### [ ] HEventLoop
**Wayland Equivalent:** `wl_event_loop` wrapper
- Event dispatching
- Timer support
- File descriptor monitoring

---

## Wayland Connection & Registry

### [ ] HWaylandDisplay
**Wayland Equivalent:** `wl_display`
- Wayland server connection
- Roundtrip synchronization
- Error handling
- Flush operations

### [ ] HWaylandRegistry
**Wayland Equivalent:** `wl_registry`
- Global object discovery
- Interface binding
- Version negotiation

### [ ] HWaylandProxy (Base)
**Wayland Equivalent:** `wl_proxy`
- Base class for all Wayland objects
- Event queue management
- Lifecycle management

---

## Window & Surface Classes

### [ ] HWindow
**Wayland Equivalent:** `wl_surface` + XDG shell
**Yoga Equivalent:** Root layout node container
- Top-level application window
- Title, icon, app ID
- Window states (maximized, minimized, fullscreen)
- Resize, move operations
- Close, show, hide
- Rendering integration (provides paint device)
- Layout tree root

### [ ] HSurface
**Wayland Equivalent:** `wl_surface`
- Basic Wayland surface
- Buffer attachment
- Damage reporting
- Frame callbacks
- Transformation (scale, rotation)
- Input region
- Opaque region

### [ ] HSubsurface
**Wayland Equivalent:** `wl_subsurface`
- Nested surface
- Position relative to parent
- Stacking order (above/below)
- Synchronized vs desynchronized mode

---

## XDG Shell (Client-Side)

### [ ] HXdgSurface
**Wayland Equivalent:** `xdg_surface`
- XDG shell surface base
- Window geometry
- Configure acknowledgment

### [ ] HXdgToplevel
**Wayland Equivalent:** `xdg_toplevel`
- Application window (client view)
- Set title, app ID
- Min/max size constraints
- Request maximize, minimize, fullscreen
- Parent windows

### [ ] HXdgPopup
**Wayland Equivalent:** `xdg_popup`
- Popup windows (menus, tooltips)
- Positioning
- Grab support

### [ ] HXdgPositioner
**Wayland Equivalent:** `xdg_positioner`
- Popup positioning rules
- Gravity, anchor
- Constraint adjustment

---

## Input Handling (Client-Side)

### [ ] HInputSeat
**Wayland Equivalent:** `wl_seat`
- Input device aggregation
- Capability queries (keyboard, pointer, touch)

### [ ] HKeyboard
**Wayland Equivalent:** `wl_keyboard`
- Key press/release events
- Keymap handling
- Modifier state
- Repeat info
- Focus enter/leave

### [ ] HPointer
**Wayland Equivalent:** `wl_pointer`
- Mouse/pointer events
- Button press/release
- Motion (absolute position)
- Axis (scroll) events
- Enter/leave surface
- Cursor surface management

### [ ] HTouch
**Wayland Equivalent:** `wl_touch`
- Touch down/up/motion events
- Touch point tracking
- Cancellation

### [ ] HRelativePointer
**Wayland Equivalent:** `zwp_relative_pointer_v1`
- Relative motion for locked pointer
- High-precision input (games, 3D)

### [ ] HPointerConstraints
**Wayland Equivalent:** `zwp_pointer_constraints_v1`
- Lock pointer to surface
- Confine pointer to region

---

## Tablet Input

### [ ] HTabletSeat
**Wayland Equivalent:** `zwp_tablet_seat_v2`
- Tablet device management

### [ ] HTabletTool
**Wayland Equivalent:** `zwp_tablet_tool_v2`
- Pen, eraser, brush
- Pressure, tilt, rotation
- Proximity events

### [ ] HTabletPad
**Wayland Equivalent:** `zwp_tablet_pad_v2`
- Tablet buttons and strips

---

## Text Input & IME (Client-Side)

### [ ] HTextInput
**Wayland Equivalent:** `zwp_text_input_v3`
- Text entry fields
- Input method support
- Pre-edit text
- Commit string
- Content type hints

### [ ] HVirtualKeyboard
**Wayland Equivalent:** `zwp_virtual_keyboard_v1`
- On-screen keyboard
- Generate key events

---

## Clipboard & Data Transfer

### [ ] HClipboard
**Wayland Equivalent:** `wl_data_device`
- Copy/paste operations
- MIME type negotiation
- Data transfer

### [ ] HDataDevice
**Wayland Equivalent:** `wl_data_device`
- Drag-and-drop
- Selection (clipboard)

### [ ] HDataSource
**Wayland Equivalent:** `wl_data_source`
- Provide data for transfer

### [ ] HDataOffer
**Wayland Equivalent:** `wl_data_offer`
- Receive offered data

### [ ] HPrimarySelection
**Wayland Equivalent:** `zwp_primary_selection_device_v1`
- Middle-click paste

### [ ] HDrag
**Wayland Equivalent:** Drag-and-drop abstraction
- Drag source
- Drop target
- Drag icon

---

## Screen & Output

### [ ] HScreen
**Wayland Equivalent:** `wl_output`
- Monitor/display information
- Physical size
- Resolution, scale factor
- Transform (rotation)
- Refresh rate
- Geometry in global space

---

## Buffers & Rendering (Client-Side)

### [ ] HBuffer
**Wayland Equivalent:** `wl_buffer`
- Generic buffer interface
- Shared memory buffers
- DMA-BUF buffers

### [ ] HShmPool
**Wayland Equivalent:** `wl_shm_pool`
- Shared memory allocation
- Buffer creation

### [ ] HLinuxDmabuf
**Wayland Equivalent:** `zwp_linux_dmabuf_v1`
- GPU buffer sharing
- Zero-copy rendering

---

## Cursor Management

### [ ] HCursor
**Wayland Equivalent:** Cursor theme + surface
- Cursor shapes
- Custom cursor images
- Cursor themes
- Hotspot

### [ ] HCursorTheme
**Wayland Equivalent:** `wl_cursor_theme`
- Load cursor theme
- Cursor animation

### [ ] HCursorShape
**Wayland Equivalent:** `wp_cursor_shape_device_v1`
- Set cursor shape by name

---

## Decoration & Presentation

### [ ] HDecoration
**Wayland Equivalent:** `zxdg_decoration_manager_v1`
- Client-side vs server-side decorations
- Decoration mode negotiation

### [ ] HPresentationTime
**Wayland Equivalent:** `wp_presentation`
- Frame timing feedback
- Vsync timing

---

## Fractional Scaling & Viewporter

### [ ] HFractionalScale
**Wayland Equivalent:** `wp_fractional_scale_v1`
- High-DPI fractional scaling
- Preferred scale factor

### [ ] HViewport
**Wayland Equivalent:** `wp_viewport`
- Surface cropping
- Scaling transformation

---

## Idle & Power Management

### [ ] HIdleInhibitor
**Wayland Equivalent:** `zwp_idle_inhibit_manager_v1`
- Prevent screen dimming/locking
- Video playback, presentations

---

## Layout Engine - Yoga Integration

### [ ] HLayout
**Yoga Equivalent:** `YGNodeRef` wrapper
- Flexbox layout engine
- CSS-like layout properties
- Tree-based layout hierarchy

### [ ] HLayoutNode
**Yoga Equivalent:** `YGNode`
- Individual layout node
- Flex properties (direction, wrap, justify, align)
- Dimensions (width, height)
- Position (absolute, relative)
- Margins, padding, border
- Min/max dimensions
- Aspect ratio
- Layout calculation

### [ ] HFlexDirection (enum)
**Yoga Equivalent:** `YGFlexDirection`
- Row, column, row-reverse, column-reverse

### [ ] HJustifyContent (enum)
**Yoga Equivalent:** `YGJustify`
- Flex-start, center, flex-end, space-between, space-around, space-evenly

### [ ] HAlignItems (enum)
**Yoga Equivalent:** `YGAlign`
- Flex-start, center, flex-end, stretch, baseline

### [ ] HAlignSelf (enum)
**Yoga Equivalent:** `YGAlign` (for individual items)

### [ ] HAlignContent (enum)
**Yoga Equivalent:** `YGAlign` (for multi-line)

### [ ] HFlexWrap (enum)
**Yoga Equivalent:** `YGWrap`
- No-wrap, wrap, wrap-reverse

### [ ] HPositionType (enum)
**Yoga Equivalent:** `YGPositionType`
- Relative, absolute

### [ ] HDisplay (enum)
**Yoga Equivalent:** `YGDisplay`
- Flex, none

### [ ] HEdge (enum)
**Yoga Equivalent:** `YGEdge`
- Left, top, right, bottom, start, end, horizontal, vertical, all

### [ ] HLayoutConfig
**Yoga Equivalent:** `YGConfigRef`
- Global layout configuration
- Point scale factor
- Experimental features

---

## Gestures (if applicable)

### [ ] HGestureRecognizer (Base)
- Abstract gesture detection

### [ ] HTapGesture
- Single/double/triple tap

### [ ] HPanGesture
- Drag/swipe

### [ ] HPinchGesture
- Two-finger zoom

### [ ] HRotationGesture
- Two-finger rotation

### [ ] HLongPressGesture
- Press and hold

---

## Utility Classes

### [ ] HPoint
**Yoga/Wayland Equivalent:** Position (x, y)
- Integer or floating-point
- Used for Wayland coordinates

### [ ] HSize
**Yoga/Wayland Equivalent:** Dimensions (width, height)
- Layout dimensions

### [ ] HRect
**Wayland Equivalent:** Window geometry
- Bounding box

### [ ] HMargins
**Yoga Equivalent:** Layout margins
- Top, right, bottom, left

### [ ] HPadding
**Yoga Equivalent:** Layout padding

---

## Native Integration

### [ ] HNativeWindowHandle
**Platform Equivalent:** Platform-specific window handle
- EGL integration
- Vulkan surface creation
- OpenGL context binding

### [ ] HVulkanWaylandContext
**Wayland + Vulkan:** VkSurfaceKHR creation
- Vulkan instance integration
- Swapchain creation

### [ ] HEglWaylandContext
**Wayland + EGL:** EGL surface creation
- OpenGL ES rendering

---

## Implementation Priority

**Phase 1: Core Application & Windowing**
1. HGuiApplication
2. HWaylandDisplay, HWaylandRegistry
3. HSurface, HWindow
4. HXdgSurface, HXdgToplevel
5. HScreen

**Phase 2: Input Handling**
6. HInputSeat, HKeyboard, HPointer, HTouch
7. HCursor, HCursorTheme

**Phase 3: Layout Engine**
8. HLayout, HLayoutNode
9. HLayoutConfig
10. Layout enums (HFlexDirection, HJustifyContent, etc.)

**Phase 4: Advanced Input**
11. HTextInput
12. HClipboard, HDataDevice
13. HTabletSeat, HTabletTool
14. HPointerConstraints, HRelativePointer

**Phase 5: Rendering Integration**
15. HBuffer, HShmPool, HLinuxDmabuf
16. HNativeWindowHandle
17. HVulkanWaylandContext, HEglWaylandContext

**Phase 6: Polish & Features**
18. HXdgPopup, HSubsurface
19. HPresentationTime, HFractionalScale, HViewport
20. HDecoration, HIdleInhibitor
21. Gesture recognizers

---

## Notes

- All classes wrap wayland-client and yoga directly, never internal legacy APIs
- Use RAII for Wayland object lifecycle
- Event-driven architecture with signals/callbacks
- Thread-safe event queue where needed
- Integrate layout engine with window resize/paint events
- Coordinate spaces: surface-local, global, layout-local
- Handle HiDPI scaling throughout
- Support both integer and fractional scaling
- Layout recalculation triggers on size changes
- Efficient incremental layout updates
