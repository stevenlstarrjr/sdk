#pragma once

#include "HPaintDevice.h"
#include "HImage.h"

namespace Ht {

/**
 * @brief CPU raster paint device backed by HImage.
 * Skia Backend: SkSurface::MakeRaster
 */
class HRasterPaintDevice : public HPaintDevice {
public:
    explicit HRasterPaintDevice(const HSize& size)
        : m_image(size, HImage::Format::ARGB32_Premul) {}

    explicit HRasterPaintDevice(int width, int height)
        : m_image(width, height, HImage::Format::ARGB32_Premul) {}

    HSize size() const override { return m_image.size(); }

    HImage& image() { return m_image; }
    const HImage& image() const { return m_image; }

    HImage* asImage() override { return &m_image; }
    const HImage* asImage() const override { return &m_image; }

private:
    HImage m_image;
};

} // namespace Ht
