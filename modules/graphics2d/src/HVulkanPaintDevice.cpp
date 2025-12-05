#include "HVulkanPaintDevice.h"

#include "HSize.h"
#include "include/core/SkSurface.h"
#include "include/core/SkRefCnt.h"

namespace Ht {

struct HVulkanPaintDevice::Impl {
    sk_sp<SkSurface> surface;
    HSize logicalSize;
};

HVulkanPaintDevice::HVulkanPaintDevice(const void* surfaceHandle, const HSize& size)
    : m_impl(std::make_unique<Impl>()) {
    SkSurface* surf = static_cast<SkSurface*>(const_cast<void*>(surfaceHandle));
    if (surf) {
        m_impl->surface = sk_ref_sp(surf);
    }
    m_impl->logicalSize = size;
}

HVulkanPaintDevice::~HVulkanPaintDevice() = default;

HSize HVulkanPaintDevice::size() const {
    return m_impl ? m_impl->logicalSize : HSize();
}

const void* HVulkanPaintDevice::rawSurfaceHandle() const {
    return m_impl && m_impl->surface ? static_cast<const void*>(m_impl->surface.get()) : nullptr;
}

} // namespace Ht

