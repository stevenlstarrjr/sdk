#pragma once

#include "HPaintDevice.h"
#include "HSize.h"
#include <memory>

namespace Ht {

/**
 * @brief GPU paint device for Vulkan-backed Skia surfaces.
 * Skia Backend: GrDirectContext + SkSurface (Vulkan)
 *
 * This is a thin wrapper around an existing Skia SkSurface that is
 * created and managed by higher-level Vulkan/windowing code.
 */
class HVulkanPaintDevice : public HPaintDevice {
public:
    // Construct from an existing SkSurface pointer (passed as opaque handle)
    // and its logical size. The surface lifetime is managed by the creator.
    HVulkanPaintDevice(const void* surfaceHandle, const HSize& size);
    ~HVulkanPaintDevice() override;

    HSize size() const override;

    const void* rawSurfaceHandle() const override;

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};

} // namespace Ht
