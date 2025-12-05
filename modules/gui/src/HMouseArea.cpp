#include "HMouseArea.h"

namespace Ht {

struct HMouseArea::MouseImpl {
    bool enabled = true;
    bool hovered = false;
    bool pressed = false;

    int pressX = 0;
    int pressY = 0;

    ClickCallback clickCallback;
    PressCallback pressCallback;
    ReleaseCallback releaseCallback;
    HoverCallback hoverCallback;
};

HMouseArea::HMouseArea()
    : HItem(), m_mouseImpl(std::make_unique<MouseImpl>()) {
}

HMouseArea::HMouseArea(HItem* parent)
    : HItem(parent), m_mouseImpl(std::make_unique<MouseImpl>()) {
}

HMouseArea::~HMouseArea() = default;

void HMouseArea::setEnabled(bool enabled) {
    m_mouseImpl->enabled = enabled;
}

bool HMouseArea::enabled() const {
    return m_mouseImpl->enabled;
}

void HMouseArea::onClicked(ClickCallback callback) {
    m_mouseImpl->clickCallback = std::move(callback);
}

void HMouseArea::onPressed(PressCallback callback) {
    m_mouseImpl->pressCallback = std::move(callback);
}

void HMouseArea::onReleased(ReleaseCallback callback) {
    m_mouseImpl->releaseCallback = std::move(callback);
}

void HMouseArea::onHoverChanged(HoverCallback callback) {
    m_mouseImpl->hoverCallback = std::move(callback);
}

bool HMouseArea::isHovered() const {
    return m_mouseImpl->hovered;
}

bool HMouseArea::isPressed() const {
    return m_mouseImpl->pressed;
}

void HMouseArea::handlePress(int x, int y) {
    if (!m_mouseImpl->enabled) {
        return;
    }

    m_mouseImpl->pressed = true;
    m_mouseImpl->pressX = x;
    m_mouseImpl->pressY = y;

    if (m_mouseImpl->pressCallback) {
        m_mouseImpl->pressCallback(x, y);
    }
}

void HMouseArea::handleRelease(int x, int y) {
    if (!m_mouseImpl->enabled) {
        return;
    }

    bool wasPressed = m_mouseImpl->pressed;
    m_mouseImpl->pressed = false;

    if (m_mouseImpl->releaseCallback) {
        m_mouseImpl->releaseCallback(x, y);
    }

    // If released in the same area where it was pressed, trigger click
    if (wasPressed && m_mouseImpl->clickCallback) {
        m_mouseImpl->clickCallback();
    }
}

void HMouseArea::handleHover(bool entered) {
    if (!m_mouseImpl->enabled) {
        return;
    }

    if (m_mouseImpl->hovered != entered) {
        m_mouseImpl->hovered = entered;
        if (m_mouseImpl->hoverCallback) {
            m_mouseImpl->hoverCallback(entered);
        }
    }
}

HMouseArea::MouseImpl* HMouseArea::mouseImpl() const {
    return m_mouseImpl.get();
}

} // namespace Ht
