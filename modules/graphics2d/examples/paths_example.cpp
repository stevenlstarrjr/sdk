/**
 * @file paths_example.cpp
 * @brief Example demonstrating vector paths and boolean operations
 *
 * This example builds complex shapes using HPainterPath and renders
 * unions, intersections, and subtractions to a PNG image.
 */

#include "HImage.h"
#include "HPainter.h"
#include "HColor.h"
#include "HPen.h"
#include "HBrush.h"
#include "HRectF.h"
#include "HPainterPath.h"
#include <iostream>

int main() {
    std::cout << "Hultrix Graphics2D - Paths Example\n";
    std::cout << "===================================\n\n";

    // Create image
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

    // Base shapes
    Ht::HPainterPath rectPath;
    rectPath.addRect(Ht::HRectF(100.0f, 150.0f, 250.0f, 200.0f));

    Ht::HPainterPath circlePath;
    circlePath.addEllipse(Ht::HRectF(200.0f, 100.0f, 250.0f, 250.0f));

    // Boolean combinations
    Ht::HPainterPath unionPath = rectPath.united(circlePath);
    Ht::HPainterPath intersectPath = rectPath.intersected(circlePath);
    Ht::HPainterPath subtractPath = rectPath.subtracted(circlePath);

    // Original shapes (outline only)
    painter.setBrush(Ht::HBrush::Style::NoBrush);
    painter.setPen(Ht::HPen(Ht::HColor::LightGray(), 2.0f));
    painter.drawPath(rectPath);
    painter.drawPath(circlePath);

    // Draw union on left
    painter.save();
    painter.translate(0.0f, 0.0f);
    painter.setBrush(Ht::HColor(200, 230, 255));
    painter.setPen(Ht::HPen(Ht::HColor::Blue(), 2.0f));
    painter.drawPath(unionPath);
    painter.restore();

    // Draw intersection in middle
    painter.save();
    painter.translate(260.0f, 0.0f);
    painter.setBrush(Ht::HColor(200, 255, 200));
    painter.setPen(Ht::HPen(Ht::HColor::Green(), 2.0f));
    painter.drawPath(intersectPath);
    painter.restore();

    // Draw subtraction on right
    painter.save();
    painter.translate(520.0f, 0.0f);
    painter.setBrush(Ht::HColor(255, 220, 200));
    painter.setPen(Ht::HPen(Ht::HColor::Red(), 2.0f));
    painter.drawPath(subtractPath);
    painter.restore();

    // Demonstrate cubic curve
    Ht::HPainterPath curvePath;
    curvePath.moveTo(100.0f, 450.0f);
    curvePath.cubicTo(250.0f, 350.0f, 550.0f, 550.0f, 700.0f, 450.0f);

    painter.setBrush(Ht::HBrush::Style::NoBrush);
    painter.setPen(Ht::HPen(Ht::HColor::Magenta(), 4.0f));
    painter.drawPath(curvePath);

    painter.end();

    std::cout << "\nSaving to output/paths_example.png...\n";
    if (image.save("output/paths_example.png")) {
        std::cout << "Successfully saved image!\n";
    } else {
        std::cerr << "Failed to save image!\n";
        return 1;
    }

    std::cout << "\n✓ Paths example completed successfully!\n";
    return 0;
}

