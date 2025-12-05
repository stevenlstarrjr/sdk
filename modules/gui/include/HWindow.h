#pragma once

#include <memory>
#include <string>
#include <functional>
#include <vector>

namespace Ht {

class HApplication;
class HColor;
class HPen;
class HPainter;
class HRect;
class HPoint;
class HItem;
class HMouseArea;
struct HKeyEvent;

/**
 * @brief HWindow represents a top-level application window.
 * Qt Equivalent: QWindow
 * Wayland Backend: wl_surface + xdg_surface/toplevel (client-side)
 *
 * Beyond Qt: Provides visual customization not available in Qt:
 * - Rounded corners with customizable radius
 * - Border stroke styling
 * - Drop shadows
 * - Custom paint callbacks for full drawing control
 */
class HWindow {
public:
    // Paint callback: receives painter and window dimensions
    using PaintCallback = std::function<void(HPainter&, int width, int height)>;
    explicit HWindow(HApplication* app);
    ~HWindow();

    HWindow(const HWindow&) = delete;
    HWindow& operator=(const HWindow&) = delete;
    HWindow(HWindow&&) noexcept;
    HWindow& operator=(HWindow&&) noexcept;

    // Basic properties
    void setTitle(const std::string& title);
    const std::string& title() const;

    int width() const;
    int height() const;

    // Geometry
    void resize(int width, int height);

    // Show/hide
    void show();
    void hide();
    void update();  // Request repaint

    // Visual customization (beyond Qt capabilities)
    void setBorderRadius(float radius);
    float borderRadius() const;

    void setBorderPen(const HPen& pen);
    const HPen& borderPen() const;

    void setBackgroundColor(const HColor& color);
    const HColor& backgroundColor() const;

    // Drop shadow
    void setDropShadowEnabled(bool enabled);
    bool dropShadowEnabled() const;

    void setDropShadowOffset(float x, float y);
    float dropShadowOffsetX() const;
    float dropShadowOffsetY() const;

    void setDropShadowBlurRadius(float radius);
    float dropShadowBlurRadius() const;

    void setDropShadowColor(const HColor& color);
    const HColor& dropShadowColor() const;

    // Custom paint callback
    void setPaintCallback(PaintCallback callback);
    void clearPaintCallback();

    // Draggable regions (for titlebar-like window dragging)
    void setDraggableRegion(const HRect& region);
    void addDraggableRegion(const HRect& region);
    void clearDraggableRegions();

    // Central item (for layout-based rendering)
    // Content item
    void setContent(HItem* item);
    HItem* content() const;

    // Window Padding (Space between window border/shadow and central item)
    void setPadding(int left, int top, int right, int bottom);
    void setPadding(int padding);
    void getPadding(int* left, int* top, int* right, int* bottom) const;

    // Focus management
    void setFocusItem(HItem* item);
    HItem* focusItem() const;

    // Event dispatch
    void dispatchKeyEvent(HKeyEvent& event);

    // Mouse event routing helpers (internal use by HApplication)
    static HMouseArea* findMouseAreaAt(HItem* rootItem, int x, int y);

    // Internal access
    struct Impl;
    Impl* impl() const { return m_impl.get(); }

private:
    std::unique_ptr<Impl> m_impl;
};

} // namespace Ht
