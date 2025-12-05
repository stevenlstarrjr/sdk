/**
 * @file basic_shapes.cpp
 * @brief Example demonstrating basic 2D shapes rendering with Hultrix graphics2d
 *
 * This example creates various shapes and renders them to a PNG image to verify
 * the graphics2d API is working correctly.
 */

#include "HImage.h"
#include "HPainter.h"
#include "HColor.h"
#include "HPen.h"
#include "HBrush.h"
#include "HPointF.h"
#include "HRectF.h"
#include <iostream>
#include <vector>

int main() {
    std::cout << "Hultrix Graphics2D - Basic Shapes Example\n";
    std::cout << "==========================================\n\n";

    // Create an 800x600 image with ARGB32 format
    Ht::HImage image(800, 600, Ht::HImage::Format::ARGB32_Premul);

    if (image.isNull()) {
        std::cerr << "Failed to create image!\n";
        return 1;
    }

    std::cout << "Created image: " << image.width() << "x" << image.height() << "\n";

    // Fill with white background
    image.fill(Ht::HColor::White());

    // Create painter
    Ht::HPainter painter;
    if (!painter.begin(&image)) {
        std::cerr << "Failed to begin painting!\n";
        return 1;
    }

    // Enable antialiasing
    painter.setAntialiasing(true);

    // Draw a red rectangle with blue outline
    std::cout << "Drawing rectangle...\n";
    painter.setPen(Ht::HPen(Ht::HColor::Blue(), 3.0f));
    painter.setBrush(Ht::HColor(255, 100, 100)); // Light red
    painter.drawRect(Ht::HRectF(50, 50, 200, 150));

    // Draw a green circle
    std::cout << "Drawing circle...\n";
    painter.setPen(Ht::HPen(Ht::HColor(0, 100, 0), 2.0f)); // Dark green
    painter.setBrush(Ht::HColor(100, 255, 100)); // Light green
    painter.drawEllipse(Ht::HRectF(300, 50, 150, 150));

    // Draw a yellow rounded rectangle
    std::cout << "Drawing rounded rectangle...\n";
    painter.setPen(Ht::HPen(Ht::HColor(200, 150, 0), 2.5f));
    painter.setBrush(Ht::HColor::Yellow());
    painter.drawRoundedRect(Ht::HRectF(500, 50, 250, 150), 20.0f, 20.0f);

    // Draw a line
    std::cout << "Drawing line...\n";
    painter.setPen(Ht::HPen(Ht::HColor::Black(), 4.0f, Ht::HPen::Style::SolidLine,
                            Ht::HPen::CapStyle::RoundCap));
    painter.drawLine(Ht::HPointF(50, 250), Ht::HPointF(750, 250));

    // Clip to a central band using HRegion and draw a polygon (triangle)
    std::cout << "Drawing triangle...\n";
    // Use save/restore around clipping so later drawing is unaffected
    painter.save();
    Ht::HRegion clipBand(Ht::HRect(0, 280, 800, 260));
    painter.setClipRegion(clipBand);

    std::vector<Ht::HPointF> triangle = {
        Ht::HPointF(150, 300),
        Ht::HPointF(250, 500),
        Ht::HPointF(50, 500)
    };
    painter.setPen(Ht::HPen(Ht::HColor(100, 0, 100), 3.0f));
    painter.setBrush(Ht::HColor::Magenta());
    // Apply a simple rectangular clip so the triangle is only visible in a band
    painter.drawPolygon(triangle);
    painter.restore();

    // Draw a polyline (zigzag)
    std::cout << "Drawing polyline...\n";
    std::vector<Ht::HPointF> zigzag = {
        Ht::HPointF(350, 300),
        Ht::HPointF(400, 350),
        Ht::HPointF(450, 300),
        Ht::HPointF(500, 350),
        Ht::HPointF(550, 300),
        Ht::HPointF(600, 350),
        Ht::HPointF(650, 300)
    };
    painter.setPen(Ht::HPen(Ht::HColor::Cyan(), 5.0f));
    painter.drawPolyline(zigzag);

    // Draw multiple circles with transformation
    std::cout << "Drawing transformed circles...\n";
    painter.save();
    painter.translate(550.0f, 450.0f);
    for (int i = 0; i < 8; ++i) {
        float angle = i * 45.0f;
        painter.save();
        painter.rotate(angle);
        painter.setBrush(Ht::HColor::fromRgb(
            static_cast<int>(255 * (i / 8.0f)),
            static_cast<int>(100 + 155 * (1 - i / 8.0f)),
            static_cast<int>(200 - 100 * (i / 8.0f))
        ));
        painter.setPen(Ht::HPen::Style::NoPen);
        painter.drawEllipse(Ht::HRectF(60, -15, 30, 30));
        painter.restore();
    }
    painter.restore();

    // Draw some points
    std::cout << "Drawing points...\n";
    painter.setPen(Ht::HPen(Ht::HColor::Red(), 8.0f, Ht::HPen::Style::SolidLine,
                            Ht::HPen::CapStyle::RoundCap));
    std::vector<Ht::HPointF> points = {
        Ht::HPointF(350, 450),
        Ht::HPointF(380, 430),
        Ht::HPointF(410, 470),
        Ht::HPointF(440, 440),
        Ht::HPointF(470, 480)
    };
    painter.drawPoints(points);

    // End painting
    painter.end();

    // Save to PNG
    std::cout << "\nSaving to output/basic_shapes.png...\n";
    if (image.save("output/basic_shapes.png")) {
        std::cout << "Successfully saved image!\n";
    } else {
        std::cerr << "Failed to save image!\n";
        return 1;
    }

    std::cout << "\n✓ Example completed successfully!\n";
    return 0;
}
