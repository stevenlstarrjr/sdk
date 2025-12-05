#pragma once

#include "HItem.h"

namespace Ht {

/**
 * @brief HLayout is a specialized HItem that acts as a container.
 * In the new Yoga-first design, any HItem can be a container.
 * HLayout provides convenience methods for common layout patterns (Box, Grid, etc.)
 * and manages child items.
 */
class HLayout : public HItem {
public:
    HLayout(HItem* parent = nullptr);
    virtual ~HLayout();

    // Add a widget to the layout
    void addWidget(HItem* widget);
    
    // Add a widget with specific flex properties
    void addWidget(HItem* widget, float flexGrow);

    // Spacing (Gap)
    void setSpacing(int spacing);
    int spacing() const;

    // Direction
    enum class Direction { Row, Column, RowReverse, ColumnReverse };
    void setDirection(Direction dir);
    Direction direction() const;

    // Justify Content
    enum class Justify { FlexStart, Center, FlexEnd, SpaceBetween, SpaceAround, SpaceEvenly };
    void setJustifyContent(Justify justify);
    Justify justifyContent() const;

    // Align Items
    enum class AlignItems { Auto, FlexStart, Center, FlexEnd, Stretch, Baseline, SpaceBetween, SpaceAround };
    void setAlignItems(AlignItems align);
    AlignItems alignItems() const;

    // Wrap
    enum class Wrap { NoWrap, Wrap, WrapReverse };
    void setWrap(Wrap wrap);
    Wrap wrap() const;

private:
    struct Impl;
    std::unique_ptr<Impl> m_layoutImpl;
};

} // namespace Ht
