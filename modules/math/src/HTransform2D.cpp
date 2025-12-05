#include "HTransform2D.h"

#include <cmath>

namespace Ht {

HTransform2D::HTransform2D()
    : m_matrix(HMatrix3x3::identity())
{
}

HTransform2D::HTransform2D(const HMatrix3x3& matrix)
    : m_matrix(matrix)
{
}

const HMatrix3x3& HTransform2D::matrix() const
{
    return m_matrix;
}

HVector2 HTransform2D::mapPoint(const HVector2& point) const
{
    return m_matrix.transformPoint(point);
}

HVector2 HTransform2D::mapVector(const HVector2& vector) const
{
    return m_matrix.transformVector(vector);
}

HTransform2D HTransform2D::translation(float tx, float ty)
{
    HMatrix3x3 m = HMatrix3x3::identity();
    m.setM(0, 2, tx);
    m.setM(1, 2, ty);
    return HTransform2D(m);
}

HTransform2D HTransform2D::scale(float sx, float sy)
{
    HMatrix3x3 m = HMatrix3x3::identity();
    m.setM(0, 0, sx);
    m.setM(1, 1, sy);
    return HTransform2D(m);
}

HTransform2D HTransform2D::rotation(float radians)
{
    float c = std::cos(radians);
    float s = std::sin(radians);

    HMatrix3x3 m;
    m.setM(0, 0, c);
    m.setM(0, 1, -s);
    m.setM(0, 2, 0.0f);
    m.setM(1, 0, s);
    m.setM(1, 1, c);
    m.setM(1, 2, 0.0f);
    m.setM(2, 0, 0.0f);
    m.setM(2, 1, 0.0f);
    m.setM(2, 2, 1.0f);
    return HTransform2D(m);
}

HTransform2D HTransform2D::shear(float shx, float shy)
{
    HMatrix3x3 m = HMatrix3x3::identity();
    m.setM(0, 1, shx);
    m.setM(1, 0, shy);
    return HTransform2D(m);
}

HTransform2D HTransform2D::operator*(const HTransform2D& other) const
{
    return HTransform2D(m_matrix * other.m_matrix);
}

HTransform2D& HTransform2D::operator*=(const HTransform2D& other)
{
    m_matrix = m_matrix * other.m_matrix;
    return *this;
}

} // namespace Ht

