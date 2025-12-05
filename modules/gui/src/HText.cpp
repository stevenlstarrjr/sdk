#include "HText.h"
#include "HPainter.h"
#include "HSize.h"
#include "private/HItem_p.h" // For access to yogaNode
#include <yoga/Yoga.h>

namespace Ht {

struct HText::Impl {
    std::string text;
    HFont font;
    HColor color = HColor::Black();
};

// Static measure callback wrapper
static YGSize yogaMeasureCallback(YGNodeConstRef node, float width, YGMeasureMode widthMode, float height, YGMeasureMode heightMode) {
    // YGNodeGetContext takes YGNodeRef (non-const) usually?
    // If node is const, we might need to cast away constness if GetContext requires non-const.
    // But YGNodeGetContext usually takes YGNodeConstRef in newer versions?
    // Let's check error: "invalid conversion from ... to YGMeasureFunc".
    // We need to match YGMeasureFunc signature.
    
    // If YGNodeGetContext expects non-const, we cast.
    // YGNodeRef nonConstNode = const_cast<YGNodeRef>(node);
    // But let's try with YGNodeConstRef first if GetContext supports it.
    // If not, we cast.
    
    const HText* item = static_cast<const HText*>(YGNodeGetContext(node));
    if (!item) {
        return {0, 0};
    }
    
    // ... (rest of logic)
    
    float w = item->font().pointSize() * 0.6f * item->text().length(); 
    float h = item->font().pointSize() * 1.2f;
    
    return {w, h};
}

HText::HText(HItem* parent)
    : HItem(parent)
    , m_textImpl(std::make_unique<Impl>()) {
    
    // Set measure callback
    if (impl()->yogaNode) {
        YGNodeSetContext(impl()->yogaNode, this);
        YGNodeSetMeasureFunc(impl()->yogaNode, yogaMeasureCallback);
    }
}

HText::HText(const std::string& text, HItem* parent)
    : HItem(parent)
    , m_textImpl(std::make_unique<Impl>()) {
    m_textImpl->text = text;
    
    if (impl()->yogaNode) {
        YGNodeSetContext(impl()->yogaNode, this);
        YGNodeSetMeasureFunc(impl()->yogaNode, yogaMeasureCallback);
    }
}

// ...

void HText::paintContent(HPainter& painter) {
    painter.setPen(m_textImpl->color);
    painter.setFont(m_textImpl->font);
    
    HRectF rect(0, 0, static_cast<float>(width()), static_cast<float>(height()));
    painter.drawText(rect, m_textImpl->text); 
}

} // namespace Ht
