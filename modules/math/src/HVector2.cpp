#include "HVector2.h"

namespace Ht {

HVector2 HVector2::operator+(const HVector2& other) const
{
    return HVector2(m_x + other.m_x, m_y + other.m_y);
}

HVector2 HVector2::operator-(const HVector2& other) const
{
    return HVector2(m_x - other.m_x, m_y - other.m_y);
}

HVector2& HVector2::operator+=(const HVector2& other)
{
    m_x += other.m_x;
    m_y += other.m_y;
    return *this;
}

HVector2& HVector2::operator-=(const HVector2& other)
{
    m_x -= other.m_x;
    m_y -= other.m_y;
    return *this;
}

HVector2 HVector2::operator*(float scalar) const
{
    return HVector2(m_x * scalar, m_y * scalar);
}

HVector2 HVector2::operator/(float scalar) const
{
    return HVector2(m_x / scalar, m_y / scalar);
}

HVector2& HVector2::operator*=(float scalar)
{
    m_x *= scalar;
    m_y *= scalar;
    return *this;
}

HVector2& HVector2::operator/=(float scalar)
{
    m_x /= scalar;
    m_y /= scalar;
    return *this;
}

bool HVector2::operator==(const HVector2& other) const
{
    return m_x == other.m_x && m_y == other.m_y;
}

bool HVector2::operator!=(const HVector2& other) const
{
    return !(*this == other);
}

float HVector2::lengthSquared() const
{
    return m_x * m_x + m_y * m_y;
}

float HVector2::length() const
{
    return std::sqrt(lengthSquared());
}

void HVector2::normalize()
{
    float len = length();
    if (len > 0.0f) {
        m_x /= len;
        m_y /= len;
    }
}

HVector2 HVector2::normalized() const
{
    float len = length();
    if (len > 0.0f) {
        return HVector2(m_x / len, m_y / len);
    }
    return HVector2();
}

float HVector2::dot(const HVector2& a, const HVector2& b)
{
    return a.m_x * b.m_x + a.m_y * b.m_y;
}

} // namespace Ht

