#pragma once

namespace Ht {

class HSizeF;

/**
 * @brief HSize represents a size with integer precision
 * Qt Equivalent: QSize
 * Skia Backend: SkISize
 */
class HSize {
public:
    // Constructors
    constexpr HSize() noexcept : m_width(0), m_height(0) {}
    constexpr HSize(int width, int height) noexcept : m_width(width), m_height(height) {}

    // Accessors
    constexpr int width() const noexcept { return m_width; }
    constexpr int height() const noexcept { return m_height; }

    constexpr void setWidth(int width) noexcept { m_width = width; }
    constexpr void setHeight(int height) noexcept { m_height = height; }

    // Reference accessors
    constexpr int& rwidth() noexcept { return m_width; }
    constexpr int& rheight() noexcept { return m_height; }

    // Validity checks
    constexpr bool isNull() const noexcept { return m_width == 0 && m_height == 0; }
    constexpr bool isEmpty() const noexcept { return m_width <= 0 || m_height <= 0; }
    constexpr bool isValid() const noexcept { return m_width >= 0 && m_height >= 0; }

    // Transpose
    constexpr HSize transposed() const noexcept {
        return HSize(m_height, m_width);
    }

    // Scale operations
    constexpr void scale(int w, int h) noexcept {
        m_width *= w;
        m_height *= h;
    }

    constexpr void scale(const HSize& size) noexcept {
        m_width *= size.m_width;
        m_height *= size.m_height;
    }

    constexpr HSize scaled(int w, int h) const noexcept {
        return HSize(m_width * w, m_height * h);
    }

    constexpr HSize scaled(const HSize& size) const noexcept {
        return HSize(m_width * size.m_width, m_height * size.m_height);
    }

    // Grow/shrink
    constexpr HSize grownBy(int dw, int dh) const noexcept {
        return HSize(m_width + dw, m_height + dh);
    }

    constexpr HSize shrunkBy(int dw, int dh) const noexcept {
        return HSize(m_width - dw, m_height - dh);
    }

    // Arithmetic operators
    constexpr HSize operator+(const HSize& other) const noexcept {
        return HSize(m_width + other.m_width, m_height + other.m_height);
    }

    constexpr HSize operator-(const HSize& other) const noexcept {
        return HSize(m_width - other.m_width, m_height - other.m_height);
    }

    constexpr HSize operator*(float factor) const noexcept {
        return HSize(static_cast<int>(m_width * factor), static_cast<int>(m_height * factor));
    }

    constexpr HSize operator/(float divisor) const noexcept {
        return HSize(static_cast<int>(m_width / divisor), static_cast<int>(m_height / divisor));
    }

    constexpr HSize& operator+=(const HSize& other) noexcept {
        m_width += other.m_width;
        m_height += other.m_height;
        return *this;
    }

    constexpr HSize& operator-=(const HSize& other) noexcept {
        m_width -= other.m_width;
        m_height -= other.m_height;
        return *this;
    }

    constexpr HSize& operator*=(float factor) noexcept {
        m_width = static_cast<int>(m_width * factor);
        m_height = static_cast<int>(m_height * factor);
        return *this;
    }

    constexpr HSize& operator/=(float divisor) noexcept {
        m_width = static_cast<int>(m_width / divisor);
        m_height = static_cast<int>(m_height / divisor);
        return *this;
    }

    // Comparison operators
    constexpr bool operator==(const HSize& other) const noexcept {
        return m_width == other.m_width && m_height == other.m_height;
    }

    constexpr bool operator!=(const HSize& other) const noexcept {
        return !(*this == other);
    }

    // Conversion to HSizeF
    HSizeF toSizeF() const noexcept;

private:
    int m_width;
    int m_height;
};

// Non-member operator for scalar * size
constexpr HSize operator*(float factor, const HSize& size) noexcept {
    return size * factor;
}

} // namespace Ht
