#include "HColor.h"
#include <algorithm>
#include <cstdlib>

namespace Ht {

// Helper function to parse hex digit
static int parseHexDigit(char c) noexcept {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return 0;
}

HColor HColor::fromHex(std::string_view hex) noexcept {
    // Remove leading '#' if present
    if (!hex.empty() && hex[0] == '#') {
        hex.remove_prefix(1);
    }

    // Handle different formats
    if (hex.size() == 3) {
        // #RGB -> #RRGGBB
        int r = parseHexDigit(hex[0]) * 17; // 0xF -> 0xFF
        int g = parseHexDigit(hex[1]) * 17;
        int b = parseHexDigit(hex[2]) * 17;
        return HColor(r, g, b, 255);
    }
    else if (hex.size() == 6) {
        // #RRGGBB
        int r = (parseHexDigit(hex[0]) << 4) | parseHexDigit(hex[1]);
        int g = (parseHexDigit(hex[2]) << 4) | parseHexDigit(hex[3]);
        int b = (parseHexDigit(hex[4]) << 4) | parseHexDigit(hex[5]);
        return HColor(r, g, b, 255);
    }
    else if (hex.size() == 8) {
        // #RRGGBBAA
        int r = (parseHexDigit(hex[0]) << 4) | parseHexDigit(hex[1]);
        int g = (parseHexDigit(hex[2]) << 4) | parseHexDigit(hex[3]);
        int b = (parseHexDigit(hex[4]) << 4) | parseHexDigit(hex[5]);
        int a = (parseHexDigit(hex[6]) << 4) | parseHexDigit(hex[7]);
        return HColor(r, g, b, a);
    }

    // Invalid format, return black
    return HColor::Black();
}

HColor HColor::lighter(int factor) const noexcept {
    if (factor <= 0 || factor >= 100 * 256) {
        return *this;
    }

    int r = red();
    int g = green();
    int b = blue();
    int a = alpha();

    // Make color lighter by moving closer to white
    r = std::min(255, (r * factor) / 100);
    g = std::min(255, (g * factor) / 100);
    b = std::min(255, (b * factor) / 100);

    return HColor(r, g, b, a);
}

HColor HColor::darker(int factor) const noexcept {
    if (factor <= 0 || factor >= 100 * 256) {
        return *this;
    }

    int r = red();
    int g = green();
    int b = blue();
    int a = alpha();

    // Make color darker by reducing brightness
    r = (r * 100) / factor;
    g = (g * 100) / factor;
    b = (b * 100) / factor;

    return HColor(r, g, b, a);
}

} // namespace Ht
