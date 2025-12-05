#pragma once

#include <memory>
#include <string>

namespace Ht {

class HFontMetrics;

/**
 * @brief HFont represents a font for text rendering
 * Qt Equivalent: QFont
 * Skia Backend: SkFont + SkTypeface
 *
 * Loads fonts directly from file paths, bypassing font manager
 */
class HFont {
public:
    enum class Weight {
        Thin = 100,
        ExtraLight = 200,
        Light = 300,
        Normal = 400,
        Medium = 500,
        SemiBold = 600,
        Bold = 700,
        ExtraBold = 800,
        Black = 900
    };

    enum class Style {
        Normal,
        Italic,
        Oblique
    };

    // Constructors
    HFont();
    HFont(const std::string& family, float pointSize);
    ~HFont();

    // Copy and move
    HFont(const HFont& other);
    HFont& operator=(const HFont& other);
    HFont(HFont&& other) noexcept;
    HFont& operator=(HFont&& other) noexcept;

    // Load from file path
    bool loadFromFile(const std::string& filepath);

    // Static factory for loading from file
    static HFont fromFile(const std::string& filepath, float pointSize = 12.0f);

    // Font family
    std::string family() const;
    void setFamily(const std::string& family);

    // Point size (user-facing size)
    float pointSize() const;
    void setPointSize(float pointSize);

    // Pixel size (actual rendering size)
    float pixelSize() const;
    void setPixelSize(float pixelSize);

    // Weight
    Weight weight() const;
    void setWeight(Weight weight);

    // Style
    Style style() const;
    void setStyle(Style style);

    // Bold/Italic shortcuts
    bool bold() const;
    void setBold(bool bold);

    bool italic() const;
    void setItalic(bool italic);

    // Font metrics
    HFontMetrics metrics() const;

    // Hinting
    bool hinting() const;
    void setHinting(bool enable);

    // Anti-aliasing
    bool antiAlias() const;
    void setAntiAlias(bool enable);

    // Subpixel positioning
    bool subpixel() const;
    void setSubpixel(bool enable);

    // Embedded bitmaps
    bool embeddedBitmaps() const;
    void setEmbeddedBitmaps(bool enable);

    // Check if font is valid
    bool isValid() const;

    // Comparison
    bool operator==(const HFont& other) const;
    bool operator!=(const HFont& other) const { return !(*this == other); }

    // Internal Skia access
    struct Impl;
    Impl* impl() const { return m_impl.get(); }

private:
    std::unique_ptr<Impl> m_impl;
};

} // namespace Ht
