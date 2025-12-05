/**
 * @file picture_example.cpp
 * @brief Example demonstrating HPicture and HPictureRecorder
 */

#include "HImage.h"
#include "HPainter.h"
#include "HColor.h"
#include "HPen.h"
#include "HBrush.h"
#include "HRectF.h"
#include "HPicture.h"
#include "HPictureRecorder.h"
#include <iostream>

int main() {
    std::cout << "Hultrix Graphics2D - Picture Example\n";
    std::cout << "====================================\n\n";

    // Record a simple picture: a rounded rectangle with a border
    Ht::HPictureRecorder recorder;
    Ht::HRectF bounds(0.0f, 0.0f, 200.0f, 120.0f);

    if (!recorder.begin(bounds)) {
        std::cerr << "Failed to begin picture recording!\n";
        return 1;
    }

    Ht::HPainter* picPainter = recorder.painter();
    picPainter->setAntialiasing(true);
    picPainter->setBrush(Ht::HColor::fromRgb(230, 240, 255));
    picPainter->setPen(Ht::HPen(Ht::HColor::fromRgb(40, 80, 160), 2.0f));
    picPainter->drawRoundedRect(bounds, 20.0f, 20.0f);

    Ht::HPicture picture = recorder.end();

    // Now play the picture into an image at multiple offsets
    Ht::HImage image(800, 600, Ht::HImage::Format::ARGB32_Premul);
    if (image.isNull()) {
        std::cerr << "Failed to create image!\n";
        return 1;
    }

    image.fill(Ht::HColor::White());

    Ht::HPainter painter;
    if (!painter.begin(&image)) {
        std::cerr << "Failed to begin painting on image!\n";
        return 1;
    }

    painter.setAntialiasing(true);

    painter.drawPicture(picture, Ht::HPointF(100.0f, 100.0f));
    painter.drawPicture(picture, Ht::HPointF(350.0f, 220.0f));
    painter.drawPicture(picture, Ht::HPointF(200.0f, 380.0f));

    painter.end();

    std::cout << "\nSaving to output/picture_example.png...\n";
    if (image.save("output/picture_example.png")) {
        std::cout << "Successfully saved image!\n";
    } else {
        std::cerr << "Failed to save image!\n";
        return 1;
    }

    std::cout << "\n✓ Picture example completed successfully!\n";
    return 0;
}

