#include "HRegion.h"

#include "include/core/SkRegion.h"

namespace Ht {

struct HRegion::Impl {
    SkRegion region;
};

HRegion::HRegion()
    : m_impl(std::make_unique<Impl>()) {
}

HRegion::HRegion(const HRect& rect)
    : m_impl(std::make_unique<Impl>()) {
    SkIRect r = SkIRect::MakeLTRB(rect.left(), rect.top(), rect.right() + 1, rect.bottom() + 1);
    m_impl->region.setRect(r);
}

HRegion::HRegion(const HRegion& other)
    : m_impl(std::make_unique<Impl>(*other.m_impl)) {
}

HRegion::HRegion(HRegion&& other) noexcept = default;

HRegion::~HRegion() = default;

HRegion& HRegion::operator=(const HRegion& other) {
    if (this != &other) {
        m_impl = std::make_unique<Impl>(*other.m_impl);
    }
    return *this;
}

HRegion& HRegion::operator=(HRegion&& other) noexcept = default;

bool HRegion::isEmpty() const {
    return !m_impl || m_impl->region.isEmpty();
}

bool HRegion::isRect() const {
    return m_impl && m_impl->region.isRect();
}

HRect HRegion::boundingRect() const {
    if (!m_impl || m_impl->region.isEmpty()) {
        return HRect();
    }
    SkIRect r = m_impl->region.getBounds();
    return HRect(r.left(), r.top(), r.width(), r.height());
}

bool HRegion::contains(const HPoint& point) const {
    return m_impl && m_impl->region.contains(point.x(), point.y());
}

bool HRegion::contains(const HRect& rect) const {
    if (!m_impl || rect.isEmpty()) {
        return false;
    }
    SkIRect r = SkIRect::MakeLTRB(rect.left(), rect.top(), rect.right() + 1, rect.bottom() + 1);
    return m_impl->region.contains(r);
}

static SkRegion::Op toSkOp(HRegion::RegionOp op) {
    switch (op) {
        case HRegion::RegionOp::Replace:    return SkRegion::kReplace_Op;
        case HRegion::RegionOp::Intersect:  return SkRegion::kIntersect_Op;
        case HRegion::RegionOp::Union:      return SkRegion::kUnion_Op;
        case HRegion::RegionOp::Xor:        return SkRegion::kXOR_Op;
        case HRegion::RegionOp::Difference: return SkRegion::kDifference_Op;
    }
    return SkRegion::kReplace_Op;
}

static HRegion applyRegionOp(const HRegion& a, const HRegion& b, SkRegion::Op op) {
    HRegion result;
    if (!a.impl() || !b.impl()) {
        return result;
    }
    result.impl()->region.op(a.impl()->region, b.impl()->region, op);
    return result;
}

HRegion HRegion::united(const HRegion& other) const {
    return applyRegionOp(*this, other, SkRegion::kUnion_Op);
}

HRegion HRegion::intersected(const HRegion& other) const {
    return applyRegionOp(*this, other, SkRegion::kIntersect_Op);
}

HRegion HRegion::subtracted(const HRegion& other) const {
    return applyRegionOp(*this, other, SkRegion::kDifference_Op);
}

HRegion HRegion::xored(const HRegion& other) const {
    return applyRegionOp(*this, other, SkRegion::kXOR_Op);
}

HRegion& HRegion::unite(const HRegion& other) {
    if (m_impl && other.impl()) {
        m_impl->region.op(other.impl()->region, SkRegion::kUnion_Op);
    }
    return *this;
}

HRegion& HRegion::intersect(const HRegion& other) {
    if (m_impl && other.impl()) {
        m_impl->region.op(other.impl()->region, SkRegion::kIntersect_Op);
    }
    return *this;
}

HRegion& HRegion::subtract(const HRegion& other) {
    if (m_impl && other.impl()) {
        m_impl->region.op(other.impl()->region, SkRegion::kDifference_Op);
    }
    return *this;
}

HRegion& HRegion::xorWith(const HRegion& other) {
    if (m_impl && other.impl()) {
        m_impl->region.op(other.impl()->region, SkRegion::kXOR_Op);
    }
    return *this;
}

void HRegion::clear() {
    if (m_impl) {
        m_impl->region.setEmpty();
    }
}

const void* HRegion::rawHandle() const {
    if (!m_impl) {
        return nullptr;
    }
    return static_cast<const void*>(&m_impl->region);
}

} // namespace Ht
