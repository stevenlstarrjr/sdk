#pragma once

#include "HItem.h"
#include "HColor.h"
#include "HFont.h"
#include <yoga/Yoga.h>

namespace Ht {

class HText : public HItem {
public:
    HText(HItem* parent = nullptr);
    HText(const std::string& text, HItem* parent = nullptr);
    virtual ~HText();

    void setText(const std::string& text);
    const std::string& text() const;

    void setFont(const HFont& font);
    const HFont& font() const;

    void setColor(const HColor& color);
    const HColor& color() const;

    // Override paintContent to draw text
    void paintContent(HPainter& painter) override;

private:
    struct Impl;
    std::unique_ptr<Impl> m_textImpl;
    
    // Yoga measure callback
    static YGSize measureFunc(YGNodeConstRef node, float width, YGMeasureMode widthMode, float height, YGMeasureMode heightMode);
};

} // namespace Ht
