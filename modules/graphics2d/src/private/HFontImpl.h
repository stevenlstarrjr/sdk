#pragma once

#include "HFont.h"
#include "HFontMetrics.h"
#include "include/core/SkFont.h"
#include "include/core/SkTypeface.h"
#include "include/core/SkFontMetrics.h"
#include <string>

namespace Ht {

/**
 * @brief Private implementation for HFont
 * Wraps Skia's SkFont and SkTypeface directly
 */
struct HFont::Impl {
    SkFont font;
    sk_sp<SkTypeface> typeface;

    std::string familyName;
    float pointSizeValue = 12.0f;
    HFont::Weight weightValue = HFont::Weight::Normal;
    HFont::Style styleValue = HFont::Style::Normal;

    Impl();
    Impl(const Impl& other);

    void updateFromPointSize();
    void updateFontSettings();

    static SkFontStyle::Weight toSkWeight(HFont::Weight weight);
    static SkFontStyle::Slant toSkSlant(HFont::Style style);

    bool loadTypefaceFromFile(const std::string& filepath);
};

/**
 * @brief Private implementation for HFontMetrics
 */
struct HFontMetrics::Impl {
    SkFont font;
    SkFontMetrics metrics;

    Impl(const HFont& hfont);
    Impl(const Impl& other);

    void updateMetrics();
};

} // namespace Ht
