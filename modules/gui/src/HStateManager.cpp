#include "HStateManager.h"

namespace Ht {

struct HStateManager::Impl {
    std::string currentState;
};

HStateManager::HStateManager() : m_impl(std::make_unique<Impl>()) {
}

HStateManager::~HStateManager() = default;

void HStateManager::setState(const std::string& state) {
    if (m_impl->currentState != state) {
        m_impl->currentState = state;
        // TODO: Emit stateChanged signal
    }
}

std::string HStateManager::currentState() const {
    return m_impl->currentState;
}

} // namespace Ht
