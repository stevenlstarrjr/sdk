#include "HEventDispatcher.h"
#include "HSceneGraph.h"
#include "HItem.h"
#include "HInput.h"
#include "HWindow.h"
#include <iostream>

namespace Ht {

struct HEventDispatcher::Impl {
    HSceneGraph* sceneGraph = nullptr;
    class HWindow* window = nullptr;
    class HItem* focusItem = nullptr;
};

HEventDispatcher::HEventDispatcher() : m_impl(std::make_unique<Impl>()) {
}

HEventDispatcher::~HEventDispatcher() = default;

void HEventDispatcher::setSceneGraph(HSceneGraph* sceneGraph) {
    m_impl->sceneGraph = sceneGraph;
}

void HEventDispatcher::setWindow(HWindow* window) {
    m_impl->window = window;
}

void HEventDispatcher::dispatchEvent(HEvent* event) {
    if (m_impl->sceneGraph) {
        // TODO: Implement generic event dispatching logic
    }
}

void HEventDispatcher::dispatchKeyEvent(HKeyEvent& event) {
    if (m_impl->focusItem) {
        if (event.pressed) {
            m_impl->focusItem->onKeyPress(event);
        } else {
            m_impl->focusItem->onKeyRelease(event);
        }
    }
}

void HEventDispatcher::setFocusItem(HItem* item) {
    if (m_impl->focusItem == item) return;

    if (m_impl->focusItem) {
        m_impl->focusItem->setFocus(false);
    }

    m_impl->focusItem = item;

    if (m_impl->focusItem) {
        m_impl->focusItem->setFocus(true);
    }

    // Trigger window repaint when focus changes
    if (m_impl->window) {
        m_impl->window->update();
    }
}

HItem* HEventDispatcher::focusItem() const {
    return m_impl->focusItem;
}

} // namespace Ht
