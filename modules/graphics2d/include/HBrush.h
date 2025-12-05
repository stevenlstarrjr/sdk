#pragma once

#include "HColor.h"

namespace Ht {

/**
 * @brief HBrush defines how shapes are filled
 * Qt Equivalent: QBrush
 * Skia Backend: SkPaint (fill style) + SkShader
 */
class HBrush {
public:
    enum class Style {
        NoBrush,
        SolidPattern,
        Dense1Pattern,
        Dense2Pattern,
        Dense3Pattern,
        Dense4Pattern,
        Dense5Pattern,
        Dense6Pattern,
        Dense7Pattern,
        HorPattern,
        VerPattern,
        CrossPattern,
        BDiagPattern,
        FDiagPattern,
        DiagCrossPattern
    };

    // Constructors
    HBrush() noexcept : m_color(HColor::Black()), m_style(Style::NoBrush) {}

    explicit HBrush(const HColor& color, Style style = Style::SolidPattern) noexcept
        : m_color(color), m_style(style) {}

    explicit HBrush(Style style) noexcept
        : m_color(HColor::Black()), m_style(style) {}

    // Accessors
    HColor color() const noexcept { return m_color; }
    void setColor(const HColor& color) noexcept { m_color = color; }

    Style style() const noexcept { return m_style; }
    void setStyle(Style style) noexcept { m_style = style; }

    // Comparison
    bool operator==(const HBrush& other) const noexcept {
        return m_color == other.m_color && m_style == other.m_style;
    }

    bool operator!=(const HBrush& other) const noexcept {
        return !(*this == other);
    }

private:
    HColor m_color;
    Style m_style;
};

} // namespace Ht
