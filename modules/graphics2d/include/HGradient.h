#pragma once

#include "HColor.h"
#include "HPointF.h"
#include <vector>

namespace Ht {

/**
 * @brief Base class for gradient definitions.
 * Qt Equivalent: QGradient
 * Skia Backend: SkShader (via SkGradientShader)
 */
class HGradient {
public:
    enum class Spread {
        Pad,
        Repeat,
        Reflect
    };

    struct ColorStop {
        float position; // 0.0 - 1.0
        HColor color;
    };

    virtual ~HGradient() = default;

    void setSpread(Spread spread) noexcept { m_spread = spread; }
    Spread spread() const noexcept { return m_spread; }

    void setStops(const std::vector<ColorStop>& stops) { m_stops = stops; }
    const std::vector<ColorStop>& stops() const noexcept { return m_stops; }

protected:
    HGradient() = default;

private:
    Spread m_spread = Spread::Pad;
    std::vector<ColorStop> m_stops;
};

/**
 * @brief Linear gradient between two points.
 * Qt Equivalent: QLinearGradient
 */
class HLinearGradient : public HGradient {
public:
    HLinearGradient() noexcept = default;
    HLinearGradient(const HPointF& start, const HPointF& end) noexcept
        : m_start(start), m_end(end) {}

    void setStart(const HPointF& start) noexcept { m_start = start; }
    void setEnd(const HPointF& end) noexcept { m_end = end; }

    HPointF start() const noexcept { return m_start; }
    HPointF end() const noexcept { return m_end; }

private:
    HPointF m_start;
    HPointF m_end;
};

/**
 * @brief Radial gradient defined by a center and radius.
 * Qt Equivalent: QRadialGradient
 */
class HRadialGradient : public HGradient {
public:
    HRadialGradient() noexcept = default;
    HRadialGradient(const HPointF& center, float radius) noexcept
        : m_center(center), m_radius(radius) {}

    void setCenter(const HPointF& center) noexcept { m_center = center; }
    void setRadius(float radius) noexcept { m_radius = radius; }

    HPointF center() const noexcept { return m_center; }
    float radius() const noexcept { return m_radius; }

private:
    HPointF m_center;
    float m_radius = 0.0f;
};

/**
 * @brief Conical (sweep) gradient around a center.
 * Qt Equivalent: QConicalGradient
 *
 * Modeled on SkGradientShader::MakeSweep; startAngle is in degrees,
 * where 0 degrees is the +X axis.
 */
class HConicalGradient : public HGradient {
public:
    HConicalGradient() noexcept = default;
    HConicalGradient(const HPointF& center, float startAngleDegrees) noexcept
        : m_center(center), m_startAngle(startAngleDegrees) {}

    void setCenter(const HPointF& center) noexcept { m_center = center; }
    void setStartAngle(float angleDegrees) noexcept { m_startAngle = angleDegrees; }

    HPointF center() const noexcept { return m_center; }
    float startAngle() const noexcept { return m_startAngle; }

private:
    HPointF m_center;
    float m_startAngle = 0.0f;
};

} // namespace Ht
