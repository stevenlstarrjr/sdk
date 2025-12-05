#pragma once

#include "HMatrix3x3.h"
#include "HVector2.h"

namespace Ht {

class HTransform2D
{
public:
    HTransform2D();
    explicit HTransform2D(const HMatrix3x3& matrix);

    const HMatrix3x3& matrix() const;

    HVector2 mapPoint(const HVector2& point) const;
    HVector2 mapVector(const HVector2& vector) const;

    static HTransform2D translation(float tx, float ty);
    static HTransform2D scale(float sx, float sy);
    static HTransform2D rotation(float radians);
    static HTransform2D shear(float shx, float shy);

    HTransform2D operator*(const HTransform2D& other) const;
    HTransform2D& operator*=(const HTransform2D& other);

private:
    HMatrix3x3 m_matrix;
};

} // namespace Ht

