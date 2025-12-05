# Graphics2D Module

**Version:** 0.0.1a
**Status:** Phase 1 Complete ✅

Qt-style 2D graphics API wrapping Skia directly.

## Implemented Classes (Phase 1)

### Geometric Primitives
- ✅ `HPoint` / `HPointF` - 2D points (integer/float)
- ✅ `HSize` / `HSizeF` - Dimensions
- ✅ `HRect` / `HRectF` - Rectangles

### Colors & Styles
- ✅ `HColor` - RGBA colors with named constants
- ✅ `HPen` - Line drawing styles
- ✅ `HBrush` - Fill patterns

### Core Graphics
- ✅ `HImage` - Raster images (wraps SkBitmap/SkImage)
  - Load/save PNG, JPEG
  - Pixel manipulation
  - Scaling and copying

- ✅ `HPainter` - 2D drawing API (wraps SkCanvas)
  - Lines, rectangles, ellipses, arcs
  - Polylines, polygons
  - Transformations (translate, scale, rotate)
  - State management (save/restore)

## Examples

- **basic_shapes.cpp** - Demonstrates all Phase 1 features
  - Output: `build/output/basic_shapes.png`

## Building

```bash
mkdir -p build && cd build
cmake ..
make -j$(nproc)
./basic_shapes  # Run example
```

## Architecture

- **Public API:** Clean C++ with no third-party types exposed
- **Backend:** Skia wrapped directly (following "Wrap Third-Party Only" principle)
- **Implementation:** Private pimpl idiom in `src/private/`

## Next Steps (Phase 2)

See `TODO.md` for:
- Text rendering (HFont, HFontMetrics, HTextLayout)
- Gradients (HLinearGradient, HRadialGradient)
- Advanced paths (HPainterPath)
- Transformations (HTransform, HMatrix4x4)
