#include "HRenderManager.h"
#include "HSceneGraph.h"
#include "HItem.h"
#include "HPainter.h"
#include "HRect.h"
#include "HImage.h"
#include <iostream>
#include <map>
#include <algorithm>

namespace Ht {

struct HRenderManager::Impl {
    HSceneGraph* sceneGraph = nullptr;
    std::vector<HRect> dirtyRegions;
    std::map<HItem*, HImage> itemCache;
    bool fullRepaintNeeded = true;
};

HRenderManager::HRenderManager() : m_impl(std::make_unique<Impl>()) {
}

HRenderManager::~HRenderManager() = default;

void HRenderManager::setSceneGraph(HSceneGraph* sceneGraph) {
    m_impl->sceneGraph = sceneGraph;
    m_impl->fullRepaintNeeded = true;
}

// Helper: Collect all dirty items recursively
static void collectDirtyItems(HItem* item, std::vector<HItem*>& dirtyItems, int offsetX = 0, int offsetY = 0) {
    if (!item || !item->isVisible()) {
        return;
    }

    if (item->isDirty()) {
        dirtyItems.push_back(item);
    }

    const int absX = offsetX + item->x();
    const int absY = offsetY + item->y();

    for (HItem* child : item->childItems()) {
        collectDirtyItems(child, dirtyItems, absX, absY);
    }
}

// Helper: Calculate absolute bounds of an item in window coordinates
static HRect getAbsoluteBounds(HItem* item, HItem* root) {
    int absX = 0;
    int absY = 0;

    HItem* current = item;
    while (current && current != root) {
        absX += current->x();
        absY += current->y();
        current = current->parentItem();
    }

    return HRect(absX, absY, item->width(), item->height());
}

// Helper: Recursively print and count all items
static void printItemTree(HItem* item, int depth, const std::string& prefix, std::vector<HItem*>& allItems) {
    if (!item) return;

    allItems.push_back(item);

    std::string indent(depth * 2, ' ');
    std::cout << indent << prefix << " Item at (" << item->x() << "," << item->y()
              << ") size " << item->width() << "x" << item->height()
              << " dirty=" << (item->isDirty() ? "YES" : "NO") << std::endl;

    for (HItem* child : item->childItems()) {
        printItemTree(child, depth + 1, "└─", allItems);
    }
}

void HRenderManager::render(HPainter& painter) {
    if (!m_impl->sceneGraph) {
        return;
    }

    HItem* root = m_impl->sceneGraph->rootItem();
    if (!root) {
        return;
    }

    // Check if we need a full repaint or can do partial updates
    if (m_impl->fullRepaintNeeded || m_impl->dirtyRegions.empty()) {
        // Full repaint: render everything
        std::vector<HItem*> allItems;
        printItemTree(root, 0, "Root", allItems);

        std::cout << "    [PAINTING] All " << allItems.size() << " items in scene" << std::endl;

        if (root->isVisible()) {
            painter.save();
            painter.translate(static_cast<float>(root->x()), static_cast<float>(root->y()));
            root->paint(painter);
            painter.restore();
        }

        // Clear dirty flags after rendering
        std::vector<HItem*> dirtyItems;
        collectDirtyItems(root, dirtyItems);
        for (HItem* item : dirtyItems) {
            item->clearDirty();
        }

        m_impl->fullRepaintNeeded = false;
    } else {
        // Partial repaint: only render dirty items

        // Collect all items to show what's being skipped
        std::vector<HItem*> allItems;
        printItemTree(root, 0, "Root", allItems);

        // Collect all dirty items
        std::vector<HItem*> dirtyItems;
        collectDirtyItems(root, dirtyItems);

        if (!dirtyItems.empty()) {
            std::cout << "    [PAINTING] " << dirtyItems.size() << " dirty item(s), "
                      << "[SKIPPED] " << (allItems.size() - dirtyItems.size()) << " clean item(s)" << std::endl;

            // Render each dirty item
            for (HItem* item : dirtyItems) {
                // Calculate absolute position
                HRect bounds = getAbsoluteBounds(item, root);

                std::cout << "      → Repainting item at (" << bounds.x() << "," << bounds.y()
                          << ") size " << bounds.width() << "x" << bounds.height() << std::endl;

                painter.save();
                painter.translate(static_cast<float>(bounds.x()), static_cast<float>(bounds.y()));
                item->paintContent(painter);
                painter.restore();

                item->clearDirty();
            }
        } else {
            std::cout << "    [SKIPPED] All " << allItems.size() << " items (none dirty)" << std::endl;
        }
    }
}

// Dirty region management
void HRenderManager::markDirty(const HRect& rect) {
    m_impl->dirtyRegions.push_back(rect);
}

void HRenderManager::clearDirtyRegions() {
    m_impl->dirtyRegions.clear();
}

bool HRenderManager::hasDirtyRegions() const {
    return !m_impl->dirtyRegions.empty();
}

const std::vector<HRect>& HRenderManager::dirtyRegions() const {
    return m_impl->dirtyRegions;
}

// Cache management
void HRenderManager::cacheItem(HItem* item, const HImage& image) {
    if (item) {
        m_impl->itemCache[item] = image;
    }
}

bool HRenderManager::hasCachedItem(HItem* item) const {
    return item && m_impl->itemCache.find(item) != m_impl->itemCache.end();
}

const HImage* HRenderManager::getCachedItem(HItem* item) const {
    if (item) {
        auto it = m_impl->itemCache.find(item);
        if (it != m_impl->itemCache.end()) {
            return &it->second;
        }
    }
    return nullptr;
}

void HRenderManager::invalidateCache(HItem* item) {
    if (item) {
        auto it = m_impl->itemCache.find(item);
        if (it != m_impl->itemCache.end()) {
            m_impl->itemCache.erase(it);
        }
    }
}

void HRenderManager::clearAllCaches() {
    m_impl->itemCache.clear();
}

} // namespace Ht
