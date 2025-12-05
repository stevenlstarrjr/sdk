#include "HImage.h"
#include "private/HImageImpl.h"
#include "HPainter.h"
#include "include/core/SkBitmap.h"
#include "include/core/SkImage.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkSurface.h"
#include "include/core/SkData.h"
#include "include/encode/SkPngEncoder.h"
#include "include/encode/SkJpegEncoder.h"
#include "include/codec/SkCodec.h"
#include <fstream>

namespace Ht {

// Impl conversion functions
SkColorType HImage::Impl::toSkColorType(HImage::Format format) {
    switch (format) {
        case HImage::Format::ARGB32:
        case HImage::Format::ARGB32_Premul:
            return kBGRA_8888_SkColorType; // Skia uses BGRA order on most platforms
        case HImage::Format::RGB32:
            return kRGB_888x_SkColorType;
        case HImage::Format::RGBA8888:
        case HImage::Format::RGBA8888_Premul:
            return kRGBA_8888_SkColorType;
        case HImage::Format::RGB888:
            return kRGB_888x_SkColorType;
        default:
            return kUnknown_SkColorType;
    }
}

SkAlphaType HImage::Impl::toSkAlphaType(HImage::Format format) {
    switch (format) {
        case HImage::Format::ARGB32_Premul:
        case HImage::Format::RGBA8888_Premul:
            return kPremul_SkAlphaType;
        case HImage::Format::ARGB32:
        case HImage::Format::RGBA8888:
            return kUnpremul_SkAlphaType;
        case HImage::Format::RGB32:
        case HImage::Format::RGB888:
            return kOpaque_SkAlphaType;
        default:
            return kUnknown_SkAlphaType;
    }
}

HImage::Format HImage::Impl::fromSkColorType(SkColorType colorType) {
    switch (colorType) {
        case kBGRA_8888_SkColorType:
            return HImage::Format::ARGB32_Premul;
        case kRGBA_8888_SkColorType:
            return HImage::Format::RGBA8888_Premul;
        case kRGB_888x_SkColorType:
            return HImage::Format::RGB32;
        default:
            return HImage::Format::Invalid;
    }
}

bool HImage::Impl::allocate(int width, int height, HImage::Format fmt) {
    format = fmt;
    SkColorType colorType = toSkColorType(fmt);
    SkAlphaType alphaType = toSkAlphaType(fmt);

    SkImageInfo info = SkImageInfo::Make(width, height, colorType, alphaType);
    if (!bitmap.tryAllocPixels(info)) {
        return false;
    }

    bitmap.eraseColor(SK_ColorTRANSPARENT);
    updateImageFromBitmap();
    return true;
}

void HImage::Impl::updateImageFromBitmap() {
    if (!bitmap.empty()) {
        image = SkImages::RasterFromBitmap(bitmap);
    }
}

SkCanvas* HImage::Impl::getCanvas() {
    if (!surface && !bitmap.empty()) {
        surface = SkSurfaces::WrapPixels(bitmap.pixmap());
    }
    return surface ? surface->getCanvas() : nullptr;
}

// HImage implementation
HImage::HImage() : m_impl(std::make_unique<Impl>()) {}

HImage::HImage(int width, int height, Format format) : m_impl(std::make_unique<Impl>()) {
    m_impl->allocate(width, height, format);
}

HImage::HImage(const HSize& size, Format format) : m_impl(std::make_unique<Impl>()) {
    m_impl->allocate(size.width(), size.height(), format);
}

HImage::~HImage() = default;

HImage::HImage(HImage&& other) noexcept = default;
HImage& HImage::operator=(HImage&& other) noexcept = default;

HImage::HImage(const HImage& other) : m_impl(std::make_unique<Impl>()) {
    if (other.m_impl) {
        m_impl->bitmap = other.m_impl->bitmap;
        m_impl->format = other.m_impl->format;
        m_impl->updateImageFromBitmap();
    }
}

HImage& HImage::operator=(const HImage& other) {
    if (this != &other) {
        if (other.m_impl) {
            m_impl->bitmap = other.m_impl->bitmap;
            m_impl->format = other.m_impl->format;
            m_impl->updateImageFromBitmap();
        }
    }
    return *this;
}

int HImage::width() const {
    return m_impl->bitmap.width();
}

int HImage::height() const {
    return m_impl->bitmap.height();
}

HSize HImage::size() const {
    return HSize(width(), height());
}

HRect HImage::rect() const {
    return HRect(0, 0, width(), height());
}

HImage::Format HImage::format() const {
    return m_impl->format;
}

bool HImage::isNull() const {
    return m_impl->bitmap.empty();
}

HColor HImage::pixelColor(int x, int y) const {
    if (x < 0 || x >= width() || y < 0 || y >= height()) {
        return HColor();
    }
    SkColor color = m_impl->bitmap.getColor(x, y);
    return HColor(color);
}

HColor HImage::pixelColor(const HPoint& point) const {
    return pixelColor(point.x(), point.y());
}

void HImage::setPixelColor(int x, int y, const HColor& color) {
    if (x >= 0 && x < width() && y >= 0 && y < height()) {
        *m_impl->bitmap.getAddr32(x, y) = color.rgba();
        m_impl->updateImageFromBitmap();
    }
}

void HImage::setPixelColor(const HPoint& point, const HColor& color) {
    setPixelColor(point.x(), point.y(), color);
}

void HImage::fill(const HColor& color) {
    m_impl->bitmap.eraseColor(color.rgba());
    m_impl->updateImageFromBitmap();
}

void HImage::fill(uint32_t rgba) {
    m_impl->bitmap.eraseColor(rgba);
    m_impl->updateImageFromBitmap();
}

bool HImage::save(const std::string& filename, const char* format, int quality) const {
    if (isNull()) {
        return false;
    }

    // Determine format from filename extension if not specified
    std::string fmt = format ? format : "";
    if (fmt.empty()) {
        size_t dotPos = filename.find_last_of('.');
        if (dotPos != std::string::npos) {
            fmt = filename.substr(dotPos + 1);
        }
    }

    // Convert to lowercase
    for (char& c : fmt) {
        c = std::tolower(c);
    }

    // Encode based on format
    sk_sp<SkData> encoded;
    if (fmt == "png") {
        SkPngEncoder::Options options;
        encoded = SkPngEncoder::Encode(nullptr, m_impl->image.get(), options);
    } else if (fmt == "jpg" || fmt == "jpeg") {
        SkJpegEncoder::Options options;
        options.fQuality = quality >= 0 ? quality : 90;
        encoded = SkJpegEncoder::Encode(nullptr, m_impl->image.get(), options);
    } else {
        // Default to PNG
        SkPngEncoder::Options options;
        encoded = SkPngEncoder::Encode(nullptr, m_impl->image.get(), options);
    }

    if (!encoded) {
        return false;
    }

    // Write to file
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        return false;
    }

