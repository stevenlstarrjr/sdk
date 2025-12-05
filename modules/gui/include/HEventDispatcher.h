#pragma once

#include "HObject.h"
#include <memory>

namespace Ht {

class HSceneGraph;
class HEvent;
struct HKeyEvent;

class HEventDispatcher : public HObject {
public:
    HEventDispatcher();
    ~HEventDispatcher();

    void setSceneGraph(HSceneGraph* sceneGraph);
    void setWindow(class HWindow* window);
    void dispatchEvent(HEvent* event);

    // Specific event dispatchers
    void dispatchKeyEvent(struct HKeyEvent& event);

    // Focus management
    void setFocusItem(class HItem* item);
    class HItem* focusItem() const;

    // Internal implementation details
    struct Impl;
    Impl* impl() const { return m_impl.get(); }

private:
    std::unique_ptr<Impl> m_impl;
};

} // namespace Ht
