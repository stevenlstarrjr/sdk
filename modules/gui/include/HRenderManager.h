#pragma once

#include "HObject.h"
#include <memory>
#include <vector>

namespace Ht {

class HSceneGraph;
class HRect;
class HItem;
class HImage;

class HRenderManager : public HObject {
public:
    HRenderManager();
    ~HRenderManager();

    void setSceneGraph(HSceneGraph* sceneGraph);
    void render(class HPainter& painter);

    // Dirty region management
    void markDirty(const HRect& rect);
    void clearDirtyRegions();
    bool hasDirtyRegions() const;
    const std::vector<HRect>& dirtyRegions() const;

    // Cache management
    void cacheItem(HItem* item, const HImage& image);
    bool hasCachedItem(HItem* item) const;
    const HImage* getCachedItem(HItem* item) const;
    void invalidateCache(HItem* item);
    void clearAllCaches();

    // Internal implementation details
    struct Impl;
    Impl* impl() const { return m_impl.get(); }

private:
    std::unique_ptr<Impl> m_impl;
};

} // namespace Ht
