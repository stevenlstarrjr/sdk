#pragma once

namespace Ht {

/**
 * @brief HMargins represents integer margins around a rectangle.
 * Qt Equivalent: QMargins
 */
class HMargins {
public:
    // Constructors
    constexpr HMargins() noexcept : m_left(0), m_top(0), m_right(0), m_bottom(0) {}
    constexpr HMargins(int left, int top, int right, int bottom) noexcept
        : m_left(left), m_top(top), m_right(right), m_bottom(bottom) {}

    // Accessors
    constexpr int left() const noexcept { return m_left; }
    constexpr int top() const noexcept { return m_top; }
    constexpr int right() const noexcept { return m_right; }
    constexpr int bottom() const noexcept { return m_bottom; }

    constexpr void setLeft(int left) noexcept { m_left = left; }
    constexpr void setTop(int top) noexcept { m_top = top; }
    constexpr void setRight(int right) noexcept { m_right = right; }
    constexpr void setBottom(int bottom) noexcept { m_bottom = bottom; }

    // Convenience
    constexpr bool isNull() const noexcept {
        return m_left == 0 && m_top == 0 && m_right == 0 && m_bottom == 0;
    }

    // Arithmetic
    constexpr HMargins operator+(const HMargins& other) const noexcept {
        return HMargins(m_left + other.m_left,
                        m_top + other.m_top,
                        m_right + other.m_right,
                        m_bottom + other.m_bottom);
    }

    constexpr HMargins operator-(const HMargins& other) const noexcept {
        return HMargins(m_left - other.m_left,
                        m_top - other.m_top,
                        m_right - other.m_right,
                        m_bottom - other.m_bottom);
    }

    constexpr HMargins& operator+=(const HMargins& other) noexcept {
        m_left += other.m_left;
        m_top += other.m_top;
        m_right += other.m_right;
        m_bottom += other.m_bottom;
        return *this;
    }

    constexpr HMargins& operator-=(const HMargins& other) noexcept {
        m_left -= other.m_left;
        m_top -= other.m_top;
        m_right -= other.m_right;
        m_bottom -= other.m_bottom;
        return *this;
    }

    // Comparison
    constexpr bool operator==(const HMargins& other) const noexcept {
        return m_left == other.m_left &&
               m_top == other.m_top &&
               m_right == other.m_right &&
               m_bottom == other.m_bottom;
    }

    constexpr bool operator!=(const HMargins& other) const noexcept {
        return !(*this == other);
    }

private:
    int m_left;
    int m_top;
    int m_right;
    int m_bottom;
};

/**
 * @brief HMarginsF represents floating-point margins around a rectangle.
 * Qt Equivalent: QMarginsF
 */
class HMarginsF {
public:
    // Constructors
    constexpr HMarginsF() noexcept
        : m_left(0.0f), m_top(0.0f), m_right(0.0f), m_bottom(0.0f) {}
    constexpr HMarginsF(float left, float top, float right, float bottom) noexcept
        : m_left(left), m_top(top), m_right(right), m_bottom(bottom) {}

    // Accessors
    constexpr float left() const noexcept { return m_left; }
    constexpr float top() const noexcept { return m_top; }
    constexpr float right() const noexcept { return m_right; }
    constexpr float bottom() const noexcept { return m_bottom; }

    constexpr void setLeft(float left) noexcept { m_left = left; }
    constexpr void setTop(float top) noexcept { m_top = top; }
    constexpr void setRight(float right) noexcept { m_right = right; }
    constexpr void setBottom(float bottom) noexcept { m_bottom = bottom; }

    // Convenience
    constexpr bool isNull() const noexcept {
        return m_left == 0.0f && m_top == 0.0f &&
               m_right == 0.0f && m_bottom == 0.0f;
    }

    // Arithmetic
    constexpr HMarginsF operator+(const HMarginsF& other) const noexcept {
        return HMarginsF(m_left + other.m_left,
                         m_top + other.m_top,
                         m_right + other.m_right,
                         m_bottom + other.m_bottom);
    }

    constexpr HMarginsF operator-(const HMarginsF& other) const noexcept {
        return HMarginsF(m_left - other.m_left,
                         m_top - other.m_top,
                         m_right - other.m_right,
                         m_bottom - other.m_bottom);
    }

    constexpr HMarginsF& operator+=(const HMarginsF& other) noexcept {
        m_left += other.m_left;
        m_top += other.m_top;
        m_right += other.m_right;
        m_bottom += other.m_bottom;
        return *this;
    }

    constexpr HMarginsF& operator-=(const HMarginsF& other) noexcept {
        m_left -= other.m_left;
        m_top -= other.m_top;
        m_right -= other.m_right;
        m_bottom -= other.m_bottom;
        return *this;
    }

    // Comparison
    constexpr bool operator==(const HMarginsF& other) const noexcept {
        return m_left == other.m_left &&
               m_top == other.m_top &&
               m_right == other.m_right &&
               m_bottom == other.m_bottom;
    }

    constexpr bool operator!=(const HMarginsF& other) const noexcept {
        return !(*this == other);
    }

private:
    float m_left;
    float m_top;
    float m_right;
    float m_bottom;
};

} // namespace Ht

