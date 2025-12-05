#pragma once

#include "HLayout.h"
#include <vector>

// Forward declare Yoga types
typedef struct YGNode* YGNodeRef;
typedef struct YGConfig* YGConfigRef;

namespace Ht {

/**
 * @brief Private implementation for HLayout
 * Wraps Yoga layout engine (YGNode)
 */
struct HLayout::LayoutImpl {
    YGConfigRef yogaConfig = nullptr;
    YGNodeRef yogaNode = nullptr;

    std::vector<HItem*> widgets;
    HItem* parentItem = nullptr;  // The HItem that owns this layout

    // Root layout frame in parent coordinates
    float rootX = 0.0f;
    float rootY = 0.0f;
    float rootWidth = 0.0f;
    float rootHeight = 0.0f;
    bool hasRootSize = false;

    int spacing = 0;
    int marginLeft = 0;
    int marginTop = 0;
    int marginRight = 0;
    int marginBottom = 0;

    bool needsUpdate = true;

    LayoutImpl();
    ~LayoutImpl();

    void updateYogaMargins();
};

} // namespace Ht
