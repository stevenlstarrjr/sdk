#pragma once

#include "HRect.h"
#include <memory>

namespace Ht {

/**
 * @brief HRegion represents an integer-based region composed of rectangles.
 * Qt Equivalent: QRegion
 * Skia Backend: SkRegion
 */
class HRegion {
public:
    enum class RegionOp {
        Replace,
        Intersect,
        Union,
        Xor,
        Difference
    };

    // Constructors
    HRegion();
    explicit HRegion(const HRect& rect);
    HRegion(const HRegion& other);
    HRegion(HRegion&& other) noexcept;
    ~HRegion();

    HRegion& operator=(const HRegion& other);
    HRegion& operator=(HRegion&& other) noexcept;

    // Basic queries
    bool isEmpty() const;
    bool isRect() const;
    HRect boundingRect() const;

    bool contains(const HPoint& point) const;
    bool contains(const HRect& rect) const;

    // Boolean operations (return new region)
    HRegion united(const HRegion& other) const;
    HRegion intersected(const HRegion& other) const;
    HRegion subtracted(const HRegion& other) const;
    HRegion xored(const HRegion& other) const;

    // In-place ops
    HRegion& unite(const HRegion& other);
    HRegion& intersect(const HRegion& other);
    HRegion& subtract(const HRegion& other);
    HRegion& xorWith(const HRegion& other);

    // Reset
    void clear();

    // Internal Skia access
    struct Impl;
    Impl* impl() const { return m_impl.get(); }
    const void* rawHandle() const;

private:
    std::unique_ptr<Impl> m_impl;
};

} // namespace Ht
