#pragma once

#include <memory>

namespace Ht {

/**
 * @brief HWaylandOutput represents a displayable area managed by the compositor.
 * Qt Equivalent: QWaylandOutput
 * wlroots Backend: wlr_output
 */
class HWaylandOutput {
public:
    HWaylandOutput();
    ~HWaylandOutput();

    // Non-copyable, movable
    HWaylandOutput(const HWaylandOutput&) = delete;
    HWaylandOutput& operator=(const HWaylandOutput&) = delete;
    HWaylandOutput(HWaylandOutput&&) noexcept;
    HWaylandOutput& operator=(HWaylandOutput&&) noexcept;

    // Basic output information (may be zero/null if no backend output is attached)
    const char* name() const;
    int width() const;
    int height() const;
    int refreshRateMilliHz() const;
    int physWidthMm() const;
    int physHeightMm() const;

    bool isEnabled() const;

    // Internal wlroots access for compositor internals
    struct Impl;
    Impl* impl() const { return m_impl.get(); }

private:
    std::unique_ptr<Impl> m_impl;
};

} // namespace Ht

