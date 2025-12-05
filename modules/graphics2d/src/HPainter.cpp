#include "HPainter.h"
#include "private/HPainterImpl.h"
#include "HPainterPath.h"
#include "HGradient.h"
#include "HRegion.h"
#include "HPicture.h"
#include "HPaintDevice.h"
#include "private/HImageImpl.h"
#include "private/HFontImpl.h"
#include "HImage.h"
#include "HFont.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkPaint.h"
#include "include/core/SkPath.h"
#include "include/core/SkPathBuilder.h"
#include "include/core/SkTextBlob.h"
#include "include/core/SkFontMetrics.h"
#include "include/core/SkMaskFilter.h"
#include "include/core/SkBlurTypes.h"
#include "include/effects/SkGradientShader.h"

namespace Ht {

// Impl helper functions
HPainter::Impl::Impl() {
    strokePaint.setStyle(SkPaint::kStroke_Style);
    strokePaint.setAntiAlias(true);
    fillPaint.setStyle(SkPaint::kFill_Style);
    fillPaint.setAntiAlias(true);
    textPaint.setStyle(SkPaint::kFill_Style);
    textPaint.setAntiAlias(true);
    fillPaint.setStyle(SkPaint::kFill_Style);
}

SkPaint::Cap HPainter::Impl::toSkCap(HPen::CapStyle cap) {
    switch (cap) {
        case HPen::CapStyle::FlatCap: return SkPaint::kButt_Cap;
        case HPen::CapStyle::SquareCap: return SkPaint::kSquare_Cap;
        case HPen::CapStyle::RoundCap: return SkPaint::kRound_Cap;
        default: return SkPaint::kButt_Cap;
    }
}

SkPaint::Join HPainter::Impl::toSkJoin(HPen::JoinStyle join) {
    switch (join) {
        case HPen::JoinStyle::MiterJoin: return SkPaint::kMiter_Join;
        case HPen::JoinStyle::BevelJoin: return SkPaint::kBevel_Join;
        case HPen::JoinStyle::RoundJoin: return SkPaint::kRound_Join;
        default: return SkPaint::kMiter_Join;
    }
}

void HPainter::Impl::applyPenStyle(SkPaint& paint, HPen::Style style) {
    // For now, we'll implement basic styles
    // TODO: Implement dash patterns for DashLine, DotLine, etc.
    if (style == HPen::Style::NoPen) {
        paint.setStrokeWidth(0);
    }
}

void HPainter::Impl::updateStrokePaint() {
    strokePaint.setColor(currentPen.color().rgba());
    strokePaint.setStrokeWidth(currentPen.width());
    strokePaint.setStrokeCap(toSkCap(currentPen.capStyle()));
    strokePaint.setStrokeJoin(toSkJoin(currentPen.joinStyle()));
    applyPenStyle(strokePaint, currentPen.style());
}

void HPainter::Impl::updateFillPaint() {
    if (hasGradientFill) {
        // Gradient shader is already installed; do not overwrite it here.
        return;
    }

    if (currentBrush.style() != HBrush::Style::NoBrush) {
        fillPaint.setShader(nullptr);
        fillPaint.setColor(currentBrush.color().rgba());
    } else {
        fillPaint.setShader(nullptr);
    }
}

void HPainter::Impl::updateTextPaint() {
    textPaint.setColor(currentPen.color().rgba());
}

void HPainter::Impl::updateBlurEffect() {
    if (blurEnabled && blurRadius > 0.0f) {
        // Apply blur mask filter to the fill paint
        fillPaint.setMaskFilter(SkMaskFilter::MakeBlur(SkBlurStyle::kNormal_SkBlurStyle, blurRadius));
    } else {
        // Remove blur mask filter
        fillPaint.setMaskFilter(nullptr);
    }
}

// HPainter implementation
HPainter::HPainter() : m_impl(std::make_unique<Impl>()) {
    m_impl->updateStrokePaint();
    m_impl->updateFillPaint();
}

HPainter::HPainter(HImage* image) : m_impl(std::make_unique<Impl>()) {
    begin(image);
}

HPainter::~HPainter() {
    end();
}

bool HPainter::begin(HImage* image) {
    if (!image || image->isNull()) {
        return false;
    }

    m_impl->canvas = image->impl()->getCanvas();
    if (!m_impl->canvas) {
        return false;
    }

    m_impl->active = true;
    m_impl->targetImage = image;
    return true;
}

bool HPainter::begin(HPaintDevice* device) {
    if (!device) {
        return false;
    }

    HImage* image = device->asImage();
    if (image) {
        return begin(image);
    }

    // Fallback: attempt to use a backend surface handle (e.g., GPU SkSurface)
    const void* surfaceHandle = device->rawSurfaceHandle();
    if (!surfaceHandle) {
        return false;
    }

    SkSurface* surface = static_cast<SkSurface*>(const_cast<void*>(surfaceHandle));
    if (!surface) {
        return false;
    }

    m_impl->canvas = surface->getCanvas();
    if (!m_impl->canvas) {
        return false;
    }

    m_impl->active = true;
    m_impl->targetImage = nullptr;
    return true;
}

bool HPainter::end() {
    if (m_impl->active && m_impl->targetImage) {
        m_impl->targetImage->impl()->updateImageFromBitmap();
    }
    m_impl->active = false;
    m_impl->canvas = nullptr;
    m_impl->targetImage = nullptr;
    return true;
}

bool HPainter::isActive() const {
    return m_impl->active;
}

void HPainter::save() {
    if (m_impl->canvas) {
        m_impl->canvas->save();
    }
}

void HPainter::restore() {
    if (m_impl->canvas) {
        m_impl->canvas->restore();
    }
}

const HPen& HPainter::pen() const {
    return m_impl->currentPen;
}

void HPainter::setPen(const HPen& pen) {
    m_impl->currentPen = pen;
    m_impl->updateStrokePaint();
    m_impl->updateTextPaint();
}

void HPainter::setPen(const HColor& color) {
    m_impl->currentPen.setColor(color);
    m_impl->updateStrokePaint();
    m_impl->updateTextPaint();
}

void HPainter::setPen(HPen::Style style) {
    m_impl->currentPen.setStyle(style);
    m_impl->updateStrokePaint();
    m_impl->updateTextPaint();
}

const HBrush& HPainter::brush() const {
    return m_impl->currentBrush;
}

void HPainter::setBrush(const HBrush& brush) {
    m_impl->currentBrush = brush;
    m_impl->hasGradientFill = false;
    m_impl->updateFillPaint();
}

void HPainter::setBrush(const HColor& color) {
    m_impl->currentBrush.setColor(color);
    m_impl->currentBrush.setStyle(HBrush::Style::SolidPattern);
    m_impl->hasGradientFill = false;
    m_impl->updateFillPaint();
}

void HPainter::setBrush(HBrush::Style style) {
    m_impl->currentBrush.setStyle(style);
    m_impl->hasGradientFill = false;
    m_impl->updateFillPaint();
}

const HColor& HPainter::background() const {
    return m_impl->backgroundColor;
}

void HPainter::setBackground(const HColor& color) {
    m_impl->backgroundColor = color;
}

bool HPainter::antialiasing() const {
    return m_impl->strokePaint.isAntiAlias();
}

void HPainter::setAntialiasing(bool enable) {
    m_impl->strokePaint.setAntiAlias(enable);
    m_impl->fillPaint.setAntiAlias(enable);
}

// Blur effect
void HPainter::setBlurRadius(float radius) {
    m_impl->blurRadius = radius;
    m_impl->updateBlurEffect();
}

float HPainter::blurRadius() const {
    return m_impl->blurRadius;
}

void HPainter::setBlurEnabled(bool enabled) {
    m_impl->blurEnabled = enabled;
    m_impl->updateBlurEffect();
}

bool HPainter::blurEnabled() const {
    return m_impl->blurEnabled;
}

void HPainter::setBrush(const HLinearGradient& gradient) {
    if (!m_impl->canvas) {
        // Still record the gradient; it will be used once begin() is called.
    }

    m_impl->hasGradientFill = true;
    // Ensure fill is enabled even if the previous brush style was NoBrush
    m_impl->currentBrush.setStyle(HBrush::Style::SolidPattern);

    // Build Skia shader from gradient definition
    const auto& stops = gradient.stops();
    if (stops.empty()) {
        // Fallback to solid brush color if no stops are defined
        m_impl->hasGradientFill = false;
        m_impl->updateFillPaint();
        return;
    }

    std::vector<SkColor> colors;
    std::vector<SkScalar> positions;
    colors.reserve(stops.size());
    positions.reserve(stops.size());

    for (const auto& stop : stops) {
        colors.push_back(stop.color.rgba());
        positions.push_back(stop.position);
    }

    SkPoint pts[2] = {
        SkPoint::Make(gradient.start().x(), gradient.start().y()),
        SkPoint::Make(gradient.end().x(), gradient.end().y())
    };

    SkTileMode tileMode = SkTileMode::kClamp;
    switch (gradient.spread()) {
        case HGradient::Spread::Pad:    tileMode = SkTileMode::kClamp;  break;
        case HGradient::Spread::Repeat: tileMode = SkTileMode::kRepeat; break;
        case HGradient::Spread::Reflect:tileMode = SkTileMode::kMirror; break;
    }

    sk_sp<SkShader> shader = SkGradientShader::MakeLinear(
        pts,
        colors.data(),
        positions.data(),
        static_cast<int>(colors.size()),
        tileMode);

    if (shader) {
        m_impl->fillPaint.setShader(shader);
    } else {
        m_impl->hasGradientFill = false;
        m_impl->updateFillPaint();
    }
}

void HPainter::setBrush(const HRadialGradient& gradient) {
    m_impl->hasGradientFill = true;
    m_impl->currentBrush.setStyle(HBrush::Style::SolidPattern);

    const auto& stops = gradient.stops();
    if (stops.empty() || gradient.radius() <= 0.0f) {
        m_impl->hasGradientFill = false;
        m_impl->updateFillPaint();
        return;
    }

    std::vector<SkColor> colors;
    std::vector<SkScalar> positions;
    colors.reserve(stops.size());
    positions.reserve(stops.size());

    for (const auto& stop : stops) {
        colors.push_back(stop.color.rgba());
        positions.push_back(stop.position);
    }

    SkPoint center = SkPoint::Make(gradient.center().x(), gradient.center().y());

    SkTileMode tileMode = SkTileMode::kClamp;
    switch (gradient.spread()) {
        case HGradient::Spread::Pad:    tileMode = SkTileMode::kClamp;  break;
        case HGradient::Spread::Repeat: tileMode = SkTileMode::kRepeat; break;
        case HGradient::Spread::Reflect:tileMode = SkTileMode::kMirror; break;
    }

    sk_sp<SkShader> shader = SkGradientShader::MakeRadial(
        center,
        gradient.radius(),
        colors.data(),
        positions.data(),
        static_cast<int>(colors.size()),
        tileMode);

    if (shader) {
        m_impl->fillPaint.setShader(shader);
    } else {
        m_impl->hasGradientFill = false;
        m_impl->updateFillPaint();
    }
}

void HPainter::setBrush(const HConicalGradient& gradient) {
    m_impl->hasGradientFill = true;
    m_impl->currentBrush.setStyle(HBrush::Style::SolidPattern);

    const auto& stops = gradient.stops();
    if (stops.empty()) {
        m_impl->hasGradientFill = false;
        m_impl->updateFillPaint();
        return;
    }

    std::vector<SkColor> colors;
    std::vector<SkScalar> positions;
    colors.reserve(stops.size());
    positions.reserve(stops.size());

    for (const auto& stop : stops) {
        colors.push_back(stop.color.rgba());
        positions.push_back(stop.position);
    }

    HPointF c = gradient.center();

    sk_sp<SkShader> shader = SkGradientShader::MakeSweep(
        c.x(),
        c.y(),
        colors.data(),
        positions.data(),
        static_cast<int>(colors.size()));

    if (shader) {
        m_impl->fillPaint.setShader(shader);
    } else {
        m_impl->hasGradientFill = false;
        m_impl->updateFillPaint();
    }
}

// Drawing operations - Lines
void HPainter::drawLine(int x1, int y1, int x2, int y2) {
    drawLine(static_cast<float>(x1), static_cast<float>(y1),
             static_cast<float>(x2), static_cast<float>(y2));
}

void HPainter::drawLine(const HPoint& p1, const HPoint& p2) {
    drawLine(p1.x(), p1.y(), p2.x(), p2.y());
}

void HPainter::drawLine(float x1, float y1, float x2, float y2) {
    if (m_impl->canvas && m_impl->currentPen.style() != HPen::Style::NoPen) {
        m_impl->canvas->drawLine(x1, y1, x2, y2, m_impl->strokePaint);
    }
}

void HPainter::drawLine(const HPointF& p1, const HPointF& p2) {
    drawLine(p1.x(), p1.y(), p2.x(), p2.y());
}

void HPainter::drawLine(const HLine& line) {
    drawLine(line.x1(), line.y1(), line.x2(), line.y2());
}

void HPainter::drawLine(const HLineF& line) {
    drawLine(line.x1(), line.y1(), line.x2(), line.y2());
}

// Drawing operations - Rectangles
void HPainter::drawRect(int x, int y, int width, int height) {
    drawRect(static_cast<float>(x), static_cast<float>(y),
             static_cast<float>(width), static_cast<float>(height));
}

void HPainter::drawRect(const HRect& rect) {
    drawRect(rect.x(), rect.y(), rect.width(), rect.height());
}

void HPainter::drawRect(float x, float y, float width, float height) {
    if (!m_impl->canvas) return;

    SkRect skRect = SkRect::MakeXYWH(x, y, width, height);

    // Fill first if brush is set
    if (m_impl->currentBrush.style() != HBrush::Style::NoBrush) {
        m_impl->canvas->drawRect(skRect, m_impl->fillPaint);
    }

    // Then stroke if pen is set
    if (m_impl->currentPen.style() != HPen::Style::NoPen) {
        m_impl->canvas->drawRect(skRect, m_impl->strokePaint);
    }
}

void HPainter::drawRect(const HRectF& rect) {
    drawRect(rect.x(), rect.y(), rect.width(), rect.height());
}

void HPainter::fillRect(int x, int y, int width, int height, const HColor& color) {
    fillRect(static_cast<float>(x), static_cast<float>(y),
             static_cast<float>(width), static_cast<float>(height), color);
}

void HPainter::fillRect(const HRect& rect, const HColor& color) {
    fillRect(rect.x(), rect.y(), rect.width(), rect.height(), color);
}

void HPainter::fillRect(float x, float y, float width, float height, const HColor& color) {
    if (m_impl->canvas) {
        SkPaint paint;
        paint.setColor(color.rgba());
        paint.setStyle(SkPaint::kFill_Style);
        m_impl->canvas->drawRect(SkRect::MakeXYWH(x, y, width, height), paint);
    }
}

void HPainter::fillRect(const HRectF& rect, const HColor& color) {
    fillRect(rect.x(), rect.y(), rect.width(), rect.height(), color);
}

// Drawing operations - Ellipses
void HPainter::drawEllipse(int x, int y, int width, int height) {
    drawEllipse(static_cast<float>(x), static_cast<float>(y),
                static_cast<float>(width), static_cast<float>(height));
}

void HPainter::drawEllipse(const HRect& rect) {
    drawEllipse(rect.x(), rect.y(), rect.width(), rect.height());
}

void HPainter::drawEllipse(float x, float y, float width, float height) {
    if (!m_impl->canvas) return;

    SkRect skRect = SkRect::MakeXYWH(x, y, width, height);

    // Fill first if brush is set
    if (m_impl->currentBrush.style() != HBrush::Style::NoBrush) {
        m_impl->canvas->drawOval(skRect, m_impl->fillPaint);
    }

    // Then stroke if pen is set
    if (m_impl->currentPen.style() != HPen::Style::NoPen) {
        m_impl->canvas->drawOval(skRect, m_impl->strokePaint);
    }
}

void HPainter::drawEllipse(const HRectF& rect) {
    drawEllipse(rect.x(), rect.y(), rect.width(), rect.height());
}

void HPainter::drawEllipse(const HPointF& center, float rx, float ry) {
    drawEllipse(center.x() - rx, center.y() - ry, rx * 2, ry * 2);
}

// Drawing operations - Arcs
void HPainter::drawArc(const HRect& rect, int startAngle, int spanAngle) {
    drawArc(rect.toRectF(), startAngle, spanAngle);
}

void HPainter::drawArc(const HRectF& rect, int startAngle, int spanAngle) {
    if (!m_impl->canvas) return;

    SkRect skRect = SkRect::MakeXYWH(rect.x(), rect.y(), rect.width(), rect.height());
    float startDegrees = startAngle / 16.0f; // Qt uses 1/16th degree units
    float sweepDegrees = spanAngle / 16.0f;

    if (m_impl->currentPen.style() != HPen::Style::NoPen) {
        m_impl->canvas->drawArc(skRect, startDegrees, sweepDegrees, false, m_impl->strokePaint);
    }
}

// Drawing operations - Points
void HPainter::drawPoint(int x, int y) {
    drawPoint(static_cast<float>(x), static_cast<float>(y));
}

void HPainter::drawPoint(const HPoint& point) {
    drawPoint(point.x(), point.y());
}

void HPainter::drawPoint(float x, float y) {
    if (m_impl->canvas && m_impl->currentPen.style() != HPen::Style::NoPen) {
        m_impl->canvas->drawPoint(x, y, m_impl->strokePaint);
    }
}

void HPainter::drawPoint(const HPointF& point) {
    drawPoint(point.x(), point.y());
}

void HPainter::drawPoints(const HPoint* points, int pointCount) {
    for (int i = 0; i < pointCount; ++i) {
        drawPoint(points[i]);
    }
}

void HPainter::drawPoints(const std::vector<HPoint>& points) {
    drawPoints(points.data(), static_cast<int>(points.size()));
}

void HPainter::drawPoints(const HPointF* points, int pointCount) {
    for (int i = 0; i < pointCount; ++i) {
        drawPoint(points[i]);
    }
}

void HPainter::drawPoints(const std::vector<HPointF>& points) {
    drawPoints(points.data(), static_cast<int>(points.size()));
}

// Drawing operations - Polylines
void HPainter::drawPolyline(const HPoint* points, int pointCount) {
    if (!m_impl->canvas || pointCount < 2 || m_impl->currentPen.style() == HPen::Style::NoPen) {
        return;
    }

    SkPathBuilder builder;
    builder.moveTo(points[0].x(), points[0].y());
    for (int i = 1; i < pointCount; ++i) {
        builder.lineTo(points[i].x(), points[i].y());
    }
    m_impl->canvas->drawPath(builder.detach(), m_impl->strokePaint);
}

void HPainter::drawPolyline(const std::vector<HPoint>& points) {
    drawPolyline(points.data(), static_cast<int>(points.size()));
}

void HPainter::drawPolyline(const HPointF* points, int pointCount) {
    if (!m_impl->canvas || pointCount < 2 || m_impl->currentPen.style() == HPen::Style::NoPen) {
        return;
    }

    SkPathBuilder builder;
    builder.moveTo(points[0].x(), points[0].y());
    for (int i = 1; i < pointCount; ++i) {
        builder.lineTo(points[i].x(), points[i].y());
    }
    m_impl->canvas->drawPath(builder.detach(), m_impl->strokePaint);
}

void HPainter::drawPolyline(const std::vector<HPointF>& points) {
    drawPolyline(points.data(), static_cast<int>(points.size()));
}

// Drawing operations - Polygons
void HPainter::drawPolygon(const HPoint* points, int pointCount) {
    if (!m_impl->canvas || pointCount < 3) {
        return;
    }

    SkPathBuilder builder;
    builder.moveTo(points[0].x(), points[0].y());
    for (int i = 1; i < pointCount; ++i) {
        builder.lineTo(points[i].x(), points[i].y());
    }
    builder.close();
    SkPath path = builder.detach();

    // Fill first if brush is set
    if (m_impl->currentBrush.style() != HBrush::Style::NoBrush) {
        m_impl->canvas->drawPath(path, m_impl->fillPaint);
    }

    // Then stroke if pen is set
    if (m_impl->currentPen.style() != HPen::Style::NoPen) {
        m_impl->canvas->drawPath(path, m_impl->strokePaint);
    }
}

void HPainter::drawPolygon(const std::vector<HPoint>& points) {
    drawPolygon(points.data(), static_cast<int>(points.size()));
}

void HPainter::drawPolygon(const HPointF* points, int pointCount) {
    if (!m_impl->canvas || pointCount < 3) {
        return;
    }

    SkPathBuilder builder;
    builder.moveTo(points[0].x(), points[0].y());
    for (int i = 1; i < pointCount; ++i) {
        builder.lineTo(points[i].x(), points[i].y());
    }
    builder.close();
    SkPath path = builder.detach();

    // Fill first if brush is set
    if (m_impl->currentBrush.style() != HBrush::Style::NoBrush) {
        m_impl->canvas->drawPath(path, m_impl->fillPaint);
    }

    // Then stroke if pen is set
    if (m_impl->currentPen.style() != HPen::Style::NoPen) {
        m_impl->canvas->drawPath(path, m_impl->strokePaint);
    }
}

void HPainter::drawPolygon(const std::vector<HPointF>& points) {
    drawPolygon(points.data(), static_cast<int>(points.size()));
}

// Drawing operations - Rounded rectangles
void HPainter::drawRoundedRect(const HRect& rect, float xRadius, float yRadius) {
    drawRoundedRect(rect.toRectF(), xRadius, yRadius);
}

void HPainter::drawRoundedRect(const HRectF& rect, float xRadius, float yRadius) {
    if (!m_impl->canvas) return;

    SkRect skRect = SkRect::MakeXYWH(rect.x(), rect.y(), rect.width(), rect.height());

    // Fill first if brush is set
    if (m_impl->currentBrush.style() != HBrush::Style::NoBrush) {
        m_impl->canvas->drawRoundRect(skRect, xRadius, yRadius, m_impl->fillPaint);
    }

    // Then stroke if pen is set
    if (m_impl->currentPen.style() != HPen::Style::NoPen) {
        m_impl->canvas->drawRoundRect(skRect, xRadius, yRadius, m_impl->strokePaint);
    }
}

// Fill operations
void HPainter::fillEllipse(const HRect& rect, const HColor& color) {
    fillEllipse(rect.toRectF(), color);
}

void HPainter::fillEllipse(const HRectF& rect, const HColor& color) {
    if (m_impl->canvas) {
        SkPaint paint;
        paint.setColor(color.rgba());
        paint.setStyle(SkPaint::kFill_Style);
        paint.setAntiAlias(true);
        SkRect skRect = SkRect::MakeXYWH(rect.x(), rect.y(), rect.width(), rect.height());
        m_impl->canvas->drawOval(skRect, paint);
    }
}

// Clearing
void HPainter::eraseRect(const HRect& rect) {
    eraseRect(rect.toRectF());
}

void HPainter::eraseRect(const HRectF& rect) {
    fillRect(rect, m_impl->backgroundColor);
}

// Transformation
void HPainter::translate(float dx, float dy) {
    if (m_impl->canvas) {
        m_impl->canvas->translate(dx, dy);
    }
}

void HPainter::translate(const HPointF& offset) {
    translate(offset.x(), offset.y());
}

void HPainter::scale(float sx, float sy) {
    if (m_impl->canvas) {
        m_impl->canvas->scale(sx, sy);
    }
}

void HPainter::rotate(float angle) {
    if (m_impl->canvas) {
        m_impl->canvas->rotate(angle);
    }
}

void HPainter::resetTransform() {
    if (m_impl->canvas) {
        m_impl->canvas->resetMatrix();
    }
}

void HPainter::setTransform(const HTransform& transform) {
    if (!m_impl->canvas) {
        return;
    }

    SkMatrix m;
    m.setAll(transform.m11(), transform.m12(), transform.m13(),
             transform.m21(), transform.m22(), transform.m23(),
             transform.m31(), transform.m32(), transform.m33());
    m_impl->canvas->setMatrix(m);
}

void HPainter::setWorldTransform(const HTransform& transform, bool combine) {
    if (!m_impl->canvas) {
        return;
    }

    SkMatrix m;
    m.setAll(transform.m11(), transform.m12(), transform.m13(),
             transform.m21(), transform.m22(), transform.m23(),
             transform.m31(), transform.m32(), transform.m33());

    if (combine) {
        m_impl->canvas->concat(m);
    } else {
        m_impl->canvas->setMatrix(m);
    }
}

void HPainter::setClipRect(const HRect& rect, bool replace) {
    if (!m_impl->canvas) {
        return;
    }

    SkRect r = SkRect::MakeXYWH(
        static_cast<SkScalar>(rect.x()),
        static_cast<SkScalar>(rect.y()),
        static_cast<SkScalar>(rect.width()),
        static_cast<SkScalar>(rect.height()));

    SkClipOp op = SkClipOp::kIntersect;
    bool doAA = true;

    if (replace) {
        m_impl->canvas->clipRect(r, op, doAA);
    } else {
        m_impl->canvas->clipRect(r, op, doAA);
    }
}

void HPainter::setClipRegion(const HRegion& region, bool replace) {
    if (!m_impl->canvas || !region.impl()) {
        return;
    }

    const auto* handle = static_cast<const SkRegion*>(region.rawHandle());
    if (!handle) {
        return;
    }
    const SkRegion& skRegion = *handle;
    SkClipOp op = SkClipOp::kIntersect;
    // SkCanvas::clipRegion always intersects; "replace" can be modeled by
    // drawing on a fresh canvas or by saveLayer, which is beyond this thin wrapper.
    (void)replace;
    m_impl->canvas->clipRegion(skRegion, op);
}

// Text rendering
const HFont& HPainter::font() const {
    return m_impl->currentFont;
}

void HPainter::setFont(const HFont& font) {
    m_impl->currentFont = font;
    m_impl->updateTextPaint();
}

void HPainter::drawText(int x, int y, const std::string& text) {
    drawText(static_cast<float>(x), static_cast<float>(y), text);
}

void HPainter::drawText(const HPoint& point, const std::string& text) {
    drawText(point.x(), point.y(), text);
}

void HPainter::drawText(float x, float y, const std::string& text) {
    if (!m_impl->canvas || text.empty() || !m_impl->currentFont.isValid()) {
        return;
    }

    const SkFont& skFont = m_impl->currentFont.impl()->font;

    // Create text blob for better performance
    sk_sp<SkTextBlob> blob = SkTextBlob::MakeFromText(
        text.c_str(), text.length(), skFont, SkTextEncoding::kUTF8);

    if (blob) {
        m_impl->canvas->drawTextBlob(blob, x, y, m_impl->textPaint);
    }
}

void HPainter::drawText(const HPointF& point, const std::string& text) {
    drawText(point.x(), point.y(), text);
}

void HPainter::drawText(const HRect& rect, int /*flags*/, const std::string& text) {
    drawText(rect.toRectF(), text);
}

void HPainter::drawText(const HRectF& rect, const std::string& text) {
    // Simple left-aligned, top-baseline text in rect
    // TODO: Support alignment flags
    if (!m_impl->canvas || text.empty() || !m_impl->currentFont.isValid()) {
        return;
    }

    const SkFont& skFont = m_impl->currentFont.impl()->font;
    SkFontMetrics metrics;
    skFont.getMetrics(&metrics);

    // Position text at top of rect plus ascent
    float baselineY = rect.y() - metrics.fAscent;

    drawText(rect.x(), baselineY, text);
}

float HPainter::textWidth(const std::string& text) const {
    if (!m_impl->currentFont.isValid()) {
        return 0.0f;
    }

    const SkFont& skFont = m_impl->currentFont.impl()->font;
    return skFont.measureText(text.c_str(), text.length(), SkTextEncoding::kUTF8);
}

HRectF HPainter::textBoundingRect(const std::string& text) const {
    if (!m_impl->currentFont.isValid()) {
        return HRectF();
    }

    const SkFont& skFont = m_impl->currentFont.impl()->font;
    SkRect bounds;
    skFont.measureText(text.c_str(), text.length(), SkTextEncoding::kUTF8, &bounds);

    return HRectF(bounds.x(), bounds.y(), bounds.width(), bounds.height());
}

void HPainter::drawPath(const HPainterPath& path) {
    if (!m_impl->canvas || path.isEmpty()) {
        return;
    }

    const auto* handle = static_cast<const SkPath*>(path.rawPathHandle());
    if (!handle) {
        return;
    }
    const SkPath& skPath = *handle;

    // Fill first if brush is set
    if (m_impl->currentBrush.style() != HBrush::Style::NoBrush) {
        m_impl->canvas->drawPath(skPath, m_impl->fillPaint);
    }

    // Then stroke if pen is set
    if (m_impl->currentPen.style() != HPen::Style::NoPen) {
        m_impl->canvas->drawPath(skPath, m_impl->strokePaint);
    }
}

void HPainter::drawPicture(const HPicture& picture, const HPointF& offset) {
    if (!m_impl->canvas) {
        return;
    }

    const auto* handle = static_cast<const SkPicture*>(picture.rawHandle());
    if (!handle) {
        return;
    }

    m_impl->canvas->save();
    m_impl->canvas->translate(offset.x(), offset.y());
    m_impl->canvas->drawPicture(handle);
    m_impl->canvas->restore();
}

// Image rendering
void HPainter::drawImage(const HPoint& point, const HImage& image) {
    drawImage(static_cast<float>(point.x()), static_cast<float>(point.y()), image);
}

void HPainter::drawImage(const HPointF& point, const HImage& image) {
    drawImage(point.x(), point.y(), image);
}

void HPainter::drawImage(int x, int y, const HImage& image) {
    drawImage(static_cast<float>(x), static_cast<float>(y), image);
}

void HPainter::drawImage(float x, float y, const HImage& image) {
    if (!m_impl->canvas || image.isNull()) {
        return;
    }

    const sk_sp<SkImage>& skImage = image.impl()->image;
    if (!skImage) {
        return;
    }

    // Use default sampling (bilinear filtering)
    SkSamplingOptions sampling(SkFilterMode::kLinear);
    m_impl->canvas->drawImage(skImage, x, y, sampling, nullptr);
}

void HPainter::drawImage(const HRect& target, const HImage& image) {
    drawImage(target.toRectF(), image);
}

void HPainter::drawImage(const HRectF& target, const HImage& image) {
    if (!m_impl->canvas || image.isNull()) {
        return;
    }

    const sk_sp<SkImage>& skImage = image.impl()->image;
    if (!skImage) {
        return;
    }

    SkRect srcRect = SkRect::MakeWH(static_cast<float>(image.width()),
                                     static_cast<float>(image.height()));
    SkRect dstRect = SkRect::MakeXYWH(target.x(), target.y(), target.width(), target.height());

    // Use default sampling (bilinear filtering)
    SkSamplingOptions sampling(SkFilterMode::kLinear);
    m_impl->canvas->drawImageRect(skImage, srcRect, dstRect, sampling, nullptr,
                                   SkCanvas::kStrict_SrcRectConstraint);
}

} // namespace Ht
