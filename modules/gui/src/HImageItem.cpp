#include "HImageItem.h"
#include "HPainter.h"
#include "HRectF.h"

namespace Ht {

struct HImageItem::Impl {
    HImage image;
};

HImageItem::HImageItem(HItem* parent)
    : HItem(parent)
    , m_imageImpl(std::make_unique<Impl>()) {
}

HImageItem::HImageItem(const HImage& image, HItem* parent)
    : HItem(parent)
    , m_imageImpl(std::make_unique<Impl>()) {
    setImage(image);
}

HImageItem::HImageItem(const std::string& path, HItem* parent)
    : HItem(parent)
    , m_imageImpl(std::make_unique<Impl>()) {
    load(path);
}

HImageItem::~HImageItem() = default;

void HImageItem::setImage(const HImage& image) {
    m_imageImpl->image = image;
    // Set implicit size?
    // In Yoga, we might want to set a preferred size or aspect ratio.
    // For now, let's just set the size if it's not set.
    // But HItem doesn't have "isSizeSet".
    // Let's just set the size to image size.
    if (!image.isNull()) {
        setFixedSize(image.width(), image.height());
    }
}

const HImage& HImageItem::image() const {
    return m_imageImpl->image;
}

void HImageItem::load(const std::string& path) {
    HImage img;
    if (img.load(path)) {
        setImage(img);
    }
}

void HImageItem::paintContent(HPainter& painter) {
    if (m_imageImpl->image.isNull()) return;

    // Draw image to fill the item
    HRectF targetRect(0, 0, static_cast<float>(width()), static_cast<float>(height()));
    HRectF sourceRect(0, 0, static_cast<float>(m_imageImpl->image.width()), static_cast<float>(m_imageImpl->image.height()));
    
    // painter.drawImage(targetRect, m_imageImpl->image, sourceRect);
    // TODO: HPainter::drawImage is missing. Implement it in graphics2d module.
}

} // namespace Ht
