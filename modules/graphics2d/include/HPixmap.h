#pragma once

#include "HImage.h"

namespace Ht {

/**
 * @brief HPixmap represents an image optimized for on-screen drawing.
 * Qt Equivalent: QPixmap
 * Skia Backend: SkImage (GPU-capable)
 *
 * Currently implemented as a thin wrapper around HImage. GPU-backed
 * pixmaps will be introduced when HPaintDevice backends are added.
 */
class HPixmap {
public:
    HPixmap() = default;
    explicit HPixmap(const HSize& size)
        : m_image(size, HImage::Format::ARGB32_Premul) {}
    explicit HPixmap(int width, int height)
        : m_image(width, height, HImage::Format::ARGB32_Premul) {}

    bool isNull() const { return m_image.isNull(); }

    int width() const { return m_image.width(); }
    int height() const { return m_image.height(); }
    HSize size() const { return m_image.size(); }

    // Conversion to/from HImage raster data
    static HPixmap fromImage(const HImage& image) {
        HPixmap p;
        p.m_image = image;
        return p;
    }

    HImage toImage() const { return m_image; }

private:
    HImage m_image;
};

} // namespace Ht

