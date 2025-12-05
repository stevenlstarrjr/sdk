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
    
    // Cached geometry from Yoga layout
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;

    Impl();
    ~Impl();
};

} // namespace Ht
