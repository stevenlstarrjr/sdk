#pragma once

#include <memory>
#include <string>

namespace Ht {

class HFont;

/**
 * @brief HFontMetrics provides font measurements
 * Qt Equivalent: QFontMetrics / QFontMetricsF
 * Skia Backend: SkFontMetrics
 */
class HFontMetrics {
public:
    HFontMetrics(const HFont& font);
    ~HFontMetrics();

    // Copy and move
    HFontMetrics(const HFontMetrics& other);
    HFontMetrics& operator=(const HFontMetrics& other);
    HFontMetrics(HFontMetrics&& other) noexcept;
    HFontMetrics& operator=(HFontMetrics&& other) noexcept;

    // Vertical metrics
    float ascent() const;   // Distance from baseline to top
    float descent() const;  // Distance from baseline to bottom
    float height() const;   // Total line height (ascent + descent + leading)
    float leading() const;  // Extra space between lines

    // Horizontal metrics
    float averageCharWidth() const;
    float maxCharWidth() const;

    // Text measurements
    float horizontalAdvance(const std::string& text) const;
    float horizontalAdvance(char ch) const;

    // Bounding rectangles (for precise layout)
    // Returns width of tight bounding box
    float boundingRectWidth(const std::string& text) const;

    // Line spacing (height to use for line layout)
    float lineSpacing() const;

    // Underline/strikeout positions
    float underlinePosition() const;
    float underlineThickness() const;
    float strikeOutPosition() const;

    // Internal implementation
    struct Impl;
    Impl* impl() const { return m_impl.get(); }

private:
    std::unique_ptr<Impl> m_impl;
};

} // namespace Ht
