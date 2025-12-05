#include "HWaylandCompositor.h"
#include "private/HWaylandCompositor_p.h"
#include "HWaylandSeat.h"

// wlroots / Wayland headers - implementation only
extern "C" {
#include <wayland-server-core.h>
}

namespace Ht {

HWaylandCompositor::Impl::Impl() = default;

HWaylandCompositor::Impl::~Impl() {
    cleanup();
}

bool HWaylandCompositor::Impl::initialize() {
    display = wl_display_create();
    if (!display) {
        return false;
    }

    eventLoop = wl_display_get_event_loop(display);
    return eventLoop != nullptr;
}

void HWaylandCompositor::Impl::cleanup() {
    if (display) {
        wl_display_destroy(display);
        display = nullptr;
    }
    eventLoop = nullptr;
    socketName = nullptr;
}

// HWaylandCompositor implementation
HWaylandCompositor::HWaylandCompositor()
    : m_impl(std::make_unique<Impl>()) {
    if (!m_impl->initialize()) {
        throw std::runtime_error("Failed to create Wayland display");
    }
}

HWaylandCompositor::~HWaylandCompositor() = default;

HWaylandCompositor::HWaylandCompositor(HWaylandCompositor&&) noexcept = default;
HWaylandCompositor& HWaylandCompositor::operator=(HWaylandCompositor&&) noexcept = default;

const char* HWaylandCompositor::addSocket(const char* name) {
    if (!m_impl->display) {
        return nullptr;
    }

    m_impl->socketName = wl_display_add_socket_auto(m_impl->display);
    if (name && m_impl->socketName) {
        if (wl_display_add_socket(m_impl->display, name) == 0) {
            m_impl->socketName = name;
        }
    }

    return m_impl->socketName;
}

const char* HWaylandCompositor::socketName() const {
    return m_impl->socketName;
}

void HWaylandCompositor::run() {
    if (m_impl->display) {
        wl_display_run(m_impl->display);
    }
}

void HWaylandCompositor::terminate() {
    if (m_impl->display) {
        wl_display_terminate(m_impl->display);
    }
}

int HWaylandCompositor::dispatchPending() {
    if (!m_impl->eventLoop) {
        return -1;
    }
    return wl_event_loop_dispatch(m_impl->eventLoop, 0);
}

void HWaylandCompositor::flush() {
    if (m_impl->display) {
        wl_display_flush_clients(m_impl->display);
    }
}

uint32_t HWaylandCompositor::nextSerial() const {
    if (!m_impl->display) {
        return 0;
    }
    return wl_display_next_serial(m_impl->display);
}

HWaylandSeat HWaylandCompositor::createDefaultSeat(const char* name) {
    return HWaylandSeat(this, name);
}

} // namespace Ht