    file.write(reinterpret_cast<const char*>(encoded->data()), encoded->size());
    return file.good();
}

bool HImage::load(const std::string& filename, const char* /*format*/) {
    sk_sp<SkData> data = SkData::MakeFromFileName(filename.c_str());
    if (!data) {
        return false;
    }

    std::unique_ptr<SkCodec> codec = SkCodec::MakeFromData(data);
    if (!codec) {
        return false;
    }

    SkImageInfo info = codec->getInfo();
    if (!m_impl->bitmap.tryAllocPixels(info)) {
        return false;
    }

    SkCodec::Result result = codec->getPixels(info, m_impl->bitmap.getPixels(), m_impl->bitmap.rowBytes());
    if (result != SkCodec::kSuccess) {
        return false;
    }

    m_impl->format = Impl::fromSkColorType(info.colorType());
    m_impl->updateImageFromBitmap();
    return true;
}

HImage HImage::fromFile(const std::string& filename, const char* format) {
    HImage image;
    image.load(filename, format);
    return image;
}

HImage HImage::scaled(int width, int height) const {
    if (isNull()) {
        return HImage();
    }

    HImage result(width, height, m_impl->format);
    SkCanvas* canvas = result.m_impl->getCanvas();
    if (!canvas) {
        return HImage();
    }

    SkPaint paint;
    paint.setAntiAlias(true);
    canvas->scale(static_cast<float>(width) / this->width(),
                  static_cast<float>(height) / this->height());
    canvas->drawImage(m_impl->image, 0, 0, SkSamplingOptions(), &paint);
    result.m_impl->updateImageFromBitmap();
    return result;
}

HImage HImage::scaled(const HSize& size) const {
    return scaled(size.width(), size.height());
}

HImage HImage::copy(const HRect& rect) const {
    if (isNull()) {
        return HImage();
    }

    HRect r = rect.isNull() ? this->rect() : rect;
    HImage result(r.width(), r.height(), m_impl->format);

    SkIRect skRect = SkIRect::MakeXYWH(r.x(), r.y(), r.width(), r.height());
    if (m_impl->bitmap.extractSubset(&result.m_impl->bitmap, skRect)) {
        result.m_impl->updateImageFromBitmap();
    }

    return result;
}

const void* HImage::constBits() const {
    return m_impl->bitmap.getPixels();
}

void* HImage::bits() {
    return m_impl->bitmap.getPixels();
}

int HImage::bytesPerLine() const {
    return m_impl->bitmap.rowBytes();
}

} // namespace Ht
