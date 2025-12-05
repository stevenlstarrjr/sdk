#include "HObject.h"
#include "private/HObject_p.h"

#include <algorithm>

namespace Ht {

HObject::HObject()
    : m_impl(std::make_unique<Impl>()) {
}

HObject::HObject(HObject* parent)
    : m_impl(std::make_unique<Impl>()) {
    setParent(parent);
}

HObject::~HObject() {
    // Remove from parent's children list
    if (m_impl->parent) {
        m_impl->parent->removeChild(this);
    }

    // Delete all children (they will remove themselves from our list in their destructor)
    while (!m_impl->children.empty()) {
        delete m_impl->children.back();
    }
}

HObject::HObject(HObject&& other) noexcept
    : m_impl(std::move(other.m_impl)) {
}

HObject& HObject::operator=(HObject&& other) noexcept {
    if (this != &other) {
        m_impl = std::move(other.m_impl);
    }
    return *this;
}

HObject* HObject::parent() const {
    return m_impl->parent;
}

void HObject::setParent(HObject* parent) {
    if (m_impl->parent == parent) {
        return;
    }

    // Remove from old parent
    if (m_impl->parent) {
        m_impl->parent->removeChild(this);
    }

    // Set new parent
    m_impl->parent = parent;

    // Add to new parent's children
    if (parent) {
        parent->addChild(this);
    }
}

const std::vector<HObject*>& HObject::children() const {
    return m_impl->children;
}

void HObject::addChild(HObject* child) {
    if (!child) {
        return;
    }

    // Check if already in children list
    auto it = std::find(m_impl->children.begin(), m_impl->children.end(), child);
    if (it != m_impl->children.end()) {
        return;
    }

    m_impl->children.push_back(child);
}

void HObject::removeChild(HObject* child) {
    if (!child) {
        return;
    }

    auto it = std::find(m_impl->children.begin(), m_impl->children.end(), child);
    if (it != m_impl->children.end()) {
        m_impl->children.erase(it);
    }
}

std::string HObject::objectName() const {
    return m_impl->objectName;
}

void HObject::setObjectName(const std::string& name) {
    m_impl->objectName = name;
}

int HObject::connect(const std::string& signalName, SlotFunction slot) {
    if (!slot) {
        return -1;
    }

    int connectionId = m_impl->nextConnectionId++;
    m_impl->connections[signalName].push_back({connectionId, std::move(slot)});
    return connectionId;
}

void HObject::disconnect(int connectionId) {
    for (auto& [signalName, slots] : m_impl->connections) {
        auto it = std::find_if(slots.begin(), slots.end(),
            [connectionId](const auto& pair) { return pair.first == connectionId; });

        if (it != slots.end()) {
            slots.erase(it);
            return;
        }
    }
}

void HObject::disconnectAll(const std::string& signalName) {
    if (signalName.empty()) {
        m_impl->connections.clear();
    } else {
        m_impl->connections.erase(signalName);
    }
}

void HObject::emit(const std::string& signalName) {
    auto it = m_impl->connections.find(signalName);
    if (it == m_impl->connections.end()) {
        return;
    }

    // Make a copy of the slots list in case a slot modifies the connections
    auto slotsCopy = it->second;
    for (const auto& [id, slot] : slotsCopy) {
        if (slot) {
            slot();
        }
    }
}

} // namespace Ht
