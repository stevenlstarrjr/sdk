#pragma once

#include "HPointF.h"
#include "HRectF.h"

namespace Ht {

/**
 * @brief HTransform represents a 2D affine transformation.
 * Qt Equivalent: QTransform (2D subset)
 * Skia Backend: SkMatrix (3x3)
 */
class HTransform {
public:
    // Constructs identity transform
    constexpr HTransform() noexcept
        : m_m11(1.0f), m_m12(0.0f), m_m13(0.0f)
        , m_m21(0.0f), m_m22(1.0f), m_m23(0.0f)
        , m_m31(0.0f), m_m32(0.0f), m_m33(1.0f) {}

    constexpr HTransform(float m11, float m12, float m13,
                         float m21, float m22, float m23,
                         float m31, float m32, float m33) noexcept
        : m_m11(m11), m_m12(m12), m_m13(m13)
        , m_m21(m21), m_m22(m22), m_m23(m23)
        , m_m31(m31), m_m32(m32), m_m33(m33) {}

    // Factory helpers
    static HTransform fromTranslate(float dx, float dy) noexcept;
    static HTransform fromScale(float sx, float sy) noexcept;
    static HTransform fromRotate(float degrees) noexcept;

    // Access to matrix elements
    constexpr float m11() const noexcept { return m_m11; }
    constexpr float m12() const noexcept { return m_m12; }
    constexpr float m13() const noexcept { return m_m13; }
    constexpr float m21() const noexcept { return m_m21; }
    constexpr float m22() const noexcept { return m_m22; }
    constexpr float m23() const noexcept { return m_m23; }
    constexpr float m31() const noexcept { return m_m31; }
    constexpr float m32() const noexcept { return m_m32; }
    constexpr float m33() const noexcept { return m_m33; }

    // Basic operations
    constexpr bool isIdentity() const noexcept {
        return m_m11 == 1.0f && m_m22 == 1.0f && m_m33 == 1.0f &&
               m_m12 == 0.0f && m_m13 == 0.0f &&
               m_m21 == 0.0f && m_m23 == 0.0f &&
               m_m31 == 0.0f && m_m32 == 0.0f;
    }

    void setToIdentity() noexcept;

    // In-place composition (this = this * other)
    HTransform& translate(float dx, float dy) noexcept;
    HTransform& scale(float sx, float sy) noexcept;
    HTransform& rotate(float degrees) noexcept;

    // Matrix multiplication (composition)
    HTransform& operator*=(const HTransform& other) noexcept;
    friend HTransform operator*(const HTransform& a, const HTransform& b) noexcept {
        HTransform result = a;
        result *= b;
        return result;
    }

    // Map helpers
    HPointF map(const HPointF& p) const noexcept;
    HRectF map(const HRectF& r) const noexcept;

private:
    float m_m11, m_m12, m_m13;
    float m_m21, m_m22, m_m23;
    float m_m31, m_m32, m_m33;
};

} // namespace Ht

