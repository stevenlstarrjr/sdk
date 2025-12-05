#pragma once

namespace Ht {

class HPainter;
class HImage;
class HSize;

/**
 * @brief Abstract paint device for HPainter backends.
 * Qt Equivalent: QPaintDevice
 *
 * This is the base for future GPU backends (e.g., Vulkan/OpenGL).
 */
class HPaintDevice {
public:
    virtual ~HPaintDevice() = default;

    virtual HSize size() const = 0;

    // Optionally expose a raster image; non-raster devices may return nullptr.
    virtual HImage* asImage() { return nullptr; }
    virtual const HImage* asImage() const { return nullptr; }

    // Optionally expose a backend GPU surface handle (e.g., SkSurface*).
    // The concrete type is intentionally hidden from the public API; HPainter
    // and backend code may reinterpret this pointer as needed.
    virtual const void* rawSurfaceHandle() const { return nullptr; }

protected:
    HPaintDevice() = default;
};

} // namespace Ht
