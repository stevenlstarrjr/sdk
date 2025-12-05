#pragma once

#include "HPointF.h"
#include "HSizeF.h"

namespace Ht {

/**
 * @brief HRectF represents a rectangle with floating-point precision
 * Qt Equivalent: QRectF
 * Skia Backend: SkRect
 */
class HRectF {
public:
    // Constructors
    constexpr HRectF() noexcept : m_x(0.0f), m_y(0.0f), m_width(0.0f), m_height(0.0f) {}
    constexpr HRectF(float x, float y, float width, float height) noexcept
        : m_x(x), m_y(y), m_width(width), m_height(height) {}
    constexpr HRectF(const HPointF& topLeft, const HSizeF& size) noexcept
        : m_x(topLeft.x()), m_y(topLeft.y()), m_width(size.width()), m_height(size.height()) {}
    constexpr HRectF(const HPointF& topLeft, const HPointF& bottomRight) noexcept
        : m_x(topLeft.x()), m_y(topLeft.y()),
          m_width(bottomRight.x() - topLeft.x()), m_height(bottomRight.y() - topLeft.y()) {}

    // Accessors
    constexpr float x() const noexcept { return m_x; }
    constexpr float y() const noexcept { return m_y; }
    constexpr float width() const noexcept { return m_width; }
    constexpr float height() const noexcept { return m_height; }

    constexpr void setX(float x) noexcept { m_x = x; }
    constexpr void setY(float y) noexcept { m_y = y; }
    constexpr void setWidth(float width) noexcept { m_width = width; }
    constexpr void setHeight(float height) noexcept { m_height = height; }

    // Edge accessors
    constexpr float left() const noexcept { return m_x; }
    constexpr float top() const noexcept { return m_y; }
    constexpr float right() const noexcept { return m_x + m_width; }
    constexpr float bottom() const noexcept { return m_y + m_height; }

    // Corner accessors
    constexpr HPointF topLeft() const noexcept { return HPointF(m_x, m_y); }
    constexpr HPointF topRight() const noexcept { return HPointF(m_x + m_width, m_y); }
    constexpr HPointF bottomLeft() const noexcept { return HPointF(m_x, m_y + m_height); }
    constexpr HPointF bottomRight() const noexcept { return HPointF(m_x + m_width, m_y + m_height); }
    constexpr HPointF center() const noexcept { return HPointF(m_x + m_width / 2.0f, m_y + m_height / 2.0f); }

    // Size
    constexpr HSizeF size() const noexcept { return HSizeF(m_width, m_height); }

    // Validity checks
    constexpr bool isNull() const noexcept { return m_width == 0.0f && m_height == 0.0f; }
    constexpr bool isEmpty() const noexcept { return m_width <= 0.0f || m_height <= 0.0f; }
    constexpr bool isValid() const noexcept { return m_width >= 0.0f && m_height >= 0.0f; }

    // Containment
    constexpr bool contains(const HPointF& point) const noexcept {
        return point.x() >= m_x && point.x() <= m_x + m_width &&
               point.y() >= m_y && point.y() <= m_y + m_height;
    }

    constexpr bool contains(const HRectF& rect) const noexcept {
        return rect.left() >= left() && rect.right() <= right() &&
               rect.top() >= top() && rect.bottom() <= bottom();
    }

    // Intersection
    constexpr bool intersects(const HRectF& rect) const noexcept {
        return left() < rect.right() && right() > rect.left() &&
               top() < rect.bottom() && bottom() > rect.top();
    }

    constexpr HRectF intersected(const HRectF& rect) const noexcept {
        float l = (m_x > rect.m_x) ? m_x : rect.m_x;
        float t = (m_y > rect.m_y) ? m_y : rect.m_y;
        float r = (m_x + m_width < rect.m_x + rect.m_width) ? m_x + m_width : rect.m_x + rect.m_width;
        float b = (m_y + m_height < rect.m_y + rect.m_height) ? m_y + m_height : rect.m_y + rect.m_height;
        return HRectF(l, t, r - l, b - t);
    }

    // Union
    constexpr HRectF united(const HRectF& rect) const noexcept {
        float l = (m_x < rect.m_x) ? m_x : rect.m_x;
        float t = (m_y < rect.m_y) ? m_y : rect.m_y;
        float r = (m_x + m_width > rect.m_x + rect.m_width) ? m_x + m_width : rect.m_x + rect.m_width;
        float b = (m_y + m_height > rect.m_y + rect.m_height) ? m_y + m_height : rect.m_y + rect.m_height;
        return HRectF(l, t, r - l, b - t);
    }

    // Adjustment
    constexpr void adjust(float dx1, float dy1, float dx2, float dy2) noexcept {
        m_x += dx1;
        m_y += dy1;
        m_width += dx2 - dx1;
        m_height += dy2 - dy1;
    }

    constexpr HRectF adjusted(float dx1, float dy1, float dx2, float dy2) const noexcept {
        return HRectF(m_x + dx1, m_y + dy1, m_width + dx2 - dx1, m_height + dy2 - dy1);
    }

    // Translation
    constexpr void translate(float dx, float dy) noexcept {
        m_x += dx;
        m_y += dy;
    }

    constexpr void translate(const HPointF& offset) noexcept {
        m_x += offset.x();
        m_y += offset.y();
    }

    constexpr HRectF translated(float dx, float dy) const noexcept {
        return HRectF(m_x + dx, m_y + dy, m_width, m_height);
    }

    constexpr HRectF translated(const HPointF& offset) const noexcept {
        return HRectF(m_x + offset.x(), m_y + offset.y(), m_width, m_height);
    }

    // Move
    constexpr void moveTo(float x, float y) noexcept {
        m_x = x;
        m_y = y;
    }

    constexpr void moveTo(const HPointF& position) noexcept {
        m_x = position.x();
        m_y = position.y();
    }

    constexpr void moveCenter(const HPointF& position) noexcept {
        m_x = position.x() - m_width / 2.0f;
        m_y = position.y() - m_height / 2.0f;
    }

    // Comparison
    constexpr bool operator==(const HRectF& other) const noexcept {
        return m_x == other.m_x && m_y == other.m_y &&
               m_width == other.m_width && m_height == other.m_height;
    }

    constexpr bool operator!=(const HRectF& other) const noexcept {
        return !(*this == other);
    }

    // Normalize (ensure positive width/height)
    constexpr HRectF normalized() const noexcept {
        float nx = m_x, ny = m_y, nw = m_width, nh = m_height;
        if (nw < 0.0f) {
            nx += nw;
            nw = -nw;
        }
        if (nh < 0.0f) {
            ny += nh;
            nh = -nh;
        }
        return HRectF(nx, ny, nw, nh);
    }

private:
    float m_x;
    float m_y;
    float m_width;
    float m_height;
};

} // namespace Ht
