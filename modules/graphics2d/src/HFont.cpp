#include "HFont.h"
#include "HFontMetrics.h"
#include "private/HFontImpl.h"
#include "include/core/SkFont.h"
#include "include/core/SkTypeface.h"
#include "include/core/SkFontStyle.h"
#include "include/core/SkFontMetrics.h"
#include "include/core/SkFontTypes.h"
#include "include/core/SkFontMgr.h"
#include "include/core/SkData.h"
#include "include/core/SkStream.h"
#include "include/core/SkSpan.h"
#include "include/ports/SkFontMgr_data.h"
#include <cmath>

namespace Ht {

// Point to pixel conversion (assuming 72 DPI standard)
static constexpr float POINTS_TO_PIXELS = 96.0f / 72.0f;

// HFont::Impl implementation
HFont::Impl::Impl() {
    // Create default typeface - use empty to get default
    typeface = SkTypeface::MakeEmpty();
    if (!typeface) {
        typeface = nullptr; // Will use Skia's internal default
    }
    font.setTypeface(typeface);
    font.setSize(pointSizeValue * POINTS_TO_PIXELS);
    updateFontSettings();
}

HFont::Impl::Impl(const Impl& other)
    : font(other.font)
    , typeface(other.typeface)
    , familyName(other.familyName)
    , pointSizeValue(other.pointSizeValue)
    , weightValue(other.weightValue)
    , styleValue(other.styleValue)
{
}

void HFont::Impl::updateFromPointSize() {
    font.setSize(pointSizeValue * POINTS_TO_PIXELS);
}

void HFont::Impl::updateFontSettings() {
    font.setEdging(SkFont::Edging::kAntiAlias);
    font.setHinting(SkFontHinting::kNormal);
    font.setSubpixel(true);
}

SkFontStyle::Weight HFont::Impl::toSkWeight(HFont::Weight weight) {
    return static_cast<SkFontStyle::Weight>(static_cast<int>(weight));
}

SkFontStyle::Slant HFont::Impl::toSkSlant(HFont::Style style) {
    switch (style) {
        case HFont::Style::Italic: return SkFontStyle::kItalic_Slant;
        case HFont::Style::Oblique: return SkFontStyle::kOblique_Slant;
        default: return SkFontStyle::kUpright_Slant;
    }
}

bool HFont::Impl::loadTypefaceFromFile(const std::string& filepath) {
    // Load font data from file
    sk_sp<SkData> fontData = SkData::MakeFromFileName(filepath.c_str());
    if (!fontData) {
        return false;
    }

    // Create a custom font manager with this single font data
    // This uses FreeType and doesn't depend on system font configuration
    sk_sp<SkData> fonts[] = { fontData };
    sk_sp<SkFontMgr> fontMgr = SkFontMgr_New_Custom_Data(SkSpan(fonts, 1));
    if (!fontMgr) {
        return false;
    }

    // Get the first (and only) typeface from the font manager
    typeface = fontMgr->makeFromData(fontData);
    if (!typeface) {
        return false;
    }

    font.setTypeface(typeface);

    // Extract family name
    SkString familySkStr;
    typeface->getFamilyName(&familySkStr);
    familyName = familySkStr.c_str();

    return true;
}

// HFont implementation
HFont::HFont() : m_impl(std::make_unique<Impl>()) {}

HFont::HFont(const std::string& family, float pointSize) : m_impl(std::make_unique<Impl>()) {
    m_impl->familyName = family;
    m_impl->pointSizeValue = pointSize;
    m_impl->updateFromPointSize();
}

HFont::~HFont() = default;

HFont::HFont(const HFont& other) : m_impl(std::make_unique<Impl>(*other.m_impl)) {}

HFont& HFont::operator=(const HFont& other) {
    if (this != &other) {
        m_impl = std::make_unique<Impl>(*other.m_impl);
    }
    return *this;
}

HFont::HFont(HFont&& other) noexcept = default;
HFont& HFont::operator=(HFont&& other) noexcept = default;

bool HFont::loadFromFile(const std::string& filepath) {
    return m_impl->loadTypefaceFromFile(filepath);
}

HFont HFont::fromFile(const std::string& filepath, float pointSize) {
    HFont font;
    font.setPointSize(pointSize);
    if (!font.loadFromFile(filepath)) {
        // Return invalid font
    }
    return font;
}

std::string HFont::family() const {
    return m_impl->familyName;
}

void HFont::setFamily(const std::string& family) {
    m_impl->familyName = family;
}

float HFont::pointSize() const {
    return m_impl->pointSizeValue;
}

void HFont::setPointSize(float pointSize) {
    m_impl->pointSizeValue = pointSize;
    m_impl->updateFromPointSize();
}

float HFont::pixelSize() const {
    return m_impl->font.getSize();
}

void HFont::setPixelSize(float pixelSize) {
    m_impl->font.setSize(pixelSize);
    m_impl->pointSizeValue = pixelSize / POINTS_TO_PIXELS;
}

HFont::Weight HFont::weight() const {
    return m_impl->weightValue;
}

void HFont::setWeight(Weight weight) {
    m_impl->weightValue = weight;
}

HFont::Style HFont::style() const {
    return m_impl->styleValue;
}

void HFont::setStyle(Style style) {
    m_impl->styleValue = style;
}

bool HFont::bold() const {
    return static_cast<int>(m_impl->weightValue) >= 700;
}

void HFont::setBold(bool bold) {
    m_impl->weightValue = bold ? Weight::Bold : Weight::Normal;
}

bool HFont::italic() const {
    return m_impl->styleValue == Style::Italic;
}

void HFont::setItalic(bool italic) {
    m_impl->styleValue = italic ? Style::Italic : Style::Normal;
}

HFontMetrics HFont::metrics() const {
    return HFontMetrics(*this);
}

bool HFont::hinting() const {
    return m_impl->font.getHinting() != SkFontHinting::kNone;
}

void HFont::setHinting(bool enable) {
    m_impl->font.setHinting(enable ? SkFontHinting::kNormal : SkFontHinting::kNone);
}

bool HFont::antiAlias() const {
    return m_impl->font.getEdging() != SkFont::Edging::kAlias;
}

void HFont::setAntiAlias(bool enable) {
    m_impl->font.setEdging(enable ? SkFont::Edging::kAntiAlias : SkFont::Edging::kAlias);
}

bool HFont::subpixel() const {
    return m_impl->font.isSubpixel();
}

void HFont::setSubpixel(bool enable) {
    m_impl->font.setSubpixel(enable);
}

bool HFont::embeddedBitmaps() const {
    return m_impl->font.isEmbeddedBitmaps();
}

void HFont::setEmbeddedBitmaps(bool enable) {
    m_impl->font.setEmbeddedBitmaps(enable);
}

bool HFont::isValid() const {
    return m_impl->typeface != nullptr;
}

bool HFont::operator==(const HFont& other) const {
    return m_impl->typeface == other.m_impl->typeface &&
           m_impl->pointSizeValue == other.m_impl->pointSizeValue &&
           m_impl->weightValue == other.m_impl->weightValue &&
           m_impl->styleValue == other.m_impl->styleValue;
}

// HFontMetrics::Impl implementation
HFontMetrics::Impl::Impl(const HFont& hfont) {
    // Copy font from HFont
    font = hfont.impl()->font;
    updateMetrics();
}

HFontMetrics::Impl::Impl(const Impl& other)
    : font(other.font)
    , metrics(other.metrics)
{
}

void HFontMetrics::Impl::updateMetrics() {
    font.getMetrics(&metrics);
}

// HFontMetrics implementation
HFontMetrics::HFontMetrics(const HFont& font) : m_impl(std::make_unique<Impl>(font)) {}

HFontMetrics::~HFontMetrics() = default;

HFontMetrics::HFontMetrics(const HFontMetrics& other)
    : m_impl(std::make_unique<Impl>(*other.m_impl)) {}

HFontMetrics& HFontMetrics::operator=(const HFontMetrics& other) {
    if (this != &other) {
        m_impl = std::make_unique<Impl>(*other.m_impl);
    }
    return *this;
}

HFontMetrics::HFontMetrics(HFontMetrics&& other) noexcept = default;
HFontMetrics& HFontMetrics::operator=(HFontMetrics&& other) noexcept = default;

float HFontMetrics::ascent() const {
    return -m_impl->metrics.fAscent; // Skia returns negative ascent
}

float HFontMetrics::descent() const {
    return m_impl->metrics.fDescent;
}

float HFontMetrics::height() const {
    return ascent() + descent() + leading();
}

float HFontMetrics::leading() const {
    return m_impl->metrics.fLeading;
}

float HFontMetrics::averageCharWidth() const {
    return m_impl->metrics.fAvgCharWidth;
}

float HFontMetrics::maxCharWidth() const {
    return m_impl->metrics.fMaxCharWidth;
}

float HFontMetrics::horizontalAdvance(const std::string& text) const {
    return m_impl->font.measureText(text.c_str(), text.length(), SkTextEncoding::kUTF8);
}

float HFontMetrics::horizontalAdvance(char ch) const {
    return horizontalAdvance(std::string(1, ch));
}

float HFontMetrics::boundingRectWidth(const std::string& text) const {
    SkRect bounds;
    m_impl->font.measureText(text.c_str(), text.length(), SkTextEncoding::kUTF8, &bounds);
    return bounds.width();
}

float HFontMetrics::lineSpacing() const {
    return height();
}

float HFontMetrics::underlinePosition() const {
    // fUnderlinePosition is a float, not optional
    return m_impl->metrics.fUnderlinePosition != 0.0f
        ? m_impl->metrics.fUnderlinePosition
        : descent() / 2.0f;
}

float HFontMetrics::underlineThickness() const {
    // fUnderlineThickness is a float, not optional
    return m_impl->metrics.fUnderlineThickness != 0.0f
        ? m_impl->metrics.fUnderlineThickness
        : m_impl->font.getSize() / 12.0f;
}

float HFontMetrics::strikeOutPosition() const {
    // fStrikeoutPosition is a float, not optional
    return m_impl->metrics.fStrikeoutPosition != 0.0f
        ? m_impl->metrics.fStrikeoutPosition
        : -ascent() / 2.0f;
}

} // namespace Ht
