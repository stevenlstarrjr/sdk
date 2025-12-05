#pragma once

#include <cmath>

namespace Ht {

class HVector2
{
public:
    HVector2()
        : m_x(0.0f)
        , m_y(0.0f)
    {
    }

    HVector2(float x, float y)
        : m_x(x)
        , m_y(y)
    {
    }

    float x() const { return m_x; }
    float y() const { return m_y; }

    void setX(float x) { m_x = x; }
    void setY(float y) { m_y = y; }

    HVector2 operator+(const HVector2& other) const;
    HVector2 operator-(const HVector2& other) const;
    HVector2& operator+=(const HVector2& other);
    HVector2& operator-=(const HVector2& other);

    HVector2 operator*(float scalar) const;
    HVector2 operator/(float scalar) const;
    HVector2& operator*=(float scalar);
    HVector2& operator/=(float scalar);

    bool operator==(const HVector2& other) const;
    bool operator!=(const HVector2& other) const;

    float length() const;
    float lengthSquared() const;
    void normalize();
    HVector2 normalized() const;

    static float dot(const HVector2& a, const HVector2& b);

private:
    float m_x;
    float m_y;
};

} // namespace Ht

