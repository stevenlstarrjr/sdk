#pragma once

#include "HItem.h"
#include <vector>

// Forward declare Yoga types
typedef struct YGNode* YGNodeRef;

namespace Ht {

/**
 * @brief Private implementation for HItem
 */
struct HItem::Impl {
    YGNodeRef yogaNode = nullptr;
    bool visible = true;
    bool dirty = false;
    bool hasFocus = false;

    // Cached geometry from Yoga layout
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;

    // Window reference for dirty propagation (set by window when content is added)
    class HWindow* window = nullptr;

    // Layer-based compositing
    std::unique_ptr<class HImage> layer;        // Cached rendering of this item
    bool layerValid = false;                     // Is the cached layer up to date?
    bool needsOwnLayer = false;                  // Does this item need its own layer?

    Impl();
    ~Impl();
};

} // namespace Ht
