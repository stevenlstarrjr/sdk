#pragma once

namespace Ht {

class HPointF;

/**
 * @brief HPoint represents a point in 2D space with integer precision
 * Qt Equivalent: QPoint
 * Skia Backend: SkIPoint
 */
class HPoint {
public:
    // Constructors
    constexpr HPoint() noexcept : m_x(0), m_y(0) {}
    constexpr HPoint(int x, int y) noexcept : m_x(x), m_y(y) {}

    // Accessors
    constexpr int x() const noexcept { return m_x; }
    constexpr int y() const noexcept { return m_y; }

    constexpr void setX(int x) noexcept { m_x = x; }
    constexpr void setY(int y) noexcept { m_y = y; }

    // Reference accessors
    constexpr int& rx() noexcept { return m_x; }
    constexpr int& ry() noexcept { return m_y; }

    // Null point check
    constexpr bool isNull() const noexcept { return m_x == 0 && m_y == 0; }

    // Arithmetic operators
    constexpr HPoint operator+(const HPoint& other) const noexcept {
        return HPoint(m_x + other.m_x, m_y + other.m_y);
    }

    constexpr HPoint operator-(const HPoint& other) const noexcept {
        return HPoint(m_x - other.m_x, m_y - other.m_y);
    }

    constexpr HPoint operator*(float factor) const noexcept {
        return HPoint(static_cast<int>(m_x * factor), static_cast<int>(m_y * factor));
    }

    constexpr HPoint operator/(float divisor) const noexcept {
        return HPoint(static_cast<int>(m_x / divisor), static_cast<int>(m_y / divisor));
    }

    constexpr HPoint& operator+=(const HPoint& other) noexcept {
        m_x += other.m_x;
        m_y += other.m_y;
        return *this;
    }

    constexpr HPoint& operator-=(const HPoint& other) noexcept {
        m_x -= other.m_x;
        m_y -= other.m_y;
        return *this;
    }

    constexpr HPoint& operator*=(float factor) noexcept {
        m_x = static_cast<int>(m_x * factor);
        m_y = static_cast<int>(m_y * factor);
        return *this;
    }

    constexpr HPoint& operator/=(float divisor) noexcept {
        m_x = static_cast<int>(m_x / divisor);
        m_y = static_cast<int>(m_y / divisor);
        return *this;
    }

    // Comparison operators
    constexpr bool operator==(const HPoint& other) const noexcept {
        return m_x == other.m_x && m_y == other.m_y;
    }

    constexpr bool operator!=(const HPoint& other) const noexcept {
        return !(*this == other);
    }

    // Unary minus
    constexpr HPoint operator-() const noexcept {
        return HPoint(-m_x, -m_y);
    }

    // Manhattan length
    constexpr int manhattanLength() const noexcept {
        return (m_x < 0 ? -m_x : m_x) + (m_y < 0 ? -m_y : m_y);
    }

    // Conversion to HPointF
    HPointF toPointF() const noexcept;

private:
    int m_x;
    int m_y;
};

// Non-member operator for scalar * point
constexpr HPoint operator*(float factor, const HPoint& point) noexcept {
    return point * factor;
}

} // namespace Ht
