#include "HRectangle.h"
#include "HPainter.h"
#include "HRectF.h"
#include "HPen.h"

namespace Ht {

struct HRectangle::Impl {
    HColor color = HColor::White();
    HColor borderColor = HColor::Black();
    float borderWidth = 0.0f;
    float borderRadius = 0.0f;
};

HRectangle::HRectangle(HItem* parent)
    : HItem(parent)
    , m_rectImpl(std::make_unique<Impl>()) {
}

HRectangle::HRectangle(const HColor& color, HItem* parent)
    : HItem(parent)
    , m_rectImpl(std::make_unique<Impl>()) {
    m_rectImpl->color = color;
}

HRectangle::~HRectangle() = default;

void HRectangle::setColor(const HColor& color) {
    m_rectImpl->color = color;
}

const HColor& HRectangle::color() const {
    return m_rectImpl->color;
}

void HRectangle::setBorderColor(const HColor& color) {
    m_rectImpl->borderColor = color;
}

const HColor& HRectangle::borderColor() const {
    return m_rectImpl->borderColor;
}

void HRectangle::setBorderWidth(float width) {
    m_rectImpl->borderWidth = width;
}

float HRectangle::borderWidth() const {
    return m_rectImpl->borderWidth;
}

void HRectangle::setBorderRadius(float radius) {
    m_rectImpl->borderRadius = radius;
}

float HRectangle::borderRadius() const {
    return m_rectImpl->borderRadius;
}

void HRectangle::paintContent(HPainter& painter) {
    // Draw background
    if (m_rectImpl->borderWidth > 0) {
        HPen pen(m_rectImpl->borderColor);
        pen.setWidth(m_rectImpl->borderWidth);
        painter.setPen(pen);
    } else {
        painter.setPen(HPen(HPen::Style::NoPen));
    }

    painter.setBrush(m_rectImpl->color);

    // Draw rect at (0,0) with size (width, height)
    // The painter is already translated to item's position
    HRectF rect(0, 0, static_cast<float>(width()), static_cast<float>(height()));
    
    if (m_rectImpl->borderRadius > 0) {
        painter.drawRoundedRect(rect, m_rectImpl->borderRadius, m_rectImpl->borderRadius);
    } else {
        painter.drawRect(rect);
    }
}

} // namespace Ht
