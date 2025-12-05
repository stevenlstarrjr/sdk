# Hultrix Project TODO

**Project:** Hultrix - Modern Wayland Compositor Toolkit
**Last Updated:** 2025-12-04
**Architecture:** Wrap Third-Party Libraries Only (Skia, wlroots, wayland-client, yoga)

---

## Project Overview

Hultrix is a modern compositor toolkit consisting of three core modules:

1. **graphics2d** - 2D graphics engine (wraps Skia)
2. **compositor** - Wayland compositor (wraps wlroots)
3. **gui** - Wayland client + layout (wraps wayland-client + yoga)

Each module follows the **"Wrap Third-Party Only"** principle - never wrapping internal legacy APIs, only external libraries.

---

## Module Status

### ✅ Module: graphics2d (14% Complete)

**Status:** Phase 1 & 2 mostly complete, actively developed
**Progress:** 13/90 classes implemented
**Documentation:** `modules/graphics2d/PROGRESS.md`, `modules/graphics2d/TODO.md`

**Completed:**
- ✅ Geometric primitives (HPoint, HSize, HRect + float variants)
- ✅ Color system (HColor)
- ✅ Drawing attributes (HPen, HBrush)
- ✅ Raster images (HImage with PNG/JPEG support)
- ✅ 2D painter (HPainter - basic drawing + text)
- ✅ Text rendering (HFont, HFontMetrics with manual font loading)

**Working Examples:**
- ✅ `basic_shapes.cpp` - Lines, shapes, polygons
- ✅ `text_rendering.cpp` - Inter Variable font rendering

