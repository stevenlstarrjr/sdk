#pragma once

#include "HLayout.h"

namespace Ht {

class HBoxLayout : public HLayout {
public:
    enum class Direction { LeftToRight, RightToLeft, TopToBottom, BottomToTop };

    HBoxLayout(Direction dir, HItem* parent = nullptr);
    virtual ~HBoxLayout();

    void addSpacing(int size);
    void addStretch(int stretch = 0);
};

class HHBoxLayout : public HBoxLayout {
public:
    HHBoxLayout(HItem* parent = nullptr);
};

class HVBoxLayout : public HBoxLayout {
public:
    HVBoxLayout(HItem* parent = nullptr);
};

} // namespace Ht
