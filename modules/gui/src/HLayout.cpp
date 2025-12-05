#include "HLayout.h"
#include "private/HItem_p.h"
#include <yoga/Yoga.h>

namespace Ht {

struct HLayout::Impl {
    // No extra state needed for now, just Yoga node config
};

HLayout::HLayout(HItem* parent)
    : HItem(parent)
    , m_layoutImpl(std::make_unique<Impl>()) {
    // Default to Column layout? Or Row?
    // Let's default to Column as it's common.
    setDirection(Direction::Column);
}

HLayout::~HLayout() = default;

void HLayout::addWidget(HItem* widget) {
    if (widget) {
        widget->setParent(this);
    }
}

void HLayout::addWidget(HItem* widget, float flexGrow) {
    if (widget) {
        widget->setParent(this);
        widget->setFlexGrow(flexGrow);
    }
}

void HLayout::setSpacing(int spacing) {
    // Set gap for both rows and columns
    YGNodeStyleSetGap(impl()->yogaNode, YGGutterAll, static_cast<float>(spacing));
}

int HLayout::spacing() const {
    return static_cast<int>(YGNodeStyleGetGap(impl()->yogaNode, YGGutterAll));
}

void HLayout::setDirection(Direction dir) {
    YGFlexDirection d = YGFlexDirectionColumn;
    switch (dir) {
        case Direction::Row: d = YGFlexDirectionRow; break;
        case Direction::Column: d = YGFlexDirectionColumn; break;
        case Direction::RowReverse: d = YGFlexDirectionRowReverse; break;
        case Direction::ColumnReverse: d = YGFlexDirectionColumnReverse; break;
    }
    YGNodeStyleSetFlexDirection(impl()->yogaNode, d);
}

HLayout::Direction HLayout::direction() const {
    YGFlexDirection d = YGNodeStyleGetFlexDirection(impl()->yogaNode);
    switch (d) {
        case YGFlexDirectionRow: return Direction::Row;
        case YGFlexDirectionColumn: return Direction::Column;
        case YGFlexDirectionRowReverse: return Direction::RowReverse;
        case YGFlexDirectionColumnReverse: return Direction::ColumnReverse;
        default: return Direction::Column;
    }
}

void HLayout::setJustifyContent(Justify justify) {
    YGJustify j = YGJustifyFlexStart;
    switch (justify) {
        case Justify::FlexStart: j = YGJustifyFlexStart; break;
        case Justify::Center: j = YGJustifyCenter; break;
        case Justify::FlexEnd: j = YGJustifyFlexEnd; break;
        case Justify::SpaceBetween: j = YGJustifySpaceBetween; break;
        case Justify::SpaceAround: j = YGJustifySpaceAround; break;
        case Justify::SpaceEvenly: j = YGJustifySpaceEvenly; break;
    }
    YGNodeStyleSetJustifyContent(impl()->yogaNode, j);
}

HLayout::Justify HLayout::justifyContent() const {
    // Simplified mapping
    return Justify::FlexStart; 
}

void HLayout::setAlignItems(AlignItems align) {
    YGAlign a = YGAlignStretch;
    switch (align) {
        case AlignItems::Auto: a = YGAlignAuto; break;
        case AlignItems::FlexStart: a = YGAlignFlexStart; break;
        case AlignItems::Center: a = YGAlignCenter; break;
        case AlignItems::FlexEnd: a = YGAlignFlexEnd; break;
        case AlignItems::Stretch: a = YGAlignStretch; break;
        case AlignItems::Baseline: a = YGAlignBaseline; break;
        case AlignItems::SpaceBetween: a = YGAlignSpaceBetween; break;
        case AlignItems::SpaceAround: a = YGAlignSpaceAround; break;
    }
    YGNodeStyleSetAlignItems(impl()->yogaNode, a);
}

HLayout::AlignItems HLayout::alignItems() const {
    // Simplified mapping
    return AlignItems::Stretch;
}

void HLayout::setWrap(Wrap wrap) {
    YGWrap w = YGWrapNoWrap;
    switch (wrap) {
        case Wrap::NoWrap: w = YGWrapNoWrap; break;
        case Wrap::Wrap: w = YGWrapWrap; break;
        case Wrap::WrapReverse: w = YGWrapWrapReverse; break;
    }
    YGNodeStyleSetFlexWrap(impl()->yogaNode, w);
}

HLayout::Wrap HLayout::wrap() const {
    return Wrap::NoWrap;
}

} // namespace Ht
