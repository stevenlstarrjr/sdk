#pragma once

#include <memory>

namespace Ht {

class HApplication;

/**
 * @brief HShmBuffer wraps a wl_shm buffer for client-side rendering.
 * Wayland Equivalent: wl_shm_pool + wl_buffer
 */
class HShmBuffer {
public:
    HShmBuffer(HApplication* app, int width, int height);
    ~HShmBuffer();

    HShmBuffer(const HShmBuffer&) = delete;
    HShmBuffer& operator=(const HShmBuffer&) = delete;
    HShmBuffer(HShmBuffer&&) noexcept;
    HShmBuffer& operator=(HShmBuffer&&) noexcept;

    int width() const;
    int height() const;
    int stride() const;

    void* data();
    const void* data() const;

    // Underlying wl_buffer handle (for wl_surface_attach)
    void* wlBuffer() const;

    struct Impl;
    Impl* impl() const { return m_impl.get(); }

private:
    std::unique_ptr<Impl> m_impl;
};

} // namespace Ht

