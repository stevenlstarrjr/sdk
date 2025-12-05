/**
 * @file paintdevice_example.cpp
 * @brief Example demonstrating HRasterPaintDevice with HPainter
 */

#include "HRasterPaintDevice.h"
#include "HPainter.h"
#include "HColor.h"
#include "HPen.h"
#include "HBrush.h"
#include "HRectF.h"
#include <iostream>

int main() {
    std::cout << "Hultrix Graphics2D - PaintDevice Example\n";
    std::cout << "=========================================\n\n";

    Ht::HRasterPaintDevice device(800, 600);

    Ht::HPainter painter;
    if (!painter.begin(&device)) {
        std::cerr << "Failed to begin painting on paint device!\n";
        return 1;
    }

    painter.setAntialiasing(true);

    painter.setBrush(Ht::HColor::fromRgb(245, 245, 245));
    painter.setPen(Ht::HPen::Style::NoPen);
    painter.drawRect(Ht::HRectF(0.0f, 0.0f, 800.0f, 600.0f));

    painter.setBrush(Ht::HColor::fromRgb(200, 230, 255));
    painter.setPen(Ht::HPen(Ht::HColor::fromRgb(40, 80, 160), 3.0f));
    painter.drawRoundedRect(Ht::HRectF(200.0f, 150.0f, 400.0f, 300.0f), 30.0f, 30.0f);

    painter.end();

    std::cout << "\nSaving to output/paintdevice_example.png...\n";
    if (device.image().save("output/paintdevice_example.png")) {
        std::cout << "Successfully saved image!\n";
    } else {
        std::cerr << "Failed to save image!\n";
        return 1;
    }

    std::cout << "\n✓ PaintDevice example completed successfully!\n";
    return 0;
}

