#include "HPoint.h"
#include "HPointF.h"
#include "HSize.h"
#include "HSizeF.h"
#include "HRect.h"
#include "HRectF.h"

namespace Ht {

HPointF HPoint::toPointF() const noexcept {
    return HPointF(static_cast<float>(m_x), static_cast<float>(m_y));
}

HSizeF HSize::toSizeF() const noexcept {
    return HSizeF(static_cast<float>(m_width), static_cast<float>(m_height));
}

HRectF HRect::toRectF() const noexcept {
    return HRectF(static_cast<float>(m_x), static_cast<float>(m_y),
                  static_cast<float>(m_width), static_cast<float>(m_height));
}

} // namespace Ht
