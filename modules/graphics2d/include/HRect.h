#pragma once

#include "HPoint.h"
#include "HSize.h"

namespace Ht {

class HRectF;

/**
 * @brief HRect represents a rectangle with integer precision
 * Qt Equivalent: QRect
 * Skia Backend: SkIRect
 */
class HRect {
public:
    // Constructors
    constexpr HRect() noexcept : m_x(0), m_y(0), m_width(0), m_height(0) {}
    constexpr HRect(int x, int y, int width, int height) noexcept
        : m_x(x), m_y(y), m_width(width), m_height(height) {}
    constexpr HRect(const HPoint& topLeft, const HSize& size) noexcept
        : m_x(topLeft.x()), m_y(topLeft.y()), m_width(size.width()), m_height(size.height()) {}
    constexpr HRect(const HPoint& topLeft, const HPoint& bottomRight) noexcept
        : m_x(topLeft.x()), m_y(topLeft.y()),
          m_width(bottomRight.x() - topLeft.x()), m_height(bottomRight.y() - topLeft.y()) {}

    // Accessors
    constexpr int x() const noexcept { return m_x; }
    constexpr int y() const noexcept { return m_y; }
    constexpr int width() const noexcept { return m_width; }
    constexpr int height() const noexcept { return m_height; }

    constexpr void setX(int x) noexcept { m_x = x; }
    constexpr void setY(int y) noexcept { m_y = y; }
    constexpr void setWidth(int width) noexcept { m_width = width; }
    constexpr void setHeight(int height) noexcept { m_height = height; }

    // Edge accessors
    constexpr int left() const noexcept { return m_x; }
    constexpr int top() const noexcept { return m_y; }
    constexpr int right() const noexcept { return m_x + m_width - 1; }
    constexpr int bottom() const noexcept { return m_y + m_height - 1; }

    // Corner accessors
    constexpr HPoint topLeft() const noexcept { return HPoint(m_x, m_y); }
    constexpr HPoint topRight() const noexcept { return HPoint(m_x + m_width - 1, m_y); }
    constexpr HPoint bottomLeft() const noexcept { return HPoint(m_x, m_y + m_height - 1); }
    constexpr HPoint bottomRight() const noexcept { return HPoint(m_x + m_width - 1, m_y + m_height - 1); }
    constexpr HPoint center() const noexcept { return HPoint(m_x + m_width / 2, m_y + m_height / 2); }

    // Size
    constexpr HSize size() const noexcept { return HSize(m_width, m_height); }

    // Validity checks
    constexpr bool isNull() const noexcept { return m_width == 0 && m_height == 0; }
    constexpr bool isEmpty() const noexcept { return m_width <= 0 || m_height <= 0; }
    constexpr bool isValid() const noexcept { return m_width >= 0 && m_height >= 0; }

    // Containment
    constexpr bool contains(const HPoint& point) const noexcept {
        return point.x() >= m_x && point.x() < m_x + m_width &&
               point.y() >= m_y && point.y() < m_y + m_height;
    }

    constexpr bool contains(const HRect& rect) const noexcept {
        return rect.left() >= left() && rect.right() <= right() &&
               rect.top() >= top() && rect.bottom() <= bottom();
    }

    // Intersection
    constexpr bool intersects(const HRect& rect) const noexcept {
        return left() <= rect.right() && right() >= rect.left() &&
               top() <= rect.bottom() && bottom() >= rect.top();
    }

    constexpr HRect intersected(const HRect& rect) const noexcept {
        int l = (m_x > rect.m_x) ? m_x : rect.m_x;
        int t = (m_y > rect.m_y) ? m_y : rect.m_y;
        int r = (m_x + m_width < rect.m_x + rect.m_width) ? m_x + m_width : rect.m_x + rect.m_width;
        int b = (m_y + m_height < rect.m_y + rect.m_height) ? m_y + m_height : rect.m_y + rect.m_height;
        return HRect(l, t, r - l, b - t);
    }

    // Union
    constexpr HRect united(const HRect& rect) const noexcept {
        int l = (m_x < rect.m_x) ? m_x : rect.m_x;
        int t = (m_y < rect.m_y) ? m_y : rect.m_y;
        int r = (m_x + m_width > rect.m_x + rect.m_width) ? m_x + m_width : rect.m_x + rect.m_width;
        int b = (m_y + m_height > rect.m_y + rect.m_height) ? m_y + m_height : rect.m_y + rect.m_height;
        return HRect(l, t, r - l, b - t);
    }

    // Adjustment
    constexpr void adjust(int dx1, int dy1, int dx2, int dy2) noexcept {
        m_x += dx1;
        m_y += dy1;
        m_width += dx2 - dx1;
        m_height += dy2 - dy1;
    }

    constexpr HRect adjusted(int dx1, int dy1, int dx2, int dy2) const noexcept {
        return HRect(m_x + dx1, m_y + dy1, m_width + dx2 - dx1, m_height + dy2 - dy1);
    }

    // Translation
    constexpr void translate(int dx, int dy) noexcept {
        m_x += dx;
        m_y += dy;
    }

    constexpr void translate(const HPoint& offset) noexcept {
        m_x += offset.x();
        m_y += offset.y();
    }

    constexpr HRect translated(int dx, int dy) const noexcept {
        return HRect(m_x + dx, m_y + dy, m_width, m_height);
    }

    constexpr HRect translated(const HPoint& offset) const noexcept {
        return HRect(m_x + offset.x(), m_y + offset.y(), m_width, m_height);
    }

    // Move
    constexpr void moveTo(int x, int y) noexcept {
        m_x = x;
        m_y = y;
    }

    constexpr void moveTo(const HPoint& position) noexcept {
        m_x = position.x();
        m_y = position.y();
    }

    constexpr void moveCenter(const HPoint& position) noexcept {
        m_x = position.x() - m_width / 2;
        m_y = position.y() - m_height / 2;
    }

    // Comparison
    constexpr bool operator==(const HRect& other) const noexcept {
        return m_x == other.m_x && m_y == other.m_y &&
               m_width == other.m_width && m_height == other.m_height;
    }

    constexpr bool operator!=(const HRect& other) const noexcept {
        return !(*this == other);
    }

    // Normalize (ensure positive width/height)
    constexpr HRect normalized() const noexcept {
        int nx = m_x, ny = m_y, nw = m_width, nh = m_height;
        if (nw < 0) {
            nx += nw;
            nw = -nw;
        }
        if (nh < 0) {
            ny += nh;
            nh = -nh;
        }
        return HRect(nx, ny, nw, nh);
    }

    // Conversion to HRectF
    HRectF toRectF() const noexcept;

private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
};

} // namespace Ht
