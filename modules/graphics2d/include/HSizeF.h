#pragma once

namespace Ht {

/**
 * @brief HSizeF represents a size with floating-point precision
 * Qt Equivalent: QSizeF
 * Skia Backend: SkSize
 */
class HSizeF {
public:
    // Constructors
    constexpr HSizeF() noexcept : m_width(0.0f), m_height(0.0f) {}
    constexpr HSizeF(float width, float height) noexcept : m_width(width), m_height(height) {}

    // Accessors
    constexpr float width() const noexcept { return m_width; }
    constexpr float height() const noexcept { return m_height; }

    constexpr void setWidth(float width) noexcept { m_width = width; }
    constexpr void setHeight(float height) noexcept { m_height = height; }

    // Validity checks
    constexpr bool isNull() const noexcept { return m_width == 0.0f && m_height == 0.0f; }
    constexpr bool isEmpty() const noexcept { return m_width <= 0.0f || m_height <= 0.0f; }
    constexpr bool isValid() const noexcept { return m_width >= 0.0f && m_height >= 0.0f; }

    // Transpose
    constexpr HSizeF transposed() const noexcept {
        return HSizeF(m_height, m_width);
    }

    // Scale operations
    constexpr void scale(float w, float h) noexcept {
        m_width *= w;
        m_height *= h;
    }

    constexpr void scale(const HSizeF& size) noexcept {
        m_width *= size.m_width;
        m_height *= size.m_height;
    }

    constexpr HSizeF scaled(float w, float h) const noexcept {
        return HSizeF(m_width * w, m_height * h);
    }

    constexpr HSizeF scaled(const HSizeF& size) const noexcept {
        return HSizeF(m_width * size.m_width, m_height * size.m_height);
    }

    // Grow/shrink
    constexpr HSizeF grownBy(float dw, float dh) const noexcept {
        return HSizeF(m_width + dw, m_height + dh);
    }

    constexpr HSizeF shrunkBy(float dw, float dh) const noexcept {
        return HSizeF(m_width - dw, m_height - dh);
    }

    // Arithmetic operators
    constexpr HSizeF operator+(const HSizeF& other) const noexcept {
        return HSizeF(m_width + other.m_width, m_height + other.m_height);
    }

    constexpr HSizeF operator-(const HSizeF& other) const noexcept {
        return HSizeF(m_width - other.m_width, m_height - other.m_height);
    }

    constexpr HSizeF operator*(float factor) const noexcept {
        return HSizeF(m_width * factor, m_height * factor);
    }

    constexpr HSizeF operator/(float divisor) const noexcept {
        return HSizeF(m_width / divisor, m_height / divisor);
    }

    constexpr HSizeF& operator+=(const HSizeF& other) noexcept {
        m_width += other.m_width;
        m_height += other.m_height;
        return *this;
    }

    constexpr HSizeF& operator-=(const HSizeF& other) noexcept {
        m_width -= other.m_width;
        m_height -= other.m_height;
        return *this;
    }

    constexpr HSizeF& operator*=(float factor) noexcept {
        m_width *= factor;
        m_height *= factor;
        return *this;
    }

    constexpr HSizeF& operator/=(float divisor) noexcept {
        m_width /= divisor;
        m_height /= divisor;
        return *this;
    }

    // Comparison operators
    constexpr bool operator==(const HSizeF& other) const noexcept {
        return m_width == other.m_width && m_height == other.m_height;
    }

    constexpr bool operator!=(const HSizeF& other) const noexcept {
        return !(*this == other);
    }

private:
    float m_width;
    float m_height;
};

// Non-member operator for scalar * size
constexpr HSizeF operator*(float factor, const HSizeF& size) noexcept {
    return size * factor;
}

} // namespace Ht
