#pragma once

#include "HItem.h"
#include <functional>

namespace Ht {

/**
 * @brief HMouseArea is an invisible primitive that captures mouse events
 * QML Equivalent: MouseArea
 *
 * Use this to make items interactive (clickable, hoverable, etc.)
 */
class HMouseArea : public HItem {
public:
    using ClickCallback = std::function<void()>;
    using PressCallback = std::function<void(int x, int y)>;
    using ReleaseCallback = std::function<void(int x, int y)>;
    using HoverCallback = std::function<void(bool entered)>;

    HMouseArea();
    explicit HMouseArea(HItem* parent);
    ~HMouseArea() override;

    // Enable/disable mouse area
    void setEnabled(bool enabled);
    bool enabled() const;

    // Callbacks
    void onClicked(ClickCallback callback);
    void onPressed(PressCallback callback);
    void onReleased(ReleaseCallback callback);
    void onHoverChanged(HoverCallback callback);

    // State
    bool isHovered() const;
    bool isPressed() const;

    // Internal event handling (called by window system)
    void handlePress(int x, int y);
    void handleRelease(int x, int y);
    void handleHover(bool entered);

    // Internal access
    struct MouseImpl;
    MouseImpl* mouseImpl() const;

private:
    std::unique_ptr<MouseImpl> m_mouseImpl;
};

} // namespace Ht
