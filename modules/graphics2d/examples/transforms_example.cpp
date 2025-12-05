/**
 * @file transforms_example.cpp
 * @brief Example demonstrating HTransform with HPainter
 */

#include "HImage.h"
#include "HPainter.h"
#include "HColor.h"
#include "HPen.h"
#include "HBrush.h"
#include "HRectF.h"
#include "HTransform.h"
#include <iostream>

int main() {
    std::cout << "Hultrix Graphics2D - Transforms Example\n";
    std::cout << "========================================\n\n";

    Ht::HImage image(800, 600, Ht::HImage::Format::ARGB32_Premul);
    if (image.isNull()) {
        std::cerr << "Failed to create image!\n";
        return 1;
    }

    image.fill(Ht::HColor::fromRgb(250, 250, 250));

    Ht::HPainter painter;
    if (!painter.begin(&image)) {
        std::cerr << "Failed to begin painting!\n";
        return 1;
    }

    painter.setAntialiasing(true);

    // Base rectangle (no transform)
    Ht::HRectF baseRect(100.0f, 100.0f, 200.0f, 120.0f);
    painter.setBrush(Ht::HColor::fromRgb(220, 220, 220));
    painter.setPen(Ht::HPen(Ht::HColor::Black(), 2.0f));
    painter.drawRect(baseRect);

    // Rotated copy using HTransform
    Ht::HTransform tRotate = Ht::HTransform::fromTranslate(400.0f, 160.0f);
    tRotate.rotate(30.0f);
    tRotate.translate(-100.0f, -60.0f); // center about origin before rotation

    painter.setBrush(Ht::HColor::fromRgb(180, 220, 255));
    painter.setPen(Ht::HPen(Ht::HColor::fromRgb(40, 80, 140), 2.0f));
    painter.setTransform(tRotate);
    painter.drawRect(baseRect);

    // Combined scale and rotation using setWorldTransform(combine)
    Ht::HTransform tWorld;
    tWorld.translate(400.0f, 380.0f);
    tWorld.rotate(-20.0f);
    tWorld.scale(1.2f, 0.8f);
    tWorld.translate(-100.0f, -60.0f);

    painter.setBrush(Ht::HColor::fromRgb(200, 255, 200));
    painter.setPen(Ht::HPen(Ht::HColor::fromRgb(40, 120, 40), 2.0f));
    painter.setWorldTransform(tWorld);
    painter.drawRect(baseRect);

    // Reset transforms and draw reference frame
    painter.resetTransform();
    painter.setPen(Ht::HPen(Ht::HColor::Red(), 1.0f));
    painter.drawLine(0.0f, 300.0f, 800.0f, 300.0f);
    painter.drawLine(400.0f, 0.0f, 400.0f, 600.0f);

    painter.end();

    std::cout << "\nSaving to output/transforms_example.png...\n";
    if (image.save("output/transforms_example.png")) {
        std::cout << "Successfully saved image!\n";
    } else {
        std::cerr << "Failed to save image!\n";
        return 1;
    }

    std::cout << "\n✓ Transforms example completed successfully!\n";
    return 0;
}

