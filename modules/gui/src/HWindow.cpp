#include "HWindow.h"
#include "private/HWindow_p.h"
#include "HShmBuffer.h"
#include "HInput.h"
#include "HApplication.h"
#include "private/HApplication_p.h"

#include <yoga/Yoga.h>

// graphics2d (HPainter, HImage)
#include "HImage.h"
#include "HPainter.h"
#include "HRectF.h"
#include "HPen.h"
#include "HColor.h"
#include "HRect.h"

// Primitives
#include "HItem.h"
#include "private/HItem_p.h"
#include "HLayout.h"
#include "HMouseArea.h"
#include "HPoint.h"

extern "C" {
#include <wayland-client.h>
#include "xdg-shell-client-protocol.h"
}

#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>

namespace Ht {

namespace {

// Forward declaration of internal helper.
struct RenderContext;


static void xdg_surface_handle_configure(void* data, xdg_surface* surface, uint32_t serial) {
    auto* impl = static_cast<HWindow::Impl*>(data);
    if (!impl || !surface) {
        return;
    }
    // Acknowledge configure; size handling will be added later when needed.
    xdg_surface_ack_configure(surface, serial);
}

static const xdg_surface_listener xdg_surface_listener = {
    .configure = xdg_surface_handle_configure,
};

// Helper to calculate margins reserved for shadows/effects
static void get_shadow_margins(HWindow::Impl* impl, int& left, int& top, int& right, int& bottom) {
    left = top = right = bottom = 0;
    if (impl->dropShadowEnabled) {
        const float blurMargin = impl->dropShadowBlurRadius;
        left = static_cast<int>(std::ceil(std::max(0.0f, blurMargin - impl->dropShadowOffsetX)));
        top = static_cast<int>(std::ceil(std::max(0.0f, blurMargin - impl->dropShadowOffsetY)));
        right = static_cast<int>(std::ceil(std::max(0.0f, blurMargin + impl->dropShadowOffsetX)));
        bottom = static_cast<int>(std::ceil(std::max(0.0f, blurMargin + impl->dropShadowOffsetY)));
    }
}

// Helper to calculate total margins (shadow + padding)
static void get_total_margins(HWindow::Impl* impl, int& left, int& top, int& right, int& bottom) {
    get_shadow_margins(impl, left, top, right, bottom);
    left += impl->paddingLeft;
    top += impl->paddingTop;
    right += impl->paddingRight;
    bottom += impl->paddingBottom;
}

// Internal helper: render current window contents and commit to Wayland.
static void render_frame(HWindow::Impl* impl) {
    if (!impl || !impl->surface || !impl->app || !impl->app->impl()->display) {
        return;
    }

    // Ensure layout is up-to-date before rendering
    if (impl->centralItem) {
        // Calculate Yoga layout for the entire tree
        YGNodeCalculateLayout(impl->centralItem->impl()->yogaNode,
                              static_cast<float>(impl->width),
                              static_cast<float>(impl->height),
                              YGDirectionLTR);

        // Sync Yoga results to HItem geometry
        impl->centralItem->updateLayout();
    }

    const int w = impl->width;
    const int h = impl->height;

    if (w <= 0 || h <= 0) {
        return;
    }

    // Check if we need full repaint or can do partial update
    bool sizeChanged = !impl->framebuffer ||
                       impl->framebuffer->width() != w ||
                       impl->framebuffer->height() != h;
    bool doFullRepaint = impl->needsFullRepaint;
    bool doSmartResize = sizeChanged && !doFullRepaint && impl->framebuffer;

    // Determine dirty regions for Wayland damage reporting
    std::vector<HRect> damageRegions;

    if (doSmartResize) {
        std::cout << "========================================" << std::endl;
        std::cout << "render_frame: SMART RESIZE (" << impl->prevWidth << "x" << impl->prevHeight
                  << " → " << w << "x" << h << ")" << std::endl;
        std::cout << "========================================" << std::endl;

        // Preserve old framebuffer
        impl->oldFramebuffer = std::move(impl->framebuffer);

        // Allocate new framebuffer
        impl->framebuffer = std::make_unique<HImage>(w, h, HImage::Format::ARGB32_Premul);

        {
            HPainter painter(impl->framebuffer.get());
            painter.setAntialiasing(true);

            // Start with transparent background
            impl->framebuffer->fill(HColor::Transparent());

            // Paint window background and shadow (these always change on resize)
            int iml, imt, imr, imb;
            get_total_margins(impl, iml, imt, imr, imb);
            float marginLeft = static_cast<float>(iml);
            float marginTop = static_cast<float>(imt);
            float marginRight = static_cast<float>(imr);
            float marginBottom = static_cast<float>(imb);

            if (impl->dropShadowEnabled) {
                std::cout << "  [PAINTING] Window drop shadow (size changed)" << std::endl;
                HRectF shadowRect(
                    marginLeft + impl->dropShadowOffsetX,
                    marginTop + impl->dropShadowOffsetY,
                    static_cast<float>(w) - marginLeft - marginRight,
                    static_cast<float>(h) - marginTop - marginBottom
                );

                painter.setBlurRadius(impl->dropShadowBlurRadius);
                painter.setBlurEnabled(true);
                painter.setPen(HPen(HPen::Style::NoPen));
                painter.setBrush(impl->dropShadowColor);
                painter.drawRoundedRect(shadowRect, impl->borderRadius, impl->borderRadius);
                painter.setBlurEnabled(false);
            }

            int sml, smt, smr, smb;
            get_shadow_margins(impl, sml, smt, smr, smb);

            std::cout << "  [PAINTING] Window rounded rect (size changed)" << std::endl;
            HRectF windowRect(
                static_cast<float>(sml),
                static_cast<float>(smt),
                static_cast<float>(w) - static_cast<float>(sml) - static_cast<float>(smr),
                static_cast<float>(h) - static_cast<float>(smt) - static_cast<float>(smb)
            );

            painter.setPen(impl->borderPen);
            painter.setBrush(impl->backgroundColor);
            painter.drawRoundedRect(windowRect, impl->borderRadius, impl->borderRadius);

            // Now handle child items intelligently - copy unchanged, repaint dirty
            std::cout << "  [SMART COPY] Preserving unchanged child items from old buffer:" << std::endl;

            // Helper: recursively copy/repaint items
            std::function<void(HItem*, int, int)> copyOrRepaintItems = [&](HItem* item, int offsetX, int offsetY) {
                if (!item || !item->isVisible()) return;

                const int absX = offsetX + item->x();
                const int absY = offsetY + item->y();
                const int itemW = item->width();
                const int itemH = item->height();

                // Check if this item needs repainting
                if (item->isDirty()) {
                    std::cout << "    → Repainting dirty item at (" << absX << "," << absY
                              << ") size " << itemW << "x" << itemH << std::endl;

                    painter.save();
                    painter.translate(static_cast<float>(absX), static_cast<float>(absY));
                    item->paintContent(painter);
                    painter.restore();
                    item->clearDirty();
                } else if (impl->oldFramebuffer &&
                           absX >= 0 && absY >= 0 &&
                           absX + itemW <= impl->oldFramebuffer->width() &&
                           absY + itemH <= impl->oldFramebuffer->height()) {

                    std::cout << "    → Copying clean item from old buffer at (" << absX << "," << absY
                              << ") size " << itemW << "x" << itemH << std::endl;

                    // Copy pixels from old framebuffer
                    const uint8_t* oldBits = static_cast<const uint8_t*>(impl->oldFramebuffer->constBits());
                    uint8_t* newBits = static_cast<uint8_t*>(impl->framebuffer->bits());
                    const int oldStride = impl->oldFramebuffer->bytesPerLine();
                    const int newStride = impl->framebuffer->bytesPerLine();
                    const int bytesPerPixel = 4; // ARGB32

                    for (int y = 0; y < itemH; ++y) {
                        const int srcY = absY + y;
                        const int dstY = absY + y;

                        if (srcY < 0 || srcY >= impl->oldFramebuffer->height() ||
                            dstY < 0 || dstY >= h) continue;

                        const uint8_t* srcRow = oldBits + srcY * oldStride + absX * bytesPerPixel;
                        uint8_t* dstRow = newBits + dstY * newStride + absX * bytesPerPixel;

                        std::memcpy(dstRow, srcRow, itemW * bytesPerPixel);
                    }
                } else {
                    std::cout << "    → Repainting item (out of old bounds) at (" << absX << "," << absY
                              << ") size " << itemW << "x" << itemH << std::endl;

                    painter.save();
                    painter.translate(static_cast<float>(absX), static_cast<float>(absY));
                    item->paintContent(painter);
                    painter.restore();
                }

                // Process children
                for (HItem* child : item->childItems()) {
                    copyOrRepaintItems(child, absX, absY);
                }
            };

            if (impl->centralItem) {
                copyOrRepaintItems(impl->centralItem, 0, 0);
            }
        }

        // Release old framebuffer
        impl->oldFramebuffer.reset();

        // Full window damage for now (could optimize to only new areas)
        damageRegions.push_back(HRect(0, 0, w, h));
        impl->prevWidth = w;
        impl->prevHeight = h;

        if (impl->renderManager) {
            impl->renderManager->clearDirtyRegions();
        }
        std::cout << "========================================" << std::endl;
    } else if (doFullRepaint || sizeChanged) {
        std::cout << "========================================" << std::endl;
        std::cout << "render_frame: FULL REPAINT" << std::endl;
        std::cout << "========================================" << std::endl;

        // Allocate or reallocate framebuffer
        impl->framebuffer = std::make_unique<HImage>(w, h, HImage::Format::ARGB32_Premul);
        impl->prevWidth = w;
        impl->prevHeight = h;

        {
            HPainter painter(impl->framebuffer.get());
            painter.setAntialiasing(true);

            // Start with transparent background
            impl->framebuffer->fill(HColor::Transparent());

            // If custom paint callback is set, use it instead of default rendering
            if (impl->paintCallback) {
                std::cout << "  [PAINTING] Custom paint callback" << std::endl;
                impl->paintCallback(painter, w, h);
            } else {
                // Default rendering: draw styled window with optional drop shadow
                int iml, imt, imr, imb;
                get_total_margins(impl, iml, imt, imr, imb);
                float marginLeft = static_cast<float>(iml);
                float marginTop = static_cast<float>(imt);
                float marginRight = static_cast<float>(imr);
                float marginBottom = static_cast<float>(imb);

                if (impl->dropShadowEnabled) {
                    std::cout << "  [PAINTING] Window drop shadow at ("
                              << (marginLeft + impl->dropShadowOffsetX) << ","
                              << (marginTop + impl->dropShadowOffsetY) << ")" << std::endl;

                    HRectF shadowRect(
                        marginLeft + impl->dropShadowOffsetX,
                        marginTop + impl->dropShadowOffsetY,
                        static_cast<float>(w) - marginLeft - marginRight,
                        static_cast<float>(h) - marginTop - marginBottom
                    );

                    painter.setBlurRadius(impl->dropShadowBlurRadius);
                    painter.setBlurEnabled(true);
                    painter.setPen(HPen(HPen::Style::NoPen));
                    painter.setBrush(impl->dropShadowColor);
                    painter.drawRoundedRect(shadowRect, impl->borderRadius, impl->borderRadius);
                    painter.setBlurEnabled(false);
                } else {
                    std::cout << "  [SKIPPED] Window drop shadow (disabled)" << std::endl;
                }

                int sml, smt, smr, smb;
                get_shadow_margins(impl, sml, smt, smr, smb);

                std::cout << "  [PAINTING] Window rounded rect at (" << sml << "," << smt << ") "
                          << "size " << (w - sml - smr) << "x" << (h - smt - smb)
                          << " radius=" << impl->borderRadius << std::endl;

                HRectF windowRect(
                    static_cast<float>(sml),
                    static_cast<float>(smt),
                    static_cast<float>(w) - static_cast<float>(sml) - static_cast<float>(smr),
                    static_cast<float>(h) - static_cast<float>(smt) - static_cast<float>(smb)
                );

                painter.setPen(impl->borderPen);
                painter.setBrush(impl->backgroundColor);
                painter.drawRoundedRect(windowRect, impl->borderRadius, impl->borderRadius);
            }

            std::cout << "  [PAINTING] Child items (via RenderManager)" << std::endl;
            // Paint the scene via RenderManager
            if (impl->renderManager) {
                impl->renderManager->render(painter);
            }
        }

        // Full window damage
        damageRegions.push_back(HRect(0, 0, w, h));
        impl->needsFullRepaint = false;

        if (impl->renderManager) {
            impl->renderManager->clearDirtyRegions();
        }
        std::cout << "========================================" << std::endl;
    } else if (impl->renderManager && impl->renderManager->hasDirtyRegions()) {
        std::cout << "========================================" << std::endl;
        std::cout << "render_frame: PARTIAL UPDATE" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "  [SKIPPED] Window drop shadow (not dirty)" << std::endl;
        std::cout << "  [SKIPPED] Window rounded rect (not dirty)" << std::endl;

        // Get dirty regions from render manager
        const auto& dirtyRects = impl->renderManager->dirtyRegions();
        damageRegions = dirtyRects;

        {
            HPainter painter(impl->framebuffer.get());
            painter.setAntialiasing(true);

            std::cout << "  [PAINTING] Only dirty child items:" << std::endl;
            // Only repaint dirty regions
            // Note: For simplicity, we still render the full scene but could optimize further
            if (impl->renderManager) {
                impl->renderManager->render(painter);
            }
        }

        impl->renderManager->clearDirtyRegions();
        std::cout << "========================================" << std::endl;
    } else {
        std::cout << "========================================" << std::endl;
        std::cout << "render_frame: NO CHANGES, SKIPPING" << std::endl;
        std::cout << "  [SKIPPED] Window drop shadow" << std::endl;
        std::cout << "  [SKIPPED] Window rounded rect" << std::endl;
        std::cout << "  [SKIPPED] All child items" << std::endl;
        std::cout << "========================================" << std::endl;
        return; // Nothing to update
    }

    // Copy framebuffer to Wayland shared memory
    HShmBuffer buffer(impl->app, w, h);

    const uint8_t* src = static_cast<const uint8_t*>(impl->framebuffer->constBits());
    const int srcStride = impl->framebuffer->bytesPerLine();
    uint8_t* dst = static_cast<uint8_t*>(buffer.data());
    const int dstStride = buffer.stride();

    const int rowBytesToCopy = std::min(srcStride, dstStride);
    for (int y = 0; y < h; ++y) {
        std::memcpy(dst + static_cast<size_t>(y) * static_cast<size_t>(dstStride),
                    src + static_cast<size_t>(y) * static_cast<size_t>(srcStride),
                    static_cast<size_t>(rowBytesToCopy));
    }

    wl_buffer* wlBuf = static_cast<wl_buffer*>(buffer.wlBuffer());
    wl_surface_attach(impl->surface, wlBuf, 0, 0);

    // Report only dirty regions to Wayland compositor
    std::cout << "  [WAYLAND] Reporting " << damageRegions.size() << " damage region(s):" << std::endl;
    for (const HRect& rect : damageRegions) {
        std::cout << "    → Damage: (" << rect.x() << "," << rect.y()
                  << ") " << rect.width() << "x" << rect.height() << std::endl;
        wl_surface_damage_buffer(impl->surface, rect.x(), rect.y(), rect.width(), rect.height());
    }

    wl_surface_commit(impl->surface);
    wl_display_flush(impl->app->impl()->display);
}

static void xdg_toplevel_handle_configure(
    void* data,
    xdg_toplevel* /*toplevel*/,
    int32_t width,
    int32_t height,
    wl_array* /*states*/) {
    auto* impl = static_cast<HWindow::Impl*>(data);
    if (!impl) {
        return;
    }

    if (width > 0) {
        impl->width = width;
    }
    if (height > 0) {
        impl->height = height;
    }

    impl->configured = true;

    // Repaint on resize if the window is visible.
    if (impl->visible) {
        render_frame(impl);
    }
}

static void xdg_toplevel_handle_close(void* data, xdg_toplevel* /*toplevel*/) {
    auto* impl = static_cast<HWindow::Impl*>(data);
    if (!impl || !impl->app) {
        return;
    }

    impl->visible = false;
    impl->app->exit(0);
}

static const xdg_toplevel_listener xdg_toplevel_listener = {
    .configure = xdg_toplevel_handle_configure,
    .close = xdg_toplevel_handle_close,
};

static void xdg_wm_base_ping(void* data, xdg_wm_base* shell, uint32_t serial) {
    (void)data;
    if (shell) {
        xdg_wm_base_pong(shell, serial);
    }
}

static const xdg_wm_base_listener xdg_wm_base_listener = {
    .ping = xdg_wm_base_ping,
};

} // namespace

HWindow::HWindow(HApplication* app)
    : m_impl(std::make_unique<Impl>()) {
    m_impl->window = this;
    m_impl->app = app;

    // Initialize internal components
    m_impl->sceneGraph = std::make_unique<HSceneGraph>();
    m_impl->renderManager = std::make_unique<HRenderManager>();
    m_impl->eventDispatcher = std::make_unique<HEventDispatcher>();

    // Wire them up
    m_impl->renderManager->setSceneGraph(m_impl->sceneGraph.get());
    m_impl->eventDispatcher->setSceneGraph(m_impl->sceneGraph.get());
    m_impl->eventDispatcher->setWindow(this);
    if (!app || !app->impl() || !app->impl()->compositor) {
        throw std::runtime_error("HWindow requires a connected HApplication with wl_compositor");
    }

    // Ensure xdg_wm_base is available and has a listener for ping/pong.
    if (!app->impl()->xdgWmBase) {
        throw std::runtime_error("HWindow requires xdg_wm_base (XDG shell) from compositor");
    }
    xdg_wm_base_add_listener(app->impl()->xdgWmBase, &xdg_wm_base_listener, app->impl());

    // Create a basic wl_surface and attach XDG roles.
    m_impl->surface = wl_compositor_create_surface(app->impl()->compositor);
    if (!m_impl->surface) {
        throw std::runtime_error("Failed to create wl_surface for HWindow");
    }
    wl_surface_set_user_data(m_impl->surface, m_impl.get());

    m_impl->xdgSurface = xdg_wm_base_get_xdg_surface(app->impl()->xdgWmBase, m_impl->surface);
    if (!m_impl->xdgSurface) {
        throw std::runtime_error("Failed to create xdg_surface for HWindow");
    }

    xdg_surface_add_listener(m_impl->xdgSurface, &xdg_surface_listener, m_impl.get());

    m_impl->xdgToplevel = xdg_surface_get_toplevel(m_impl->xdgSurface);
    if (!m_impl->xdgToplevel) {
        throw std::runtime_error("Failed to create xdg_toplevel for HWindow");
    }

    xdg_toplevel_add_listener(m_impl->xdgToplevel, &xdg_toplevel_listener, m_impl.get());

    // Register as primary window for simple drag support.
    if (app && app->impl()) {
        app->impl()->primaryWindow = this;
    }
}

HWindow::~HWindow() {
    if (m_impl && m_impl->app && m_impl->app->impl() &&
        m_impl->app->impl()->primaryWindow == this) {
        m_impl->app->impl()->primaryWindow = nullptr;
    }
    if (m_impl && m_impl->xdgToplevel) {
        xdg_toplevel_destroy(m_impl->xdgToplevel);
        m_impl->xdgToplevel = nullptr;
    }
    if (m_impl && m_impl->xdgSurface) {
        xdg_surface_destroy(m_impl->xdgSurface);
        m_impl->xdgSurface = nullptr;
    }
    if (m_impl && m_impl->surface && m_impl->app && m_impl->app->impl()->display) {
        wl_surface_destroy(m_impl->surface);
        m_impl->surface = nullptr;
    }
}

HWindow::HWindow(HWindow&&) noexcept = default;
HWindow& HWindow::operator=(HWindow&&) noexcept = default;

void HWindow::setTitle(const std::string& title) {
    m_impl->windowTitle = title;
    if (m_impl->xdgToplevel) {
        xdg_toplevel_set_title(m_impl->xdgToplevel, m_impl->windowTitle.c_str());
    }
}

const std::string& HWindow::title() const {
    return m_impl->windowTitle;
}

int HWindow::width() const {
    return m_impl->width;
}

int HWindow::height() const {
    return m_impl->height;
}

void HWindow::resize(int width, int height) {
    if (width <= 0 || height <= 0) {
        return;
    }

    m_impl->width = width;
    m_impl->height = height;
    m_impl->needsFullRepaint = true;

    if (m_impl->visible) {
        render_frame(m_impl.get());
    }
}

void HWindow::show() {
    m_impl->visible = true;

    // Ensure layout is calculated before first render
    if (m_impl->centralItem) {
        m_impl->centralItem->updateLayout();
    }

    render_frame(m_impl.get());
}

void HWindow::hide() {
    m_impl->visible = false;
    // Future: detach buffers / mark as hidden.
}

void HWindow::update() {
    if (m_impl->visible) {
        render_frame(m_impl.get());
    }
}

// Visual customization methods

void HWindow::setBorderRadius(float radius) {
    m_impl->borderRadius = radius;
    m_impl->needsFullRepaint = true;
    if (m_impl->visible) {
        render_frame(m_impl.get());
    }
}

float HWindow::borderRadius() const {
    return m_impl->borderRadius;
}

void HWindow::setBorderPen(const HPen& pen) {
    m_impl->borderPen = pen;
    m_impl->needsFullRepaint = true;
    if (m_impl->visible) {
        render_frame(m_impl.get());
    }
}

const HPen& HWindow::borderPen() const {
    return m_impl->borderPen;
}

void HWindow::setBackgroundColor(const HColor& color) {
    m_impl->backgroundColor = color;
    m_impl->needsFullRepaint = true;
    if (m_impl->visible) {
        render_frame(m_impl.get());
    }
}

const HColor& HWindow::backgroundColor() const {
    return m_impl->backgroundColor;
}

// Drop shadow methods

void HWindow::setDropShadowEnabled(bool enabled) {
    m_impl->dropShadowEnabled = enabled;
    m_impl->needsFullRepaint = true;
    if (m_impl->visible) {
        render_frame(m_impl.get());
    }
}

bool HWindow::dropShadowEnabled() const {
    return m_impl->dropShadowEnabled;
}

void HWindow::setDropShadowOffset(float x, float y) {
    m_impl->dropShadowOffsetX = x;
    m_impl->dropShadowOffsetY = y;
    m_impl->needsFullRepaint = true;
    if (m_impl->visible) {
        render_frame(m_impl.get());
    }
}

float HWindow::dropShadowOffsetX() const {
    return m_impl->dropShadowOffsetX;
}

float HWindow::dropShadowOffsetY() const {
    return m_impl->dropShadowOffsetY;
}

void HWindow::setDropShadowBlurRadius(float radius) {
    m_impl->dropShadowBlurRadius = radius;
    m_impl->needsFullRepaint = true;
    if (m_impl->visible) {
        render_frame(m_impl.get());
    }
}

float HWindow::dropShadowBlurRadius() const {
    return m_impl->dropShadowBlurRadius;
}

void HWindow::setDropShadowColor(const HColor& color) {
    m_impl->dropShadowColor = color;
    m_impl->needsFullRepaint = true;
    if (m_impl->visible) {
        render_frame(m_impl.get());
    }
}

const HColor& HWindow::dropShadowColor() const {
    return m_impl->dropShadowColor;
}

// Custom paint callback

void HWindow::setPaintCallback(PaintCallback callback) {
    m_impl->paintCallback = std::move(callback);
    m_impl->needsFullRepaint = true;
    if (m_impl->visible) {
        render_frame(m_impl.get());
    }
}

void HWindow::clearPaintCallback() {
    m_impl->paintCallback = nullptr;
    m_impl->needsFullRepaint = true;
    if (m_impl->visible) {
        render_frame(m_impl.get());
    }
}

// Draggable regions

void HWindow::setDraggableRegion(const HRect& region) {
    m_impl->draggableRegions.clear();
    m_impl->draggableRegions.push_back(region);
}

void HWindow::addDraggableRegion(const HRect& region) {
    m_impl->draggableRegions.push_back(region);
}

void HWindow::clearDraggableRegions() {
    m_impl->draggableRegions.clear();
}

// Content item

void HWindow::setContent(HItem* item) {
    m_impl->centralItem = item;
    if (m_impl->sceneGraph) {
        m_impl->sceneGraph->setRootItem(item);
    }

    // Set window reference on all items for dirty propagation
    if (item) {
        item->setWindow(this);
    }

    if (m_impl->visible) {
        render_frame(m_impl.get());
    }
}

// Helper function for dirty notification (called by HItem::update())
void notifyItemDirty(HWindow* window, const HRect& dirtyRect) {
    if (!window || !window->impl()) {
        return;
    }

    auto* impl = window->impl();

    // Mark the region as dirty in render manager
    if (impl->renderManager) {
        impl->renderManager->markDirty(dirtyRect);
    }

    // Schedule a repaint if window is visible
    if (impl->visible) {
        window->update();
    }
}

HItem* HWindow::content() const {
    return m_impl->centralItem;
}

// Mouse event routing helper (static) - internal with offset
static HMouseArea* findMouseAreaAtOffset(HItem* item, int x, int y, int offsetX, int offsetY) {
    if (!item || !item->isVisible()) {
        return nullptr;
    }

    // Calculate absolute item bounds
    const int absX = offsetX + item->x();
    const int absY = offsetY + item->y();
    const HRect itemBounds(absX, absY, item->width(), item->height());

    // Check if point is even within this item's bounds first
    if (!itemBounds.contains(HPoint(x, y))) {
        return nullptr;
    }

    // Check children first (they're on top) - pass accumulated offset
    for (HItem* child : item->childItems()) {
        HMouseArea* found = findMouseAreaAtOffset(child, x, y, absX, absY);
        if (found) {
            return found;
        }
    }

    // Check if this item is a HMouseArea
    HMouseArea* mouseArea = dynamic_cast<HMouseArea*>(item);
    if (mouseArea && mouseArea->enabled()) {
        return mouseArea;
    }

    return nullptr;
}

// Mouse event routing helper (static) - public entry point
HMouseArea* HWindow::findMouseAreaAt(HItem* item, int x, int y) {
    return findMouseAreaAtOffset(item, x, y, 0, 0);
}

// Helper to find any HItem at position (for focus management)
static HItem* findItemAtOffset(HItem* item, int x, int y, int offsetX, int offsetY) {
    if (!item || !item->isVisible()) {
        return nullptr;
    }

    // Calculate absolute item bounds
    const int absX = offsetX + item->x();
    const int absY = offsetY + item->y();
    const HRect itemBounds(absX, absY, item->width(), item->height());

    // Check if point is even within this item's bounds first
    if (!itemBounds.contains(HPoint(x, y))) {
        return nullptr;
    }

    // Check children first (they're on top) - pass accumulated offset
    for (HItem* child : item->childItems()) {
        HItem* found = findItemAtOffset(child, x, y, absX, absY);
        if (found) {
            return found;
        }
    }

    // Return this item if it contains the point
    return item;
}

HItem* HWindow::findItemAt(HItem* item, int x, int y) {
    return findItemAtOffset(item, x, y, 0, 0);
}

void HWindow::setPadding(int left, int top, int right, int bottom) {
    m_impl->paddingLeft = left;
    m_impl->paddingTop = top;
    m_impl->paddingRight = right;
    m_impl->paddingBottom = bottom;
    // Layout update removed
    update();
}

void HWindow::setPadding(int padding) {
    setPadding(padding, padding, padding, padding);
}

void HWindow::getPadding(int* left, int* top, int* right, int* bottom) const {
    if (left) *left = m_impl->paddingLeft;
    if (top) *top = m_impl->paddingTop;
    if (right) *right = m_impl->paddingRight;
    if (bottom) *bottom = m_impl->paddingBottom;
}

void HWindow::setFocusItem(HItem* item) {
    if (m_impl->eventDispatcher) {
        m_impl->eventDispatcher->setFocusItem(item);
    }
}

HItem* HWindow::focusItem() const {
    if (m_impl->eventDispatcher) {
        return m_impl->eventDispatcher->focusItem();
    }
    return nullptr;
}

void HWindow::dispatchKeyEvent(HKeyEvent& event) {
    if (m_impl->eventDispatcher) {
        m_impl->eventDispatcher->dispatchKeyEvent(event);
    }
}

} // namespace Ht