#pragma once

#include "HColor.h"

namespace Ht {

/**
 * @brief HPen defines how outlines are drawn
 * Qt Equivalent: QPen
 * Skia Backend: SkPaint (stroke style)
 */
class HPen {
public:
    enum class Style {
        NoPen,
        SolidLine,
        DashLine,
        DotLine,
        DashDotLine,
        DashDotDotLine
    };

    enum class CapStyle {
        FlatCap,
        SquareCap,
        RoundCap
    };

    enum class JoinStyle {
        MiterJoin,
        BevelJoin,
        RoundJoin
    };

    // Constructors
    HPen() noexcept : m_color(HColor::Black()), m_width(1.0f), m_style(Style::SolidLine),
                      m_capStyle(CapStyle::FlatCap), m_joinStyle(JoinStyle::MiterJoin) {}

    explicit HPen(const HColor& color) noexcept
        : m_color(color), m_width(1.0f), m_style(Style::SolidLine),
          m_capStyle(CapStyle::FlatCap), m_joinStyle(JoinStyle::MiterJoin) {}

    explicit HPen(Style style) noexcept
        : m_color(HColor::Black()), m_width(1.0f), m_style(style),
          m_capStyle(CapStyle::FlatCap), m_joinStyle(JoinStyle::MiterJoin) {}

    HPen(const HColor& color, float width, Style style = Style::SolidLine,
         CapStyle cap = CapStyle::FlatCap, JoinStyle join = JoinStyle::MiterJoin) noexcept
        : m_color(color), m_width(width), m_style(style), m_capStyle(cap), m_joinStyle(join) {}

    // Accessors
    HColor color() const noexcept { return m_color; }
    void setColor(const HColor& color) noexcept { m_color = color; }

    float width() const noexcept { return m_width; }
    float widthF() const noexcept { return m_width; }
    void setWidth(float width) noexcept { m_width = width; }
    void setWidthF(float width) noexcept { m_width = width; }

    Style style() const noexcept { return m_style; }
    void setStyle(Style style) noexcept { m_style = style; }

    CapStyle capStyle() const noexcept { return m_capStyle; }
    void setCapStyle(CapStyle cap) noexcept { m_capStyle = cap; }

    JoinStyle joinStyle() const noexcept { return m_joinStyle; }
    void setJoinStyle(JoinStyle join) noexcept { m_joinStyle = join; }

    // Comparison
    bool operator==(const HPen& other) const noexcept {
        return m_color == other.m_color && m_width == other.m_width &&
               m_style == other.m_style && m_capStyle == other.m_capStyle &&
               m_joinStyle == other.m_joinStyle;
    }

    bool operator!=(const HPen& other) const noexcept {
        return !(*this == other);
    }

private:
    HColor m_color;
    float m_width;
    Style m_style;
    CapStyle m_capStyle;
    JoinStyle m_joinStyle;
};

} // namespace Ht
