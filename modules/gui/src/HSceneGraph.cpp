#include "HSceneGraph.h"
#include "HItem.h"

namespace Ht {

struct HSceneGraph::Impl {
    HItem* rootItem = nullptr;
};

HSceneGraph::HSceneGraph() : m_impl(std::make_unique<Impl>()) {
}

HSceneGraph::~HSceneGraph() = default;

void HSceneGraph::setRootItem(HItem* item) {
    m_impl->rootItem = item;
}

HItem* HSceneGraph::rootItem() const {
    return m_impl->rootItem;
}

} // namespace Ht
