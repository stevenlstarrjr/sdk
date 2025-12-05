#include "HBoxLayout.h"

namespace Ht {

HBoxLayout::HBoxLayout(Direction dir, HItem* parent)
    : HLayout(parent) {
    switch (dir) {
        case Direction::LeftToRight: setDirection(HLayout::Direction::Row); break;
        case Direction::RightToLeft: setDirection(HLayout::Direction::RowReverse); break;
        case Direction::TopToBottom: setDirection(HLayout::Direction::Column); break;
        case Direction::BottomToTop: setDirection(HLayout::Direction::ColumnReverse); break;
    }
}

HBoxLayout::~HBoxLayout() = default;

void HBoxLayout::addSpacing(int size) {
    // In Yoga, spacing is usually 'gap' on the container.
    // But addSpacing usually adds a fixed spacer item.
    // We can add an empty HItem with fixed size.
    auto* spacer = new HItem(this);
    if (direction() == HLayout::Direction::Row || direction() == HLayout::Direction::RowReverse) {
        spacer->setWidth(size);
        spacer->setHeight(0); // or auto?
    } else {
        spacer->setWidth(0);
        spacer->setHeight(size);
    }
}

void HBoxLayout::addStretch(int stretch) {
    // Add an empty item with flex grow
    auto* spacer = new HItem(this);
    spacer->setFlexGrow(stretch > 0 ? static_cast<float>(stretch) : 1.0f);
}

// -- HHBoxLayout --

HHBoxLayout::HHBoxLayout(HItem* parent)
    : HBoxLayout(Direction::LeftToRight, parent) {
}

// -- HVBoxLayout --

HVBoxLayout::HVBoxLayout(HItem* parent)
    : HBoxLayout(Direction::TopToBottom, parent) {
}

} // namespace Ht
