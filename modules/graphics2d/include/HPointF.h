#pragma once

namespace Ht {

/**
 * @brief HPointF represents a point in 2D space with floating-point precision
 * Qt Equivalent: QPointF
 * Skia Backend: SkPoint
 */
class HPointF {
public:
    // Constructors
    constexpr HPointF() noexcept : m_x(0.0f), m_y(0.0f) {}
    constexpr HPointF(float x, float y) noexcept : m_x(x), m_y(y) {}

    // Accessors
    constexpr float x() const noexcept { return m_x; }
    constexpr float y() const noexcept { return m_y; }

    constexpr void setX(float x) noexcept { m_x = x; }
    constexpr void setY(float y) noexcept { m_y = y; }

    // Null point check
    constexpr bool isNull() const noexcept { return m_x == 0.0f && m_y == 0.0f; }

    // Arithmetic operators
    constexpr HPointF operator+(const HPointF& other) const noexcept {
        return HPointF(m_x + other.m_x, m_y + other.m_y);
    }

    constexpr HPointF operator-(const HPointF& other) const noexcept {
        return HPointF(m_x - other.m_x, m_y - other.m_y);
    }

    constexpr HPointF operator*(float factor) const noexcept {
        return HPointF(m_x * factor, m_y * factor);
    }

    constexpr HPointF operator/(float divisor) const noexcept {
        return HPointF(m_x / divisor, m_y / divisor);
    }

    constexpr HPointF& operator+=(const HPointF& other) noexcept {
        m_x += other.m_x;
        m_y += other.m_y;
        return *this;
    }

    constexpr HPointF& operator-=(const HPointF& other) noexcept {
        m_x -= other.m_x;
        m_y -= other.m_y;
        return *this;
    }

    constexpr HPointF& operator*=(float factor) noexcept {
        m_x *= factor;
        m_y *= factor;
        return *this;
    }

    constexpr HPointF& operator/=(float divisor) noexcept {
        m_x /= divisor;
        m_y /= divisor;
        return *this;
    }

    // Comparison operators
    constexpr bool operator==(const HPointF& other) const noexcept {
        return m_x == other.m_x && m_y == other.m_y;
    }

    constexpr bool operator!=(const HPointF& other) const noexcept {
        return !(*this == other);
    }

    // Unary minus
    constexpr HPointF operator-() const noexcept {
        return HPointF(-m_x, -m_y);
    }

    // Manhattan length
    constexpr float manhattanLength() const noexcept {
        return (m_x < 0.0f ? -m_x : m_x) + (m_y < 0.0f ? -m_y : m_y);
    }

private:
    float m_x;
    float m_y;
};

// Non-member operator for scalar * point
constexpr HPointF operator*(float factor, const HPointF& point) noexcept {
    return point * factor;
}

} // namespace Ht
