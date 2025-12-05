#pragma once

#include <memory>

namespace Ht {

/**
 * @brief HWaylandCompositor manages the Wayland display server.
 * Qt Equivalent: QWaylandCompositor
 * wlroots Backend: wl_display + event loop
 */
class HWaylandCompositor {
public:
    HWaylandCompositor();
    ~HWaylandCompositor();

    // Non-copyable, movable
    HWaylandCompositor(const HWaylandCompositor&) = delete;
    HWaylandCompositor& operator=(const HWaylandCompositor&) = delete;
    HWaylandCompositor(HWaylandCompositor&&) noexcept;
    HWaylandCompositor& operator=(HWaylandCompositor&&) noexcept;

    // Create and bind a socket for clients to connect.
    // Returns socket name (e.g., "wayland-0") on success, nullptr on failure.
    const char* addSocket(const char* name = nullptr);

    // Get the socket name if one was created.
    const char* socketName() const;

    // Run the event loop (blocks until quit).
    void run();

    // Request event loop termination.
    void terminate();

    // Dispatch pending events (non-blocking).
    int dispatchPending();

    // Flush pending events to clients.
    void flush();

    // Get backend serial.
    uint32_t nextSerial() const;

    // Convenience factory for a default seat (Qt: QWaylandSeat created from QWaylandCompositor).
    class HWaylandSeat createDefaultSeat(const char* name = "seat0");

    // Internal wl_display access (for compositor internals)
    struct Impl;
    Impl* impl() const { return m_impl.get(); }

private:
    std::unique_ptr<Impl> m_impl;
};

} // namespace Ht
