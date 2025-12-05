#pragma once

#include "HPainter.h"
#include "HPen.h"
#include "HBrush.h"
#include "HColor.h"
#include "HFont.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkPaint.h"
#include <stack>

namespace Ht {

/**
 * @brief Private implementation for HPainter
 * Wraps Skia's SkCanvas and SkPaint directly
 */
struct HPainter::Impl {
    SkCanvas* canvas = nullptr;
    SkPaint strokePaint;
    SkPaint fillPaint;
    SkPaint textPaint;
    HPen currentPen;
    HBrush currentBrush;
    HFont currentFont;
    HColor backgroundColor;
    bool active = false;
    HImage* targetImage = nullptr;
    bool hasGradientFill = false;

    // Blur/shadow effect
    float blurRadius = 0.0f;
    bool blurEnabled = false;

    Impl();

    void updateStrokePaint();
    void updateFillPaint();
    void updateTextPaint();
    void updateBlurEffect();

    static SkPaint::Cap toSkCap(HPen::CapStyle cap);
    static SkPaint::Join toSkJoin(HPen::JoinStyle join);
    static void applyPenStyle(SkPaint& paint, HPen::Style style);
};

} // namespace Ht
