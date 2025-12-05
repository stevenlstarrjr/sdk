#pragma once

#include <vector>

#include "HPoint.h"
#include "HPointF.h"

namespace Ht {

/**
 * @brief HPolygon represents a polygon as a list of integer points.
 * Qt Equivalent: QPolygon
 *
 * This is a thin alias over std::vector<HPoint> to keep value semantics
 * while matching Qt-style naming.
 */
using HPolygon = std::vector<HPoint>;

/**
 * @brief HPolygonF represents a polygon as a list of floating-point points.
 * Qt Equivalent: QPolygonF
 */
using HPolygonF = std::vector<HPointF>;

} // namespace Ht

