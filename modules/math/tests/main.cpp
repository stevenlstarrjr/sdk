#include <cmath>
#include <cstdlib>
#include <iostream>

#include "HVector2.h"
#include "HMatrix3x3.h"
#include "HTransform2D.h"

using namespace Ht;

namespace {

bool approxEqual(float a, float b, float epsilon = 1e-5f)
{
    return std::fabs(a - b) <= epsilon;
}

bool approxEqualVec(const HVector2& a, const HVector2& b, float epsilon = 1e-5f)
{
    return approxEqual(a.x(), b.x(), epsilon) && approxEqual(a.y(), b.y(), epsilon);
}

void testVectorBasic()
{
    HVector2 a(1.0f, 2.0f);
    HVector2 b(3.0f, 4.0f);

    HVector2 sum = a + b;
    if (!approxEqualVec(sum, HVector2(4.0f, 6.0f))) {
        std::cerr << "Vector add failed\n";
        std::exit(1);
    }

    HVector2 diff = b - a;
    if (!approxEqualVec(diff, HVector2(2.0f, 2.0f))) {
        std::cerr << "Vector sub failed\n";
        std::exit(1);
    }

    HVector2 scaled = a * 2.0f;
    if (!approxEqualVec(scaled, HVector2(2.0f, 4.0f))) {
        std::cerr << "Vector scale failed\n";
        std::exit(1);
    }

    float d = HVector2::dot(a, b);
    if (!approxEqual(d, 11.0f)) {
        std::cerr << "Vector dot failed\n";
        std::exit(1);
    }
}

void testVectorNormalize()
{
    HVector2 v(3.0f, 4.0f);
    v.normalize();
    float len = v.length();
    if (!approxEqual(len, 1.0f)) {
        std::cerr << "Vector normalize failed\n";
        std::exit(1);
    }
}

void testMatrixTransform()
{
    HMatrix3x3 m = HMatrix3x3::identity();
    m.setM(0, 2, 10.0f);
    m.setM(1, 2, 20.0f);

    HVector2 p(1.0f, 2.0f);
    HVector2 tp = m.transformPoint(p);
    if (!approxEqualVec(tp, HVector2(11.0f, 22.0f))) {
        std::cerr << "Matrix transformPoint failed\n";
        std::exit(1);
    }
}

void testTransformComposition()
{
    HTransform2D tTranslate = HTransform2D::translation(10.0f, 0.0f);
    HTransform2D tScale = HTransform2D::scale(2.0f, 2.0f);

    HTransform2D combined = tTranslate * tScale;

    HVector2 p(1.0f, 1.0f);
    HVector2 result = combined.mapPoint(p);

    if (!approxEqualVec(result, HVector2(12.0f, 2.0f))) {
        std::cerr << "Transform composition failed\n";
        std::exit(1);
    }
}

} // namespace

int main()
{
    testVectorBasic();
    testVectorNormalize();
    testMatrixTransform();
    testTransformComposition();

    std::cout << "All math2d tests passed\n";
    return 0;
}

