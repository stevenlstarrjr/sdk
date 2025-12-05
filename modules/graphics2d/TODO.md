# Graphics2D Module TODO - Qt API Mapping

**Version: 0.0.1a**

This document outlines the classes to be created for the graphics2d module, mapping 1:1 to Qt's graphics API while wrapping Skia directly (following the "Wrap Third-Party Only" principle).

---

## Core Painting Classes

### [x] HPainter
**Qt Equivalent:** `QPainter`
**Skia Backend:** `SkCanvas`
- Primary drawing interface
- State management (save/restore)
- Drawing primitives (lines, rects, ellipses, arcs, paths)
- Text rendering
- Image drawing
- Transformation stack
- Clipping operations
- Composition modes

### [x] HPaintDevice (Abstract Base)
**Qt Equivalent:** `QPaintDevice`
**Skia Backend:** `SkSurface` + device context
- Abstract interface for paint targets
- Provides access to HPainter
- Resolution/DPI information

### [ ] HPaintEngine (Internal)
**Qt Equivalent:** `QPaintEngine`
**Skia Backend:** Direct `SkCanvas` operations
- Backend-specific rendering implementation
- Typically internal, abstracts rasterizer vs GPU

---

## Image & Pixmap Classes

### [x] HImage
**Qt Equivalent:** `QImage`
**Skia Backend:** `SkImage` + `SkBitmap`
- Pixel-based image storage
- Format conversion
- Direct pixel access
- Load/save operations (PNG, JPEG, etc.)
- Scaling and transformations
- Raster rendering target

### [ ] HPixmap
**Qt Equivalent:** `QPixmap`
**Skia Backend:** `SkImage` (GPU-optimized)
- Optimized for screen drawing
- Hardware acceleration support
- Conversion to/from HImage

### [ ] HBitmap
**Qt Equivalent:** `QBitmap`
**Skia Backend:** `SkBitmap` (1-bit depth)
- Monochrome images
- Mask operations

---

## Geometric Primitives (Value Types)

### [x] HPoint
**Qt Equivalent:** `QPoint`
**Skia Backend:** `SkIPoint`
- Integer point (x, y)

### [x] HPointF
**Qt Equivalent:** `QPointF`
**Skia Backend:** `SkPoint`
- Floating-point point (x, y)

### [x] HSize
**Qt Equivalent:** `QSize`
**Skia Backend:** `SkISize`
- Integer size (width, height)

### [x] HSizeF
**Qt Equivalent:** `QSizeF`
**Skia Backend:** `SkSize`
- Floating-point size (width, height)

### [x] HRect
**Qt Equivalent:** `QRect`
**Skia Backend:** `SkIRect`
- Integer rectangle

### [x] HRectF
**Qt Equivalent:** `QRectF`
**Skia Backend:** `SkRect`
- Floating-point rectangle

### [x] HLine
**Qt Equivalent:** `QLine`
- Integer line segment

### [x] HLineF
**Qt Equivalent:** `QLineF`
- Floating-point line segment

### [x] HPolygon
**Qt Equivalent:** `QPolygon`
**Skia Backend:** `SkPath`
- Integer polygon

### [x] HPolygonF
**Qt Equivalent:** `QPolygonF`
**Skia Backend:** `SkPath`
- Floating-point polygon

### [x] HMargins
**Qt Equivalent:** `QMargins`
- Margins (left, top, right, bottom)

### [x] HMarginsF
**Qt Equivalent:** `QMarginsF`
- Floating-point margins

---

## Path & Region Classes

### [x] HPainterPath
**Qt Equivalent:** `QPainterPath`
**Skia Backend:** `SkPath`
- Vector path construction
- Cubic/quadratic curves
- Boolean path operations
- Path stroking/filling
- Bounding rectangle calculations

### [x] HRegion
**Qt Equivalent:** `QRegion`
**Skia Backend:** `SkRegion`
- Integer-based clipping regions
- Boolean region operations
- Region combination

---

## Color & Gradient Classes

### [x] HColor
**Qt Equivalent:** `QColor`
**Skia Backend:** `SkColor`, `SkColor4f`
- RGB/RGBA color representation
- HSV/HSL conversions
- Named colors
- Alpha blending

### [ ] HRgb / HRgba
**Qt Equivalent:** `QRgb` (typedef)
- Raw color values

### [x] HGradient (Abstract Base)
**Qt Equivalent:** `QGradient`
**Skia Backend:** `SkShader`
- Gradient stops
- Spread modes
- Color interpolation

### [x] HLinearGradient
**Qt Equivalent:** `QLinearGradient`
**Skia Backend:** `SkGradientShader::MakeLinear`

### [x] HRadialGradient
**Qt Equivalent:** `QRadialGradient`
**Skia Backend:** `SkGradientShader::MakeRadial`

### [x] HConicalGradient
**Qt Equivalent:** `QConicalGradient`
**Skia Backend:** `SkGradientShader::MakeSweep`

---

## Drawing Attributes

### [x] HPen
**Qt Equivalent:** `QPen`
**Skia Backend:** `SkPaint` (stroke style)
- Line width
- Line style (solid, dashed, dotted)
- Cap style
- Join style
- Dash pattern
- Color/brush

### [x] HBrush
**Qt Equivalent:** `QBrush`
**Skia Backend:** `SkPaint` (fill style) + `SkShader`
- Solid color fills
- Gradient fills
- Pattern/texture fills
- Fill styles

---

## Text Rendering Classes

### [x] HFont
**Qt Equivalent:** `QFont`
**Skia Backend:** `SkFont` + `SkTypeface`
- Font family
- Point size/pixel size
- Weight, style (italic, oblique)
- Stretch
- Kerning, hinting

