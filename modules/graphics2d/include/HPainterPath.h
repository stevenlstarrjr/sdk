#pragma once

#include "HPointF.h"
#include "HRectF.h"
#include <memory>

namespace Ht {

/**
 * @brief HPainterPath represents a vector drawing path
 * Qt Equivalent: QPainterPath
 * Skia Backend: SkPath
 *
 * HPainterPath is a value type that describes complex shapes built from
 * lines and curves. It supports boolean operations and can be rendered
 * using HPainter::drawPath().
 */
class HPainterPath {
public:
    // Constructors
    HPainterPath();
    ~HPainterPath();

    HPainterPath(const HPainterPath& other);
    HPainterPath& operator=(const HPainterPath& other);

    HPainterPath(HPainterPath&& other) noexcept;
    HPainterPath& operator=(HPainterPath&& other) noexcept;

    // Basic state
    bool isEmpty() const;
    void clear();

    // Path construction - move/lines
    void moveTo(float x, float y);
    void moveTo(const HPointF& point);

    void lineTo(float x, float y);
    void lineTo(const HPointF& point);

    // Quadratic Bezier
    void quadTo(float cx, float cy, float x, float y);
    void quadTo(const HPointF& control, const HPointF& endPoint);

    // Cubic Bezier
    void cubicTo(float cx1, float cy1, float cx2, float cy2, float x, float y);
    void cubicTo(const HPointF& control1, const HPointF& control2, const HPointF& endPoint);

    // Close current sub-path
    void closeSubpath();

    // Convenience shape builders
    void addRect(const HRectF& rect);
    void addEllipse(const HRectF& rect);

    // Bounding box
    HRectF boundingRect() const;

    // Boolean operations (return new paths)
    HPainterPath united(const HPainterPath& other) const;
    HPainterPath intersected(const HPainterPath& other) const;
    HPainterPath subtracted(const HPainterPath& other) const;
    HPainterPath xored(const HPainterPath& other) const;

    // Internal Skia access
    struct Impl;
    Impl* impl() const { return m_impl.get(); }

    // Internal helper for Skia integration (HPainter)
    // Returns a const reference to the underlying SkPath.
    // This does not expose Skia types in the public API since the
    // declaration is only visible to implementation files that
    // include Skia headers.
    const void* rawPathHandle() const;

private:
    std::unique_ptr<Impl> m_impl;
};

} // namespace Ht
