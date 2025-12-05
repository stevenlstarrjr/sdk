#pragma once

#include "HPoint.h"
#include "HPointF.h"
#include "HRect.h"
#include "HRectF.h"
#include "HColor.h"
#include "HPen.h"
#include "HBrush.h"
#include "HPainterPath.h"
#include "HLine.h"
#include "HPolygon.h"
#include "HTransform.h"
#include "HRegion.h"
#include <memory>
#include <vector>
#include <string>

namespace Ht {

class HImage;
class HFont;
class HLinearGradient;
class HRadialGradient;
class HConicalGradient;
class HPicture;
class HPaintDevice;

/**
 * @brief HPainter provides drawing operations
 * Qt Equivalent: QPainter
 * Skia Backend: SkCanvas
 */
class HPainter {
public:
    // Constructors
    HPainter();
    explicit HPainter(HImage* image);
    ~HPainter();

    // Non-copyable
    HPainter(const HPainter&) = delete;
    HPainter& operator=(const HPainter&) = delete;

    // Begin/end painting
    bool begin(HImage* image);
    bool begin(HPaintDevice* device);
    bool end();
    bool isActive() const;

    // State management
    void save();
    void restore();

    // Pen and brush
    const HPen& pen() const;
    void setPen(const HPen& pen);
    void setPen(const HColor& color);
    void setPen(HPen::Style style);

    const HBrush& brush() const;
    void setBrush(const HBrush& brush);
    void setBrush(const HColor& color);
    void setBrush(HBrush::Style style);
    void setBrush(const HLinearGradient& gradient);
    void setBrush(const HRadialGradient& gradient);
    void setBrush(const HConicalGradient& gradient);

    // Background
    const HColor& background() const;
    void setBackground(const HColor& color);

    // Anti-aliasing
    bool antialiasing() const;
    void setAntialiasing(bool enable);

    // Blur effect (for drop shadows, etc.)
    void setBlurRadius(float radius);
    float blurRadius() const;
    void setBlurEnabled(bool enabled);
    bool blurEnabled() const;

    // Drawing operations - Lines
    void drawLine(int x1, int y1, int x2, int y2);
    void drawLine(const HPoint& p1, const HPoint& p2);
    void drawLine(float x1, float y1, float x2, float y2);
    void drawLine(const HPointF& p1, const HPointF& p2);
    void drawLine(const HLine& line);
    void drawLine(const HLineF& line);

    // Drawing operations - Rectangles
    void drawRect(int x, int y, int width, int height);
    void drawRect(const HRect& rect);
    void drawRect(float x, float y, float width, float height);
    void drawRect(const HRectF& rect);

    void fillRect(int x, int y, int width, int height, const HColor& color);
    void fillRect(const HRect& rect, const HColor& color);
    void fillRect(float x, float y, float width, float height, const HColor& color);
    void fillRect(const HRectF& rect, const HColor& color);

    // Drawing operations - Ellipses/Circles
    void drawEllipse(int x, int y, int width, int height);
    void drawEllipse(const HRect& rect);
    void drawEllipse(float x, float y, float width, float height);
    void drawEllipse(const HRectF& rect);
    void drawEllipse(const HPointF& center, float rx, float ry);

    // Drawing operations - Arcs
    void drawArc(const HRect& rect, int startAngle, int spanAngle);
    void drawArc(const HRectF& rect, int startAngle, int spanAngle);

    // Drawing operations - Points
    void drawPoint(int x, int y);
    void drawPoint(const HPoint& point);
    void drawPoint(float x, float y);
    void drawPoint(const HPointF& point);

    void drawPoints(const HPoint* points, int pointCount);
    void drawPoints(const std::vector<HPoint>& points);
    void drawPoints(const HPointF* points, int pointCount);
    void drawPoints(const std::vector<HPointF>& points);

    // Drawing operations - Polylines
    void drawPolyline(const HPoint* points, int pointCount);
    void drawPolyline(const std::vector<HPoint>& points);
    void drawPolyline(const HPointF* points, int pointCount);
    void drawPolyline(const std::vector<HPointF>& points);

    // Drawing operations - Polygons
    void drawPolygon(const HPoint* points, int pointCount);
    void drawPolygon(const std::vector<HPoint>& points);
    void drawPolygon(const HPointF* points, int pointCount);
    void drawPolygon(const std::vector<HPointF>& points);

    // Drawing operations - Rounded rectangles
    void drawRoundedRect(const HRect& rect, float xRadius, float yRadius);
    void drawRoundedRect(const HRectF& rect, float xRadius, float yRadius);

    // Fill operations
    void fillEllipse(const HRect& rect, const HColor& color);
    void fillEllipse(const HRectF& rect, const HColor& color);

    // Clearing
    void eraseRect(const HRect& rect);
    void eraseRect(const HRectF& rect);

    // Transformation
    void translate(float dx, float dy);
    void translate(const HPointF& offset);
    void scale(float sx, float sy);
    void rotate(float angle); // degrees
    void resetTransform();
    void setTransform(const HTransform& transform);
    void setWorldTransform(const HTransform& transform, bool combine = false);

    // Clipping
    void setClipRect(const HRect& rect, bool replace = false);
    void setClipRegion(const HRegion& region, bool replace = false);

    // Text rendering
    const HFont& font() const;
    void setFont(const HFont& font);

    void drawText(int x, int y, const std::string& text);
    void drawText(const HPoint& point, const std::string& text);
    void drawText(float x, float y, const std::string& text);
    void drawText(const HPointF& point, const std::string& text);

    void drawText(const HRect& rect, int flags, const std::string& text);
    void drawText(const HRectF& rect, const std::string& text);

    // Path rendering
    void drawPath(const HPainterPath& path);

    // Picture rendering
    void drawPicture(const HPicture& picture, const HPointF& offset = HPointF(0.0f, 0.0f));

    // Text measurement (using current font)
    float textWidth(const std::string& text) const;
    HRectF textBoundingRect(const std::string& text) const;

    // Internal Skia access
    struct Impl;
    Impl* impl() const { return m_impl.get(); }

private:
    std::unique_ptr<Impl> m_impl;
};

} // namespace Ht
