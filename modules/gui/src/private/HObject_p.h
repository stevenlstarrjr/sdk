#pragma once

#include "HObject.h"
#include <unordered_map>
#include <vector>

namespace Ht {

struct HObject::Impl {
    HObject* parent = nullptr;
    std::vector<HObject*> children;
    std::string objectName;

    // Signal-slot connections
    // Map from signal name -> list of (connectionId, slot function)
    std::unordered_map<std::string, std::vector<std::pair<int, SlotFunction>>> connections;
    int nextConnectionId = 1;

    Impl() = default;
    ~Impl() = default;
};

} // namespace Ht
