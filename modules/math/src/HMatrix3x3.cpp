#include "HMatrix3x3.h"
#include "HVector2.h"

namespace Ht {

HMatrix3x3::HMatrix3x3()
{
    m_values[0] = 1.0f; m_values[1] = 0.0f; m_values[2] = 0.0f;
    m_values[3] = 0.0f; m_values[4] = 1.0f; m_values[5] = 0.0f;
    m_values[6] = 0.0f; m_values[7] = 0.0f; m_values[8] = 1.0f;
}

HMatrix3x3 HMatrix3x3::identity()
{
    return HMatrix3x3();
}

float HMatrix3x3::m(int row, int column) const
{
    return m_values[row * 3 + column];
}

void HMatrix3x3::setM(int row, int column, float value)
{
    m_values[row * 3 + column] = value;
}

HMatrix3x3 HMatrix3x3::operator*(const HMatrix3x3& other) const
{
    HMatrix3x3 result;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            float sum = 0.0f;
            for (int k = 0; k < 3; ++k) {
                sum += m(row, k) * other.m(k, col);
            }
            result.setM(row, col, sum);
        }
    }
    return result;
}

HVector2 HMatrix3x3::transformPoint(const HVector2& v) const
{
    float x = v.x();
    float y = v.y();
    float tx = m(0, 0) * x + m(0, 1) * y + m(0, 2);
    float ty = m(1, 0) * x + m(1, 1) * y + m(1, 2);
    float w = m(2, 0) * x + m(2, 1) * y + m(2, 2);
    if (w != 0.0f) {
        tx /= w;
        ty /= w;
    }
    return HVector2(tx, ty);
}

HVector2 HMatrix3x3::transformVector(const HVector2& v) const
{
    float x = v.x();
    float y = v.y();
    float tx = m(0, 0) * x + m(0, 1) * y;
    float ty = m(1, 0) * x + m(1, 1) * y;
    return HVector2(tx, ty);
}

} // namespace Ht

