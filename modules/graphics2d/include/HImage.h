#pragma once

#include "HSize.h"
#include "HRect.h"
#include "HColor.h"
#include <memory>
#include <string>

namespace Ht {

class HPainter;

/**
 * @brief HImage represents a pixel-based image
 * Qt Equivalent: QImage
 * Skia Backend: SkImage + SkBitmap
 */
class HImage {
public:
    enum class Format {
        Invalid,
        ARGB32,          // 32-bit ARGB
        RGB32,           // 32-bit RGB (alpha ignored)
        ARGB32_Premul,   // 32-bit premultiplied ARGB
        RGB888,          // 24-bit RGB
        RGBA8888,        // 32-bit RGBA
        RGBA8888_Premul  // 32-bit premultiplied RGBA
    };

    // Constructors
    HImage();
    HImage(int width, int height, Format format);
    HImage(const HSize& size, Format format);
    ~HImage();

    // Move semantics
    HImage(HImage&& other) noexcept;
    HImage& operator=(HImage&& other) noexcept;

    // Copy semantics
    HImage(const HImage& other);
    HImage& operator=(const HImage& other);

    // Properties
    int width() const;
    int height() const;
    HSize size() const;
    HRect rect() const;
    Format format() const;
    bool isNull() const;

    // Pixel access
    HColor pixelColor(int x, int y) const;
    HColor pixelColor(const HPoint& point) const;
    void setPixelColor(int x, int y, const HColor& color);
    void setPixelColor(const HPoint& point, const HColor& color);

    // Fill
    void fill(const HColor& color);
    void fill(uint32_t rgba);

    // Save/Load
    bool save(const std::string& filename, const char* format = nullptr, int quality = -1) const;
    bool load(const std::string& filename, const char* format = nullptr);

    // Static load
    static HImage fromFile(const std::string& filename, const char* format = nullptr);

    // Scaling
    HImage scaled(int width, int height) const;
    HImage scaled(const HSize& size) const;

    // Copy region
    HImage copy(const HRect& rect = HRect()) const;

    // Painter access (for drawing into the image)
    bool beginPaint(HPainter& painter);
    void endPaint();

    // Direct pixel data access (advanced)
    const void* constBits() const;
    void* bits();
    int bytesPerLine() const;

    // Internal Skia access (for internal use)
    struct Impl;
    Impl* impl() const { return m_impl.get(); }

private:
    std::unique_ptr<Impl> m_impl;
};

} // namespace Ht
