#pragma once

#include "HPoint.h"
#include "HPointF.h"

namespace Ht {

/**
 * @brief HLine represents a line segment with integer endpoints.
 * Qt Equivalent: QLine
 */
class HLine {
public:
    // Constructors
    constexpr HLine() noexcept : m_p1(), m_p2() {}
    constexpr HLine(int x1, int y1, int x2, int y2) noexcept
        : m_p1(x1, y1), m_p2(x2, y2) {}
    constexpr HLine(const HPoint& p1, const HPoint& p2) noexcept
        : m_p1(p1), m_p2(p2) {}

    // Accessors
    constexpr HPoint p1() const noexcept { return m_p1; }
    constexpr HPoint p2() const noexcept { return m_p2; }

    constexpr void setP1(const HPoint& p) noexcept { m_p1 = p; }
    constexpr void setP2(const HPoint& p) noexcept { m_p2 = p; }

    constexpr int x1() const noexcept { return m_p1.x(); }
    constexpr int y1() const noexcept { return m_p1.y(); }
    constexpr int x2() const noexcept { return m_p2.x(); }
    constexpr int y2() const noexcept { return m_p2.y(); }

    constexpr void setLine(int x1, int y1, int x2, int y2) noexcept {
        m_p1.setX(x1);
        m_p1.setY(y1);
        m_p2.setX(x2);
        m_p2.setY(y2);
    }

    // Geometric helpers
    constexpr bool isNull() const noexcept {
        return m_p1 == m_p2;
    }

    constexpr HPoint center() const noexcept {
        return HPoint((m_p1.x() + m_p2.x()) / 2, (m_p1.y() + m_p2.y()) / 2);
    }

    // Conversion
    HLine toLine() const noexcept { return *this; }

    // Comparison
    constexpr bool operator==(const HLine& other) const noexcept {
        return m_p1 == other.m_p1 && m_p2 == other.m_p2;
    }

    constexpr bool operator!=(const HLine& other) const noexcept {
        return !(*this == other);
    }

private:
    HPoint m_p1;
    HPoint m_p2;
};

/**
 * @brief HLineF represents a line segment with floating-point endpoints.
 * Qt Equivalent: QLineF
 */
class HLineF {
public:
    // Constructors
    constexpr HLineF() noexcept : m_p1(), m_p2() {}
    constexpr HLineF(float x1, float y1, float x2, float y2) noexcept
        : m_p1(x1, y1), m_p2(x2, y2) {}
    constexpr HLineF(const HPointF& p1, const HPointF& p2) noexcept
        : m_p1(p1), m_p2(p2) {}

    // Accessors
    constexpr HPointF p1() const noexcept { return m_p1; }
    constexpr HPointF p2() const noexcept { return m_p2; }

    constexpr void setP1(const HPointF& p) noexcept { m_p1 = p; }
    constexpr void setP2(const HPointF& p) noexcept { m_p2 = p; }

    constexpr float x1() const noexcept { return m_p1.x(); }
    constexpr float y1() const noexcept { return m_p1.y(); }
    constexpr float x2() const noexcept { return m_p2.x(); }
    constexpr float y2() const noexcept { return m_p2.y(); }

    constexpr void setLine(float x1, float y1, float x2, float y2) noexcept {
        m_p1.setX(x1);
        m_p1.setY(y1);
        m_p2.setX(x2);
        m_p2.setY(y2);
    }

    // Geometric helpers
    constexpr bool isNull() const noexcept {
        return m_p1 == m_p2;
    }

    constexpr HPointF center() const noexcept {
        return HPointF((m_p1.x() + m_p2.x()) / 2.0f, (m_p1.y() + m_p2.y()) / 2.0f);
    }

    // Conversion
    HLineF toLineF() const noexcept { return *this; }

    // Comparison
    constexpr bool operator==(const HLineF& other) const noexcept {
        return m_p1 == other.m_p1 && m_p2 == other.m_p2;
    }

    constexpr bool operator!=(const HLineF& other) const noexcept {
        return !(*this == other);
    }

private:
    HPointF m_p1;
    HPointF m_p2;
};

} // namespace Ht

