#include "HPainterPath.h"

#include "include/core/SkPath.h"
#include "include/core/SkPathBuilder.h"
#include "include/pathops/SkPathOps.h"

namespace Ht {

struct HPainterPath::Impl {
    SkPathBuilder builder;
    SkPath path;
    bool hasPoints = false;
    bool pathValid = false;

    const SkPath& ensurePath() {
        if (!pathValid) {
            path = builder.snapshot();
            pathValid = true;
        }
        return path;
    }
};

HPainterPath::HPainterPath()
    : m_impl(std::make_unique<Impl>()) {
}

HPainterPath::~HPainterPath() = default;

HPainterPath::HPainterPath(const HPainterPath& other)
    : m_impl(std::make_unique<Impl>(*other.m_impl)) {
}

HPainterPath& HPainterPath::operator=(const HPainterPath& other) {
    if (this != &other) {
        m_impl = std::make_unique<Impl>(*other.m_impl);
    }
    return *this;
}

HPainterPath::HPainterPath(HPainterPath&& other) noexcept = default;
HPainterPath& HPainterPath::operator=(HPainterPath&& other) noexcept = default;

bool HPainterPath::isEmpty() const {
    if (!m_impl) {
        return true;
    }
    return !m_impl->hasPoints;
}

void HPainterPath::clear() {
    if (m_impl) {
        m_impl->builder.reset();
        m_impl->path.reset();
        m_impl->hasPoints = false;
        m_impl->pathValid = false;
    }
}

void HPainterPath::moveTo(float x, float y) {
    m_impl->builder.moveTo(x, y);
    m_impl->hasPoints = true;
    m_impl->pathValid = false;
}

void HPainterPath::moveTo(const HPointF& point) {
    moveTo(point.x(), point.y());
}

void HPainterPath::lineTo(float x, float y) {
    m_impl->builder.lineTo(x, y);
    m_impl->hasPoints = true;
    m_impl->pathValid = false;
}

void HPainterPath::lineTo(const HPointF& point) {
    lineTo(point.x(), point.y());
}

void HPainterPath::quadTo(float cx, float cy, float x, float y) {
    m_impl->builder.quadTo(cx, cy, x, y);
    m_impl->hasPoints = true;
    m_impl->pathValid = false;
}

void HPainterPath::quadTo(const HPointF& control, const HPointF& endPoint) {
    quadTo(control.x(), control.y(), endPoint.x(), endPoint.y());
}

void HPainterPath::cubicTo(float cx1, float cy1, float cx2, float cy2, float x, float y) {
    m_impl->builder.cubicTo(cx1, cy1, cx2, cy2, x, y);
    m_impl->hasPoints = true;
    m_impl->pathValid = false;
}

void HPainterPath::cubicTo(const HPointF& control1, const HPointF& control2, const HPointF& endPoint) {
    cubicTo(control1.x(), control1.y(), control2.x(), control2.y(), endPoint.x(), endPoint.y());
}

void HPainterPath::closeSubpath() {
    m_impl->builder.close();
    m_impl->pathValid = false;
}

void HPainterPath::addRect(const HRectF& rect) {
    SkRect r = SkRect::MakeXYWH(rect.x(), rect.y(), rect.width(), rect.height());
    m_impl->builder.addRect(r);
    m_impl->hasPoints = true;
    m_impl->pathValid = false;
}

void HPainterPath::addEllipse(const HRectF& rect) {
    SkRect r = SkRect::MakeXYWH(rect.x(), rect.y(), rect.width(), rect.height());
    m_impl->builder.addOval(r);
    m_impl->hasPoints = true;
    m_impl->pathValid = false;
}

HRectF HPainterPath::boundingRect() const {
    if (!m_impl || !m_impl->hasPoints) {
        return HRectF();
    }

    auto boundsOpt = m_impl->builder.computeFiniteBounds();
    if (!boundsOpt.has_value()) {
        return HRectF();
    }

    SkRect bounds = *boundsOpt;
    return HRectF(bounds.x(), bounds.y(), bounds.width(), bounds.height());
}

static HPainterPath applyPathOp(const HPainterPath& a, const HPainterPath& b, SkPathOp op) {
    HPainterPath result;
    if (!a.impl() || !b.impl()) {
        return result;
    }

    const SkPath& aPath = a.impl()->ensurePath();
    const SkPath& bPath = b.impl()->ensurePath();

    SkPath dst;
    if (Op(aPath, bPath, op, &dst)) {
        result.impl()->builder = SkPathBuilder(dst);
        result.impl()->path = dst;
        result.impl()->hasPoints = true;
        result.impl()->pathValid = true;
    }
    return result;
}

HPainterPath HPainterPath::united(const HPainterPath& other) const {
    return applyPathOp(*this, other, kUnion_SkPathOp);
}

HPainterPath HPainterPath::intersected(const HPainterPath& other) const {
    return applyPathOp(*this, other, kIntersect_SkPathOp);
}

HPainterPath HPainterPath::subtracted(const HPainterPath& other) const {
    return applyPathOp(*this, other, kDifference_SkPathOp);
}

HPainterPath HPainterPath::xored(const HPainterPath& other) const {
    return applyPathOp(*this, other, kXOR_SkPathOp);
}

const void* HPainterPath::rawPathHandle() const {
    if (!m_impl) {
        return nullptr;
    }
    const SkPath& path = m_impl->ensurePath();
    return static_cast<const void*>(&path);
}

} // namespace Ht
