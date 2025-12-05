#pragma once

#include "HObject.h"
#include <memory>

namespace Ht {

class HItem;

class HSceneGraph : public HObject {
public:
    HSceneGraph();
    ~HSceneGraph();

    void setRootItem(HItem* item);
    HItem* rootItem() const;

    // Internal implementation details
    struct Impl;
    Impl* impl() const { return m_impl.get(); }

private:
    std::unique_ptr<Impl> m_impl;
};

} // namespace Ht
