#pragma once

#include <cstdint>
#include <string_view>

namespace Ht {

/**
 * @brief HColor represents a color in RGBA format
 * Qt Equivalent: QColor
 * Skia Backend: SkColor, SkColor4f
 */
class HColor {
public:
    // Constructors
    constexpr HColor() noexcept : m_rgba(0xFF000000) {} // Opaque black
    constexpr HColor(uint32_t rgba) noexcept : m_rgba(rgba) {}
    constexpr HColor(int r, int g, int b, int a = 255) noexcept
        : m_rgba(((a & 0xFF) << 24) | ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF)) {}

    // RGB Accessors (0-255)
    constexpr int red() const noexcept { return (m_rgba >> 16) & 0xFF; }
    constexpr int green() const noexcept { return (m_rgba >> 8) & 0xFF; }
    constexpr int blue() const noexcept { return m_rgba & 0xFF; }
    constexpr int alpha() const noexcept { return (m_rgba >> 24) & 0xFF; }

    constexpr void setRed(int r) noexcept {
        m_rgba = (m_rgba & 0xFF00FFFF) | ((r & 0xFF) << 16);
    }
    constexpr void setGreen(int g) noexcept {
        m_rgba = (m_rgba & 0xFFFF00FF) | ((g & 0xFF) << 8);
    }
    constexpr void setBlue(int b) noexcept {
        m_rgba = (m_rgba & 0xFFFFFF00) | (b & 0xFF);
    }
    constexpr void setAlpha(int a) noexcept {
        m_rgba = (m_rgba & 0x00FFFFFF) | ((a & 0xFF) << 24);
    }

    // RGB Float accessors (0.0-1.0)
    constexpr float redF() const noexcept { return red() / 255.0f; }
    constexpr float greenF() const noexcept { return green() / 255.0f; }
    constexpr float blueF() const noexcept { return blue() / 255.0f; }
    constexpr float alphaF() const noexcept { return alpha() / 255.0f; }

    constexpr void setRedF(float r) noexcept { setRed(static_cast<int>(r * 255.0f)); }
    constexpr void setGreenF(float g) noexcept { setGreen(static_cast<int>(g * 255.0f)); }
    constexpr void setBlueF(float b) noexcept { setBlue(static_cast<int>(b * 255.0f)); }
    constexpr void setAlphaF(float a) noexcept { setAlpha(static_cast<int>(a * 255.0f)); }

    // Set RGB
    constexpr void setRgb(int r, int g, int b, int a = 255) noexcept {
        m_rgba = ((a & 0xFF) << 24) | ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF);
    }

    constexpr void setRgbF(float r, float g, float b, float a = 1.0f) noexcept {
        setRgb(static_cast<int>(r * 255.0f),
               static_cast<int>(g * 255.0f),
               static_cast<int>(b * 255.0f),
               static_cast<int>(a * 255.0f));
    }

    // Raw RGBA value
    constexpr uint32_t rgba() const noexcept { return m_rgba; }
    constexpr void setRgba(uint32_t rgba) noexcept { m_rgba = rgba; }

    // Validity
    constexpr bool isValid() const noexcept { return true; }

    // Comparison
    constexpr bool operator==(const HColor& other) const noexcept {
        return m_rgba == other.m_rgba;
    }
    constexpr bool operator!=(const HColor& other) const noexcept {
        return m_rgba != other.m_rgba;
    }

    // Named colors (static factory methods)
    static constexpr HColor fromRgb(int r, int g, int b, int a = 255) noexcept {
        return HColor(r, g, b, a);
    }

    static constexpr HColor fromRgbF(float r, float g, float b, float a = 1.0f) noexcept {
        return HColor(static_cast<int>(r * 255.0f),
                     static_cast<int>(g * 255.0f),
                     static_cast<int>(b * 255.0f),
                     static_cast<int>(a * 255.0f));
    }

    static constexpr HColor fromRgba(uint32_t rgba) noexcept {
        return HColor(rgba);
    }

    // Parse hex color strings: "#RGB", "#RRGGBB", "#RRGGBBAA"
    static HColor fromHex(std::string_view hex) noexcept;

    // Standard colors
    static constexpr HColor Black() noexcept { return HColor(0, 0, 0); }
    static constexpr HColor White() noexcept { return HColor(255, 255, 255); }
    static constexpr HColor Red() noexcept { return HColor(255, 0, 0); }
    static constexpr HColor Green() noexcept { return HColor(0, 255, 0); }
    static constexpr HColor Blue() noexcept { return HColor(0, 0, 255); }
    static constexpr HColor Yellow() noexcept { return HColor(255, 255, 0); }
    static constexpr HColor Cyan() noexcept { return HColor(0, 255, 255); }
    static constexpr HColor Magenta() noexcept { return HColor(255, 0, 255); }
    static constexpr HColor Gray() noexcept { return HColor(128, 128, 128); }
    static constexpr HColor DarkGray() noexcept { return HColor(64, 64, 64); }
    static constexpr HColor LightGray() noexcept { return HColor(192, 192, 192); }
    static constexpr HColor Transparent() noexcept { return HColor(0, 0, 0, 0); }

    // Lighter/Darker
    HColor lighter(int factor = 150) const noexcept;
    HColor darker(int factor = 200) const noexcept;

private:
    uint32_t m_rgba; // ARGB format: AA RR GG BB
};

} // namespace Ht
