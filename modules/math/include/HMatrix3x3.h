#pragma once

namespace Ht {

class HVector2;

class HMatrix3x3
{
public:
    HMatrix3x3();

    static HMatrix3x3 identity();

    float m(int row, int column) const;
    void setM(int row, int column, float value);

    HMatrix3x3 operator*(const HMatrix3x3& other) const;

    HVector2 transformPoint(const HVector2& v) const;
    HVector2 transformVector(const HVector2& v) const;

private:
    float m_values[9];
};

} // namespace Ht

