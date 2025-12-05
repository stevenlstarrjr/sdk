#pragma once

#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <unordered_map>

namespace Ht {

/**
 * @brief HObject is the base class for all objects with parent-child relationships and signals/slots
 * Qt Equivalent: QObject
 *
 * Provides:
 * - Parent-child object tree with automatic cleanup
 * - Signal and slot mechanism for event handling
 * - Object naming and identification
 */
class HObject {
public:
    HObject();
    explicit HObject(HObject* parent);
    virtual ~HObject();

    // Disable copy, allow move
    HObject(const HObject&) = delete;
    HObject& operator=(const HObject&) = delete;
    HObject(HObject&&) noexcept;
    HObject& operator=(HObject&&) noexcept;

    // Parent-child relationships
    HObject* parent() const;
    void setParent(HObject* parent);
    const std::vector<HObject*>& children() const;
    void addChild(HObject* child);
    void removeChild(HObject* child);

    // Object identification
    std::string objectName() const;
    void setObjectName(const std::string& name);

    // Signals and slots
    using SlotFunction = std::function<void()>;

    int connect(const std::string& signalName, SlotFunction slot);
    void disconnect(int connectionId);
    void disconnectAll(const std::string& signalName = "");

    // Internal access
    struct Impl;
    Impl* impl() const { return m_impl.get(); }

protected:
    // Emit a signal (call all connected slots)
    void emit(const std::string& signalName);

    std::unique_ptr<Impl> m_impl;
};

} // namespace Ht
