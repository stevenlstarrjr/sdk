#include "HWaylandOutput.h"
#include "private/HWaylandOutput_p.h"

namespace Ht {

HWaylandOutput::HWaylandOutput()
    : m_impl(std::make_unique<Impl>()) {
}

HWaylandOutput::~HWaylandOutput() = default;

HWaylandOutput::HWaylandOutput(HWaylandOutput&&) noexcept = default;
HWaylandOutput& HWaylandOutput::operator=(HWaylandOutput&&) noexcept = default;

const char* HWaylandOutput::name() const {
    return (m_impl && m_impl->output && m_impl->output->name)
        ? m_impl->output->name
        : nullptr;
}

int HWaylandOutput::width() const {
    return (m_impl && m_impl->output) ? m_impl->output->width : 0;
}

int HWaylandOutput::height() const {
    return (m_impl && m_impl->output) ? m_impl->output->height : 0;
}

int HWaylandOutput::refreshRateMilliHz() const {
    return (m_impl && m_impl->output) ? m_impl->output->refresh : 0;
}

int HWaylandOutput::physWidthMm() const {
    return (m_impl && m_impl->output) ? m_impl->output->phys_width : 0;
}

int HWaylandOutput::physHeightMm() const {
    return (m_impl && m_impl->output) ? m_impl->output->phys_height : 0;
}

bool HWaylandOutput::isEnabled() const {
    return m_impl && m_impl->output && m_impl->output->enabled;
}

} // namespace Ht