**Critical Implementation Notes:**
- Font loading uses `SkFontMgr_New_Custom_Data()` (system font manager doesn't work)
- Modern Skia uses `SkPathBuilder`, not direct `SkPath` manipulation
- All Skia types hidden via PImpl pattern

**Next Priority:**
- HPainterPath (vector paths with curves and boolean ops)
- Gradients (HLinearGradient, HRadialGradient, HConicalGradient)
- Transformations (HTransform, HMatrix4x4)

**Dependencies:**
- Skia (from thirdparty/lib64/libskia.a)
- Vulkan, PNG, JPEG, WebP, fontconfig, freetype

---

### 🏗️ Module: compositor (~1% Complete)

**Status:** Foundational classes only, minimal implementation
**Progress:** 1/75 classes implemented
**Documentation:** `modules/compositor/TODO.md`, `modules/compositor/Agents.md`

**Completed:**
- ✅ HDisplay (basic wlroots display wrapper)

**Not Yet Implemented:**
- ❌ HCompositor
- ❌ HOutput
- ❌ HXdgToplevel, HXdgSurface, HXdgPopup
- ❌ HSeat, HKeyboard, HPointer
- ❌ HSurface, HLayerSurface
- ❌ HBackend (DRM, headless, etc.)
- ❌ All rendering integration

**Critical Notes:**
- CMakeLists.txt fixed to use `thirdparty/lib64/libwlroots-0.20.a`
- No examples yet - needs basic compositor example

**Dependencies:**
- wlroots 0.20 (from thirdparty/lib64/)
- wayland-server
- xkbcommon
- pixman

**Next Priority:**
- HCompositor + HBackend (basic compositor setup)
- HOutput (display management)
- HSeat + HKeyboard + HPointer (input handling)
- Basic compositor example that starts wlroots

---

### 🏗️ Module: gui (~1% Complete)

**Status:** Foundational classes only, minimal implementation
**Progress:** 1/80 classes implemented
**Documentation:** `modules/gui/TODO.md`, `modules/gui/Agents.md`

**Completed:**
- ✅ HApplication (basic Wayland client setup)

**Not Yet Implemented:**
- ❌ HWindow
- ❌ HSurface (Wayland surface wrapper)
- ❌ HLayout (yoga integration)
- ❌ Widget system
- ❌ Input handling (HInputSeat, HKeyboard, HPointer)
- ❌ All protocol handlers

**Critical Notes:**
- Needs integration with graphics2d for rendering
- Needs yoga layout engine integration
- No examples yet - needs basic window example

**Dependencies:**
- wayland-client
- wayland-protocols
- xkbcommon
- yoga (Facebook's flexbox layout)

**Next Priority:**
- HWindow + HSurface (basic window creation)
- Integration with graphics2d (render to window)
- HLayout (yoga wrapper for flexbox)
- Basic window example showing rendering

---

## Overall Project Architecture

### Build System
```
Hultrix/
├── CMakeLists.txt (root)
├── modules/
│   ├── graphics2d/
│   │   ├── CMakeLists.txt ✅
│   │   ├── build/ ✅
│   │   └── libgraphics2d.a ✅
│   ├── compositor/
│   │   ├── CMakeLists.txt ✅
│   │   ├── build/ ✅
│   │   └── libhultrix_compositor.a ✅
│   └── gui/
│       ├── CMakeLists.txt ✅
│       ├── build/ ✅
│       └── libhultrix_gui.a ✅
├── thirdparty/
│   ├── include/ (Skia, wlroots headers)
│   └── lib64/ (compiled libraries)
├── assets/
│   └── font/Inter-4.1/InterVariable.ttf ✅
└── projects/
    ├── htinywl/ (compositor project)
    └── lab/ (test projects)
```

### Third-Party Dependencies

**graphics2d:**
- Skia (2D graphics library)
- Vulkan (GPU backend)
- Image codecs: PNG, JPEG, WebP
- Text: fontconfig, freetype

**compositor:**
- wlroots 0.20 (compositor library)
- wayland-server
- xkbcommon (keyboard handling)
- pixman (software rendering)

**gui:**
- wayland-client
- wayland-protocols (xdg-shell, etc.)
- yoga (flexbox layout engine)
- xkbcommon (keyboard handling)

---

## Design Principles

### 1. Wrap Third-Party Only
- ✅ **DO:** Wrap Skia, wlroots, wayland-client, yoga
- ❌ **DON'T:** Wrap our own legacy code or internal APIs

### 2. Private Implementation (PImpl)
- Hide all third-party types from public headers
- Use `src/private/*_p.h` for implementation details
- Never expose `Skia*`, `wlr_*`, or `wl_*` types in public API

### 3. Qt-Style API (graphics2d)
- 1:1 mapping to Qt API where applicable
- camelCase method names
- Value semantics for geometric types

### 4. Modern C++20
- Use constexpr where possible
- Move semantics for performance
- Explicit constructors (no implicit conversions)
- Smart pointers (no raw owning pointers)

---

## Known Issues & Gotchas

### graphics2d Module

1. **Skia Font Manager:**
   - System font manager doesn't work reliably
   - Must use `SkFontMgr_New_Custom_Data()` for manual font loading
   - Required includes: `SkFontMgr_data.h`, `SkSpan.h`

2. **Skia Path API:**
   - Modern Skia uses `SkPathBuilder` instead of direct `SkPath`
   - Call `.detach()` to get the final `SkPath`

3. **Type Ambiguity:**
   - Use explicit `.0f` suffix for float literals
   - Avoid mixing int/float in overloaded function calls

4. **SkFontMetrics:**
   - Fields are plain floats, not `std::optional<float>`
   - Check `!= 0.0f` instead of `.has_value()`

### compositor Module

1. **wlroots Library Path:**
   - Use `thirdparty/lib64/libwlroots-0.20.a`
   - Not in `thirdparty/src/wlroots/build/`

### gui Module

1. **Wayland Protocol Generation:**
   - May need to generate protocol headers from XML
   - Check wayland-scanner usage

---

## Testing Strategy

### Current Approach:
- Using example programs for verification
- Manual visual inspection of output images
- No automated test suite yet

### Future Testing Needs:
- Unit tests for geometric primitives
- Rendering regression tests (image comparison)
- Compositor integration tests
- Window/input handling tests

---

## Immediate Next Steps (Priority Order)

### 1. Complete graphics2d Phase 1
**Priority: High**
- [ ] Implement HPainterPath (vector paths with curves)
- [ ] Add path example (complex shapes, boolean ops)
- [ ] Implement HLine/HLineF, HPolygon/HPolygonF
- [ ] Implement HMargins/HMarginsF

### 2. Start graphics2d Phase 3
**Priority: High**
- [ ] Implement gradient classes (Linear, Radial, Conical)
- [ ] Add gradient example (backgrounds, buttons)
- [ ] Implement HTransform (2D affine transforms)
- [ ] Add transformation example (rotations, scaling)

### 3. Build Compositor Foundation
**Priority: Medium**
- [ ] Implement HCompositor + HBackend
- [ ] Implement HOutput (display management)
- [ ] Implement HSeat + HKeyboard + HPointer
- [ ] Create basic compositor example (launches wlroots)

### 4. Build GUI Foundation
**Priority: Medium**
- [ ] Implement HWindow + HSurface
- [ ] Integrate graphics2d rendering into HWindow
- [ ] Implement HLayout (yoga wrapper)
- [ ] Create basic window example (shows graphics2d rendering)

### 5. Integration Work
**Priority: Medium**
- [ ] Connect compositor to GUI (window management)
- [ ] Connect graphics2d to GUI (window rendering)
- [ ] Create full-stack example (compositor + windows + rendering)

---

## Long-Term Goals

### Phase 4: GPU Acceleration
- HPixmap (GPU-optimized images)
- HVulkanPaintDevice
- Hardware-accelerated compositor rendering

### Phase 5: Advanced Features
- PDF/SVG output (HPdfWriter, HSvgGenerator)
- Color management (HColorSpace)
- Font database (HFontDatabase for system fonts)
- Icon system (HIcon, HIconEngine)
- Advanced text layout (HTextLayout with HarfBuzz)

### Phase 6: Polish & Optimization
- Performance profiling
- Memory usage optimization
- API documentation (Doxygen)
- Tutorial examples
- Developer guide

---

## Documentation Files

### Per-Module Documentation:
- `modules/graphics2d/TODO.md` - Full class list and roadmap
- `modules/graphics2d/PROGRESS.md` - Detailed implementation status ✅
- `modules/graphics2d/Agents.md` - AI agent instructions
- `modules/compositor/TODO.md` - Full class list and roadmap
- `modules/compositor/Agents.md` - AI agent instructions
- `modules/gui/TODO.md` - Full class list and roadmap
- `modules/gui/Agents.md` - AI agent instructions

### Project Documentation:
- `Agents.md` - Overall architecture and principles
- `README.md` - Project overview (needs update)
- `TODO.md` - This file

---

## For Future AI Agents

### Getting Started:
1. Read `Agents.md` for architecture principles
2. Read module-specific `PROGRESS.md` for current status
3. Check module `TODO.md` for planned classes
4. Follow "Wrap Third-Party Only" principle strictly

### Before Implementing:
1. Check if class already exists in module
2. Identify the third-party API to wrap
3. Use PImpl pattern for complex classes
4. Never expose third-party types in public headers
5. Create example to verify implementation

### Common Patterns:
- Geometric types: Header-only or simple source files
- Complex classes: PImpl with `src/private/*Impl.h`
- Skia access: `impl()->skObject` for internal use only
- Qt compatibility: Match Qt API signatures where possible

### Build Commands:
```bash
# graphics2d module
cd modules/graphics2d/build
cmake .. && make -j$(nproc)
./basic_shapes
./text_rendering

# compositor module
cd modules/compositor/build
cmake .. && make -j$(nproc)

# gui module
cd modules/gui/build
cmake .. && make -j$(nproc)
```

---

**End of Project TODO**
