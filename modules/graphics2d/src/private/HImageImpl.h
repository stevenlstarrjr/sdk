#pragma once

#include "HImage.h"
#include "include/core/SkBitmap.h"
#include "include/core/SkImage.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkSurface.h"
#include <memory>

namespace Ht {

/**
 * @brief Private implementation for HImage
 * Wraps Skia's SkBitmap and SkImage directly
 */
struct HImage::Impl {
    SkBitmap bitmap;
    sk_sp<SkImage> image;
    sk_sp<SkSurface> surface; // For painting operations
    HImage::Format format = HImage::Format::Invalid;

    Impl() = default;

    static SkColorType toSkColorType(HImage::Format format);
    static HImage::Format fromSkColorType(SkColorType colorType);
    static SkAlphaType toSkAlphaType(HImage::Format format);

    bool allocate(int width, int height, HImage::Format fmt);
    void updateImageFromBitmap();
    SkCanvas* getCanvas();
};

} // namespace Ht
