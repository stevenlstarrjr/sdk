#pragma once

#include "HObject.h"
#include <memory>
#include <vector>
#include <string>

namespace Ht {

class HPainter;
class HLayout;
class HRect;
class HPoint;
class HSize;
class HKeyEvent;

/**
 * @brief HItem is the base class for all UI elements.
 * It wraps a Yoga node for layout and handles painting/events.
 */
class HItem : public HObject {
public:
    HItem();
    explicit HItem(HItem* parent);
    virtual ~HItem();

    // -- Geometry (Read-only, calculated by Layout) --
    int x() const;
    int y() const;
    int width() const;
    int height() const;
    HRect geometry() const;

    // -- Layout Configuration (Yoga) --
    
    // Position Type
    enum class PositionType { Relative, Absolute };
    void setPositionType(PositionType type);
    PositionType positionType() const;

    // Flex Properties
    void setFlexGrow(float grow);
    float flexGrow() const;
    void setFlexShrink(float shrink);
    float flexShrink() const;
    void setFlexBasis(float basis);
    float flexBasis() const;

    // Alignment
    enum class Align {
        Auto, FlexStart, Center, FlexEnd, Stretch, Baseline, SpaceBetween, SpaceAround
    };
    void setAlignSelf(Align align);
    Align alignSelf() const;

    // Margins
    void setMargin(int left, int top, int right, int bottom);
    void setMargin(int margin);
    int marginLeft() const;
    int marginTop() const;
    int marginRight() const;
    int marginBottom() const;

    // Padding
    void setPadding(int left, int top, int right, int bottom);
    void setPadding(int padding);
    int paddingLeft() const;
    int paddingTop() const;
    int paddingRight() const;
    int paddingBottom() const;

    // Position (for Absolute or Relative offsets)
    void setTop(int top);
    void setLeft(int left);
    void setRight(int right);
    void setBottom(int bottom);
    int top() const;
    int left() const;
    int right() const;
    int bottom() const;

    // Sizing Constraints
    void setWidth(int w);
    void setHeight(int h);
    void setMinWidth(int w);
    void setMinHeight(int h);
    void setMaxWidth(int w);
    void setMaxHeight(int h);
    
    // Fixed size helper
    void setFixedSize(int w, int h);

    // -- Hierarchy --
    HItem* parentItem() const;
    void setParent(HItem* parent); // Overrides HObject::setParent to handle Yoga tree
    const std::vector<HItem*>& childItems() const;
    void addChild(HItem* child); // Overrides HObject::addChild
    void removeChild(HItem* child); // Overrides HObject::removeChild

    // -- Painting --
    void paint(HPainter& painter); // Recursive paint
    virtual void paintContent(HPainter& painter); // Custom content painting

    // -- Events --
    virtual void onGeometryChanged();
    
    // Input Events
    virtual void onKeyPress(HKeyEvent& event);
    virtual void onKeyRelease(HKeyEvent& event);
    
    // Focus
    void setFocus(bool focus);
    bool hasFocus() const;
    
    // -- Visibility --
    bool isVisible() const;
    void setVisible(bool visible);
    void show();
    void hide();

    // -- Internal --
    struct Impl;
    Impl* impl() const { return m_impl.get(); }

    // Sync Yoga layout results to internal geometry
    void updateLayout();

protected:
    std::unique_ptr<Impl> m_impl;
};

} // namespace Ht