### [x] HFontMetrics
**Qt Equivalent:** `QFontMetrics`
**Skia Backend:** `SkFontMetrics`
- Ascent, descent, leading
- Text bounding boxes
- Character widths

### [ ] HFontMetricsF
**Qt Equivalent:** `QFontMetricsF`
- Floating-point font metrics

### [ ] HFontInfo
**Qt Equivalent:** `QFontInfo`
- Query actual font properties

### [ ] HFontDatabase
**Qt Equivalent:** `QFontDatabase`
**Skia Backend:** `SkFontMgr`
- System font enumeration
- Font loading

### [ ] HStaticText
**Qt Equivalent:** `QStaticText`
**Skia Backend:** `SkTextBlob`
- Pre-laid-out text for efficient repeated rendering

### [ ] HGlyphRun
**Qt Equivalent:** `QGlyphRun`
**Skia Backend:** `SkTextBlob` internals
- Raw glyph positioning

### [ ] HTextLayout
**Qt Equivalent:** `QTextLayout`
- Text shaping and layout
- Line breaking

### [ ] HTextLine
**Qt Equivalent:** `QTextLine`
- Single line of laid-out text

---

## Transformation Classes

### [x] HTransform
**Qt Equivalent:** `QTransform`
**Skia Backend:** `SkMatrix`
- Affine transformations (2D)
- Rotation, scaling, translation, shearing
- Matrix composition
- Perspective transformations (3x3 matrix)

### [ ] HMatrix4x4
**Qt Equivalent:** `QMatrix4x4`
**Skia Backend:** `SkM44`
- 4x4 transformation matrices
- 3D transformations

---

## Special Effects & Filters

### [ ] HPixelFormat
**Qt Equivalent:** `QPixelFormat`
**Skia Backend:** `SkColorType` + `SkAlphaType`
- Pixel layout description

### [ ] HColorSpace
**Qt Equivalent:** `QColorSpace`
**Skia Backend:** `SkColorSpace`
- Color space management (sRGB, Display P3, etc.)

### [ ] HColorTransform
**Qt Equivalent:** `QColorTransform`
- Color space conversions

---

## Painting & Composition

### [ ] HBlendMode (enum)
**Qt Equivalent:** `QPainter::CompositionMode`
**Skia Backend:** `SkBlendMode`
- Porter-Duff modes
- Additional blend modes

### [ ] HPaintEvent
**Qt Equivalent:** `QPaintEvent`
- Paint event information

---

## Picture Recording

### [x] HPicture
**Qt Equivalent:** `QPicture`
**Skia Backend:** `SkPicture`
- Records and replays paint commands
- Serialization

### [x] HPictureRecorder
**Qt Equivalent:** Internal to `QPicture`
**Skia Backend:** `SkPictureRecorder`
- Records drawing commands into HPicture

---

## Icon & Cursor

### [ ] HIcon
**Qt Equivalent:** `QIcon`
- Multiple sizes/states
- Theme integration

### [ ] HIconEngine
**Qt Equivalent:** `QIconEngine`
- Custom icon rendering

### [ ] HCursor (if in scope)
**Qt Equivalent:** `QCursor`
- Cursor shapes and custom cursors

---

## OpenGL/Vulkan Integration

### [ ] HOpenGLPaintDevice
**Qt Equivalent:** `QOpenGLPaintDevice`
**Skia Backend:** `GrDirectContext` + `SkSurface` (OpenGL backend)

### [ ] HVulkanPaintDevice
**Qt Equivalent:** N/A (Qt uses QVulkanWindow)
**Skia Backend:** `GrDirectContext` + `SkSurface` (Vulkan backend)

### [x] HRasterPaintDevice
**Qt Equivalent:** N/A (implicit in QImage)
**Skia Backend:** `SkSurface::MakeRaster` (CPU raster paint device)

---

## PDF & Vector Output

### [ ] HPdfWriter
**Qt Equivalent:** `QPdfWriter`
**Skia Backend:** `SkDocument::MakePDF`
- PDF generation

### [ ] HSvgGenerator
**Qt Equivalent:** `QSvgGenerator`
**Skia Backend:** `SkSVGCanvas` (if available)
- SVG output

---

## Additional Utilities

### [ ] HPageSize
**Qt Equivalent:** `QPageSize`
- Standard page sizes

### [ ] HPageLayout
**Qt Equivalent:** `QPageLayout`
- Page orientation, margins

---

## Implementation Priority

**Phase 1: Core Value Types & Basic Painting**
1. Geometric primitives (HPoint, HPointF, HRect, HRectF, HSize, HSizeF) ✅
2. HColor ✅
3. HPen, HBrush ✅
4. HPainter (basic operations) ✅
5. HImage (raster target) ✅
6. HPainterPath ✅

**Phase 2: Text Rendering**
7. HFont, HFontMetrics
8. HStaticText / HTextLayout

**Phase 3: Advanced Features**
9. Gradients (HLinearGradient, HRadialGradient, HConicalGradient)
10. HTransform, HMatrix4x4
11. HRegion
12. HPicture / HPictureRecorder

**Phase 4: GPU & Windowing**
13. HPixmap
14. HVulkanPaintDevice / HOpenGLPaintDevice
15. Integration with HWindow

**Phase 5: Extended Features**
16. PDF/SVG output
17. HIcon, HFontDatabase
18. Color spaces

---

## Notes

- All classes should follow strict value semantics where appropriate (especially geometric types)
- Use explicit constructors and avoid implicit conversions
- Provide both integer and floating-point variants for geometric types
- Ensure const-correctness throughout
- Implement move semantics for performance
- Maintain binary compatibility considerations (private implementation idiom where needed)
- All Skia wrapping should be direct, never wrapping our own legacy APIs
