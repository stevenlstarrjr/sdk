#pragma once

#include "HItem.h"
#include "HColor.h"

namespace Ht {

class HRectangle : public HItem {
public:
    HRectangle(HItem* parent = nullptr);
    HRectangle(const HColor& color, HItem* parent = nullptr);
    virtual ~HRectangle();

    void setColor(const HColor& color);
    const HColor& color() const;

    void setBorderColor(const HColor& color);
    const HColor& borderColor() const;

    void setBorderWidth(float width);
    float borderWidth() const;

    void setBorderRadius(float radius);
    float borderRadius() const;

    // Override paintContent to draw the rectangle
    void paintContent(HPainter& painter) override;

private:
    struct Impl;
    std::unique_ptr<Impl> m_rectImpl;
};

} // namespace Ht
