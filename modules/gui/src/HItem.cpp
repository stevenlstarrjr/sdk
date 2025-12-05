#include "HItem.h"
#include "private/HItem_p.h"
#include "HPainter.h"
#include <yoga/Yoga.h>
#include <algorithm>
#include <iostream>

namespace Ht {

// -- Impl -------------------------------------------------------------------

// -- Impl -------------------------------------------------------------------

HItem::Impl::Impl() {
    yogaNode = YGNodeNew();
}

HItem::Impl::~Impl() {
    if (yogaNode) {
        YGNodeFree(yogaNode);
        yogaNode = nullptr;
    }
}

// -- HItem ------------------------------------------------------------------

HItem::HItem()
    : HObject()
    , m_impl(std::make_unique<Impl>()) {
}

HItem::HItem(HItem* parent)
    : HObject(parent)
    , m_impl(std::make_unique<Impl>()) {
    // Note: HObject constructor calls setParent(parent), which calls addChild/removeChild.
    // However, since m_impl is not initialized when HObject ctor runs, 
    // we might need to handle Yoga node attachment here or in setParent override.
    // Actually, HObject ctor sets parent member but doesn't call virtual setParent?
    // Let's check HObject. usually it does.
    // If HObject calls setParent, and setParent is virtual, it calls HItem::setParent.
    // But m_impl is not init yet! Crash risk.
    // Standard fix: Don't pass parent to HObject ctor, call setParent after m_impl init.
    // But HObject(parent) is standard.
    // Let's assume HObject ctor does NOT call virtual setParent but just adds to children.
    // We need to ensure Yoga nodes are connected.
    if (parent) {
        // Manually trigger Yoga attachment since HObject ctor might have missed it
        // or we need to ensure it happens after m_impl init.
        // Actually, HObject ctor adds to parent's children list.
        // We need to add our yoga node to parent's yoga node.
        if (parent->impl() && parent->impl()->yogaNode) {
            YGNodeInsertChild(parent->impl()->yogaNode, m_impl->yogaNode, YGNodeGetChildCount(parent->impl()->yogaNode));
        }
    }
}

HItem::~HItem() = default;

// -- Geometry ---------------------------------------------------------------

int HItem::x() const { return m_impl->x; }
int HItem::y() const { return m_impl->y; }
int HItem::width() const { return m_impl->width; }
int HItem::height() const { return m_impl->height; }

HRect HItem::geometry() const {
    return HRect(m_impl->x, m_impl->y, m_impl->width, m_impl->height);
}

// -- Layout Configuration ---------------------------------------------------

void HItem::setPositionType(PositionType type) {
    YGNodeStyleSetPositionType(m_impl->yogaNode, 
        type == PositionType::Absolute ? YGPositionTypeAbsolute : YGPositionTypeRelative);
}

HItem::PositionType HItem::positionType() const {
    return YGNodeStyleGetPositionType(m_impl->yogaNode) == YGPositionTypeAbsolute ? 
           PositionType::Absolute : PositionType::Relative;
}

void HItem::setFlexGrow(float grow) {
    YGNodeStyleSetFlexGrow(m_impl->yogaNode, grow);
}

float HItem::flexGrow() const {
    return YGNodeStyleGetFlexGrow(m_impl->yogaNode);
}

void HItem::setFlexShrink(float shrink) {
    YGNodeStyleSetFlexShrink(m_impl->yogaNode, shrink);
}

float HItem::flexShrink() const {
    return YGNodeStyleGetFlexShrink(m_impl->yogaNode);
}

void HItem::setFlexBasis(float basis) {
    YGNodeStyleSetFlexBasis(m_impl->yogaNode, basis);
}

float HItem::flexBasis() const {
    return YGNodeStyleGetFlexBasis(m_impl->yogaNode).value;
}

void HItem::setAlignSelf(Align align) {
    YGAlign a = YGAlignAuto;
    switch (align) {
        case Align::Auto: a = YGAlignAuto; break;
        case Align::FlexStart: a = YGAlignFlexStart; break;
        case Align::Center: a = YGAlignCenter; break;
        case Align::FlexEnd: a = YGAlignFlexEnd; break;
        case Align::Stretch: a = YGAlignStretch; break;
        case Align::Baseline: a = YGAlignBaseline; break;
        case Align::SpaceBetween: a = YGAlignSpaceBetween; break;
        case Align::SpaceAround: a = YGAlignSpaceAround; break;
    }
    YGNodeStyleSetAlignSelf(m_impl->yogaNode, a);
}

HItem::Align HItem::alignSelf() const {
    // Simplified mapping back
    return Align::Auto; 
}

void HItem::setMargin(int left, int top, int right, int bottom) {
    YGNodeStyleSetMargin(m_impl->yogaNode, YGEdgeLeft, static_cast<float>(left));
    YGNodeStyleSetMargin(m_impl->yogaNode, YGEdgeTop, static_cast<float>(top));
    YGNodeStyleSetMargin(m_impl->yogaNode, YGEdgeRight, static_cast<float>(right));
    YGNodeStyleSetMargin(m_impl->yogaNode, YGEdgeBottom, static_cast<float>(bottom));
}

void HItem::setMargin(int margin) {
    setMargin(margin, margin, margin, margin);
}

int HItem::marginLeft() const { return static_cast<int>(YGNodeStyleGetMargin(m_impl->yogaNode, YGEdgeLeft).value); }
int HItem::marginTop() const { return static_cast<int>(YGNodeStyleGetMargin(m_impl->yogaNode, YGEdgeTop).value); }
int HItem::marginRight() const { return static_cast<int>(YGNodeStyleGetMargin(m_impl->yogaNode, YGEdgeRight).value); }
int HItem::marginBottom() const { return static_cast<int>(YGNodeStyleGetMargin(m_impl->yogaNode, YGEdgeBottom).value); }

void HItem::setPadding(int left, int top, int right, int bottom) {
    YGNodeStyleSetPadding(m_impl->yogaNode, YGEdgeLeft, static_cast<float>(left));
    YGNodeStyleSetPadding(m_impl->yogaNode, YGEdgeTop, static_cast<float>(top));
    YGNodeStyleSetPadding(m_impl->yogaNode, YGEdgeRight, static_cast<float>(right));
    YGNodeStyleSetPadding(m_impl->yogaNode, YGEdgeBottom, static_cast<float>(bottom));
}

void HItem::setPadding(int padding) {
    setPadding(padding, padding, padding, padding);
}

int HItem::paddingLeft() const { return static_cast<int>(YGNodeStyleGetPadding(m_impl->yogaNode, YGEdgeLeft).value); }
int HItem::paddingTop() const { return static_cast<int>(YGNodeStyleGetPadding(m_impl->yogaNode, YGEdgeTop).value); }
int HItem::paddingRight() const { return static_cast<int>(YGNodeStyleGetPadding(m_impl->yogaNode, YGEdgeRight).value); }
int HItem::paddingBottom() const { return static_cast<int>(YGNodeStyleGetPadding(m_impl->yogaNode, YGEdgeBottom).value); }

void HItem::setTop(int top) { YGNodeStyleSetPosition(m_impl->yogaNode, YGEdgeTop, static_cast<float>(top)); }
void HItem::setLeft(int left) { YGNodeStyleSetPosition(m_impl->yogaNode, YGEdgeLeft, static_cast<float>(left)); }
void HItem::setRight(int right) { YGNodeStyleSetPosition(m_impl->yogaNode, YGEdgeRight, static_cast<float>(right)); }
void HItem::setBottom(int bottom) { YGNodeStyleSetPosition(m_impl->yogaNode, YGEdgeBottom, static_cast<float>(bottom)); }

int HItem::top() const { return static_cast<int>(YGNodeStyleGetPosition(m_impl->yogaNode, YGEdgeTop).value); }
int HItem::left() const { return static_cast<int>(YGNodeStyleGetPosition(m_impl->yogaNode, YGEdgeLeft).value); }
int HItem::right() const { return static_cast<int>(YGNodeStyleGetPosition(m_impl->yogaNode, YGEdgeRight).value); }
int HItem::bottom() const { return static_cast<int>(YGNodeStyleGetPosition(m_impl->yogaNode, YGEdgeBottom).value); }

void HItem::setWidth(int w) { YGNodeStyleSetWidth(m_impl->yogaNode, static_cast<float>(w)); }
void HItem::setHeight(int h) { YGNodeStyleSetHeight(m_impl->yogaNode, static_cast<float>(h)); }
void HItem::setMinWidth(int w) { YGNodeStyleSetMinWidth(m_impl->yogaNode, static_cast<float>(w)); }
void HItem::setMinHeight(int h) { YGNodeStyleSetMinHeight(m_impl->yogaNode, static_cast<float>(h)); }
void HItem::setMaxWidth(int w) { YGNodeStyleSetMaxWidth(m_impl->yogaNode, static_cast<float>(w)); }
void HItem::setMaxHeight(int h) { YGNodeStyleSetMaxHeight(m_impl->yogaNode, static_cast<float>(h)); }

void HItem::setFixedSize(int w, int h) {
    setWidth(w);
    setHeight(h);
}

// -- Hierarchy --------------------------------------------------------------

HItem* HItem::parentItem() const {
    return static_cast<HItem*>(parent());
}

void HItem::setParent(HItem* parent) {
    HItem* oldParent = parentItem();
    if (oldParent == parent) return;

    if (oldParent) {
        oldParent->removeChild(this);
    }
    
    HObject::setParent(parent);
    
    if (parent) {
        // HObject::setParent calls parent->addChild(this) usually?
        // If so, addChild will handle Yoga node insertion.
        // If not, we do it here.
        // Let's assume HObject::setParent does NOT call addChild on parent, 
        // but just sets the parent pointer and adds to children list.
        // We need to ensure Yoga node is moved.
        // Actually, safest is to rely on addChild/removeChild.
        // If HObject::setParent calls addChild, we are good.
        // If not, we need to manually manage Yoga.
        // Let's assume we need to manage it.
        if (parent->impl() && parent->impl()->yogaNode && m_impl->yogaNode) {
             // Check if already added?
             if (YGNodeGetOwner(m_impl->yogaNode) != parent->impl()->yogaNode) {
                 YGNodeInsertChild(parent->impl()->yogaNode, m_impl->yogaNode, YGNodeGetChildCount(parent->impl()->yogaNode));
             }
        }
    }
}

const std::vector<HItem*>& HItem::childItems() const {
    return reinterpret_cast<const std::vector<HItem*>&>(children());
}

void HItem::addChild(HItem* child) {
    HObject::addChild(child);
    if (child && child->impl() && child->impl()->yogaNode && m_impl->yogaNode) {
        // Append child to the end
        if (YGNodeGetOwner(child->impl()->yogaNode) != m_impl->yogaNode) {
            YGNodeInsertChild(m_impl->yogaNode, child->impl()->yogaNode, YGNodeGetChildCount(m_impl->yogaNode));
        }
    }
}

void HItem::removeChild(HItem* child) {
    if (child && child->impl() && child->impl()->yogaNode && m_impl->yogaNode) {
        YGNodeRemoveChild(m_impl->yogaNode, child->impl()->yogaNode);
    }
    HObject::removeChild(child);
}

// -- Painting ---------------------------------------------------------------

void HItem::paint(HPainter& painter) {
    if (!isVisible()) return;

    // 1. Draw self
    paintContent(painter);

    // 2. Draw children
    for (HItem* child : childItems()) {
        if (child->isVisible()) {
            painter.save();
            painter.translate(static_cast<float>(child->x()), static_cast<float>(child->y()));
            child->paint(painter);
            painter.restore();
        }
    }
}

void HItem::paintContent(HPainter& painter) {
    // Default: do nothing
    (void)painter;
}

// -- Events -----------------------------------------------------------------

void HItem::onGeometryChanged() {}

void HItem::onKeyPress(HKeyEvent& event) {
    (void)event;
}

void HItem::onKeyRelease(HKeyEvent& event) {
    (void)event;
}

void HItem::setFocus(bool focus) {
    // TODO: Notify window or application?
    // For now just store state if needed, but HItem doesn't have focus state in Impl yet.
    // Let's add it to Impl if needed, or just ignore for now.
    // But HWindow calls setFocus(true/false).
}

bool HItem::hasFocus() const {
    return false; // TODO
}

// -- Visibility -------------------------------------------------------------

bool HItem::isVisible() const { return m_impl->visible; }
void HItem::setVisible(bool visible) { m_impl->visible = visible; }
void HItem::show() { setVisible(true); }
void HItem::hide() { setVisible(false); }

// -- Internal ---------------------------------------------------------------

void HItem::updateLayout() {
    if (m_impl->yogaNode) {
        float l = YGNodeLayoutGetLeft(m_impl->yogaNode);
        float t = YGNodeLayoutGetTop(m_impl->yogaNode);
        float w = YGNodeLayoutGetWidth(m_impl->yogaNode);
        float h = YGNodeLayoutGetHeight(m_impl->yogaNode);

        bool changed = (m_impl->x != (int)l || m_impl->y != (int)t || m_impl->width != (int)w || m_impl->height != (int)h);

        m_impl->x = static_cast<int>(l);
        m_impl->y = static_cast<int>(t);
        m_impl->width = static_cast<int>(w);
        m_impl->height = static_cast<int>(h);

        if (changed) {
            onGeometryChanged();
        }
    }

    for (HItem* child : childItems()) {
        child->updateLayout();
    }
}

} // namespace Ht
