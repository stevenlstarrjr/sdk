#pragma once

#include "HObject.h"
#include <memory>
#include <string>

namespace Ht {

class HStateManager : public HObject {
public:
    HStateManager();
    ~HStateManager();

    void setState(const std::string& state);
    std::string currentState() const;

    // Internal implementation details
    struct Impl;
    Impl* impl() const { return m_impl.get(); }

private:
    std::unique_ptr<Impl> m_impl;
};

} // namespace Ht
