#include "HTransform.h"

#include <cmath>

namespace Ht {

HTransform HTransform::fromTranslate(float dx, float dy) noexcept {
    return HTransform(1.0f, 0.0f, dx,
                      0.0f, 1.0f, dy,
                      0.0f, 0.0f, 1.0f);
}

HTransform HTransform::fromScale(float sx, float sy) noexcept {
    return HTransform(sx,  0.0f, 0.0f,
                      0.0f, sy,  0.0f,
                      0.0f, 0.0f, 1.0f);
}

HTransform HTransform::fromRotate(float degrees) noexcept {
    float rad = degrees * 3.1415926535f / 180.0f;
    float c = std::cos(rad);
    float s = std::sin(rad);
    return HTransform(c, -s, 0.0f,
                      s,  c, 0.0f,
                      0.0f, 0.0f, 1.0f);
}

void HTransform::setToIdentity() noexcept {
    *this = HTransform();
}

HTransform& HTransform::translate(float dx, float dy) noexcept {
    *this *= fromTranslate(dx, dy);
    return *this;
}

HTransform& HTransform::scale(float sx, float sy) noexcept {
    *this *= fromScale(sx, sy);
    return *this;
}

HTransform& HTransform::rotate(float degrees) noexcept {
    *this *= fromRotate(degrees);
    return *this;
}

HTransform& HTransform::operator*=(const HTransform& o) noexcept {
    const float a11 = m_m11 * o.m_m11 + m_m12 * o.m_m21 + m_m13 * o.m_m31;
    const float a12 = m_m11 * o.m_m12 + m_m12 * o.m_m22 + m_m13 * o.m_m32;
    const float a13 = m_m11 * o.m_m13 + m_m12 * o.m_m23 + m_m13 * o.m_m33;

    const float a21 = m_m21 * o.m_m11 + m_m22 * o.m_m21 + m_m23 * o.m_m31;
    const float a22 = m_m21 * o.m_m12 + m_m22 * o.m_m22 + m_m23 * o.m_m32;
    const float a23 = m_m21 * o.m_m13 + m_m22 * o.m_m23 + m_m23 * o.m_m33;

    const float a31 = m_m31 * o.m_m11 + m_m32 * o.m_m21 + m_m33 * o.m_m31;
    const float a32 = m_m31 * o.m_m12 + m_m32 * o.m_m22 + m_m33 * o.m_m32;
    const float a33 = m_m31 * o.m_m13 + m_m32 * o.m_m23 + m_m33 * o.m_m33;

    m_m11 = a11; m_m12 = a12; m_m13 = a13;
    m_m21 = a21; m_m22 = a22; m_m23 = a23;
    m_m31 = a31; m_m32 = a32; m_m33 = a33;

    return *this;
}

HPointF HTransform::map(const HPointF& p) const noexcept {
    float x = p.x();
    float y = p.y();
    float tx = m_m11 * x + m_m12 * y + m_m13;
    float ty = m_m21 * x + m_m22 * y + m_m23;
    float w  = m_m31 * x + m_m32 * y + m_m33;
    if (w != 0.0f && w != 1.0f) {
        tx /= w;
        ty /= w;
    }
    return HPointF(tx, ty);
}

HRectF HTransform::map(const HRectF& r) const noexcept {
    if (r.isEmpty()) {
        return HRectF();
    }

    HPointF p1 = map(r.topLeft());
    HPointF p2 = map(r.topRight());
    HPointF p3 = map(r.bottomLeft());
    HPointF p4 = map(r.bottomRight());

    float minX = p1.x();
    float minY = p1.y();
    float maxX = p1.x();
    float maxY = p1.y();

    auto expand = [&](const HPointF& p) {
        if (p.x() < minX) minX = p.x();
        if (p.x() > maxX) maxX = p.x();
        if (p.y() < minY) minY = p.y();
        if (p.y() > maxY) maxY = p.y();
    };

    expand(p2);
    expand(p3);
    expand(p4);

    return HRectF(minX, minY, maxX - minX, maxY - minY);
}

} // namespace Ht

