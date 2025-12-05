/**
 * @file gradients_example.cpp
 * @brief Example demonstrating linear gradients with HPainter
 */

#include "HImage.h"
#include "HPainter.h"
#include "HColor.h"
#include "HGradient.h"
#include "HRectF.h"
#include <iostream>

int main() {
    std::cout << "Hultrix Graphics2D - Gradients Example\n";
    std::cout << "=======================================\n\n";

    Ht::HImage image(800, 600, Ht::HImage::Format::ARGB32_Premul);
    if (image.isNull()) {
        std::cerr << "Failed to create image!\n";
        return 1;
    }

    image.fill(Ht::HColor::White());

    Ht::HPainter painter;
    if (!painter.begin(&image)) {
        std::cerr << "Failed to begin painting!\n";
        return 1;
    }

    painter.setAntialiasing(true);

    // Background vertical gradient
    Ht::HLinearGradient backgroundGrad(
        Ht::HPointF(0.0f, 0.0f),
        Ht::HPointF(0.0f, 600.0f));
    backgroundGrad.setSpread(Ht::HGradient::Spread::Pad);
    backgroundGrad.setStops({
        {0.0f, Ht::HColor::fromRgb(40, 40, 80)},
        {0.5f, Ht::HColor::fromRgb(80, 120, 200)},
        {1.0f, Ht::HColor::fromRgb(220, 240, 255)}
    });

    painter.setBrush(backgroundGrad);
    painter.setPen(Ht::HPen::Style::NoPen);
    painter.drawRect(Ht::HRectF(0.0f, 0.0f, 800.0f, 600.0f));

    // Horizontal linear gradient bar
    Ht::HLinearGradient barGrad(
        Ht::HPointF(100.0f, 200.0f),
        Ht::HPointF(700.0f, 200.0f));
    barGrad.setSpread(Ht::HGradient::Spread::Pad);
    barGrad.setStops({
        {0.0f, Ht::HColor::Red()},
        {0.5f, Ht::HColor::Yellow()},
        {1.0f, Ht::HColor::Green()}
    });

    painter.setBrush(barGrad);
    painter.setPen(Ht::HPen(Ht::HColor::Black(), 2.0f));
    painter.drawRoundedRect(Ht::HRectF(100.0f, 200.0f, 600.0f, 80.0f), 20.0f, 20.0f);

    // Radial gradient circle
    Ht::HRadialGradient radialGrad(
        Ht::HPointF(250.0f, 420.0f),
        80.0f);
    radialGrad.setSpread(Ht::HGradient::Spread::Pad);
    radialGrad.setStops({
        {0.0f, Ht::HColor::fromRgb(255, 255, 255)},
        {1.0f, Ht::HColor::fromRgb(0, 128, 255)}
    });

    painter.setBrush(radialGrad);
    painter.setPen(Ht::HPen(Ht::HColor::Black(), 2.0f));
    painter.drawEllipse(Ht::HRectF(170.0f, 340.0f, 160.0f, 160.0f));

    // Conical (sweep) gradient circle
    Ht::HConicalGradient conicalGrad(
        Ht::HPointF(550.0f, 420.0f),
        0.0f);
    conicalGrad.setSpread(Ht::HGradient::Spread::Pad);
    conicalGrad.setStops({
        {0.0f, Ht::HColor::Red()},
        {0.25f, Ht::HColor::Yellow()},
        {0.5f, Ht::HColor::Green()},
        {0.75f, Ht::HColor::Cyan()},
        {1.0f, Ht::HColor::Red()}
    });

    painter.setBrush(conicalGrad);
    painter.setPen(Ht::HPen(Ht::HColor::Black(), 2.0f));
    painter.drawEllipse(Ht::HRectF(470.0f, 340.0f, 160.0f, 160.0f));

    painter.end();

    std::cout << "\nSaving to output/gradients_example.png...\n";
    if (image.save("output/gradients_example.png")) {
        std::cout << "Successfully saved image!\n";
    } else {
        std::cerr << "Failed to save image!\n";
        return 1;
    }

    std::cout << "\n✓ Gradients example completed successfully!\n";
    return 0;
}
