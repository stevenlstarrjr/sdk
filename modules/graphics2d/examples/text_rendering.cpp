/**
 * @file text_rendering.cpp
 * @brief Example demonstrating text rendering with Inter font
 *
 * This example loads the Inter variable font and demonstrates various
 * text rendering features including different sizes, colors, and metrics.
 */

#include "HImage.h"
#include "HPainter.h"
#include "HColor.h"
#include "HPen.h"
#include "HFont.h"
#include "HFontMetrics.h"
#include "HPointF.h"
#include "HRectF.h"
#include <iostream>
#include <string>

int main() {
    std::cout << "Hultrix Graphics2D - Text Rendering Example\n";
    std::cout << "=============================================\n\n";

    // Path to Inter font
    const std::string fontPath = "/home/stevenstarr/Projects/Hultrix/assets/font/Inter-4.1/InterVariable.ttf";

    // Create an 1000x800 image
    Ht::HImage image(1000, 800, Ht::HImage::Format::ARGB32_Premul);

    if (image.isNull()) {
        std::cerr << "Failed to create image!\n";
        return 1;
    }

    std::cout << "Created image: " << image.width() << "x" << image.height() << "\n";

    // Fill with light gray background
    image.fill(Ht::HColor::fromRgb(245, 245, 245));

    // Create painter
    Ht::HPainter painter;
    if (!painter.begin(&image)) {
        std::cerr << "Failed to begin painting!\n";
        return 1;
    }

    painter.setAntialiasing(true);

    // Load Inter font at various sizes
    std::cout << "Loading font: " << fontPath << "\n";

    Ht::HFont titleFont = Ht::HFont::fromFile(fontPath, 48.0f);
    if (!titleFont.isValid()) {
        std::cerr << "Failed to load font from: " << fontPath << "\n";
        return 1;
    }
    std::cout << "  Loaded font family: " << titleFont.family() << "\n";

    Ht::HFont headingFont = Ht::HFont::fromFile(fontPath, 32.0f);
    Ht::HFont bodyFont = Ht::HFont::fromFile(fontPath, 18.0f);
    Ht::HFont smallFont = Ht::HFont::fromFile(fontPath, 14.0f);

    // Draw title
    std::cout << "\nRendering text...\n";
    painter.setFont(titleFont);
    painter.setPen(Ht::HColor::fromRgb(20, 20, 20));
    painter.drawText(50.0f, 80.0f, "Hultrix Graphics2D");

    // Draw subtitle
    painter.setFont(bodyFont);
    painter.setPen(Ht::HColor::fromRgb(100, 100, 100));
    painter.drawText(50.0f, 120.0f, "Text Rendering with Inter Variable Font");

    // Draw heading
    painter.setFont(headingFont);
    painter.setPen(Ht::HColor::fromRgb(40, 40, 40));
    painter.drawText(50.0f, 180.0f, "Font Sizes & Colors");

    // Different sizes
    float y = 230.0f;
    for (float size : {12.0f, 16.0f, 20.0f, 24.0f, 30.0f, 36.0f}) {
        Ht::HFont font = Ht::HFont::fromFile(fontPath, size);
        painter.setFont(font);
        painter.setPen(Ht::HColor::fromRgb(60, 60, 60));

        std::string text = "The quick brown fox jumps - " + std::to_string(static_cast<int>(size)) + "pt";
        painter.drawText(50.0f, y, text);

        y += size * 1.5f;
    }

    // Different colors
    painter.setFont(headingFont);
    painter.setPen(Ht::HColor::fromRgb(40, 40, 40));
    painter.drawText(50.0f, 480.0f, "Color Variations");

    y = 530.0f;
    painter.setFont(bodyFont);

    painter.setPen(Ht::HColor::Red());
    painter.drawText(50.0f, y, "Red text example");

    y += 30.0f;
    painter.setPen(Ht::HColor::Green());
    painter.drawText(50.0f, y, "Green text example");

    y += 30.0f;
    painter.setPen(Ht::HColor::Blue());
    painter.drawText(50.0f, y, "Blue text example");

    y += 30.0f;
    painter.setPen(Ht::HColor::Magenta());
    painter.drawText(50.0f, y, "Magenta text example");

    y += 30.0f;
    painter.setPen(Ht::HColor::Cyan());
    painter.drawText(50.0f, y, "Cyan text example");

    // Font metrics demonstration
    painter.setFont(headingFont);
    painter.setPen(Ht::HColor::fromRgb(40, 40, 40));
    painter.drawText(550.0f, 180.0f, "Font Metrics");

    painter.setFont(bodyFont);
    painter.setPen(Ht::HColor::fromRgb(60, 60, 60));

    Ht::HFontMetrics metrics = bodyFont.metrics();

    y = 230.0f;
    float lineHeight = 25.0f;

    auto drawMetric = [&](const std::string& label, float value) {
        std::string text = label + ": " + std::to_string(value);
        painter.drawText(550.0f, y, text);
        y += lineHeight;
    };

    drawMetric("Ascent", metrics.ascent());
    drawMetric("Descent", metrics.descent());
    drawMetric("Height", metrics.height());
    drawMetric("Leading", metrics.leading());
    drawMetric("Line Spacing", metrics.lineSpacing());
    drawMetric("Avg Char Width", metrics.averageCharWidth());
    drawMetric("Max Char Width", metrics.maxCharWidth());

    // Text width measurements
    y += 20.0f;
    painter.drawText(550.0f, y, "Text Width Measurements:");
    y += lineHeight;

    std::string sampleText = "Hello, World!";
    float textWidth = painter.textWidth(sampleText);

    painter.drawText(550.0f, y, "\"" + sampleText + "\"");
    y += lineHeight;
    drawMetric("Width", textWidth);

    // Draw baseline and metrics visualization
    painter.setFont(headingFont);
    painter.setPen(Ht::HColor::fromRgb(40, 40, 40));
    painter.drawText(550.0f, 480.0f, "Baseline Guide");

    painter.setFont(Ht::HFont::fromFile(fontPath, 36.0f));
    float baselineY = 540.0f;
    std::string guideText = "Typography";

    Ht::HFontMetrics guideMetrics = painter.font().metrics();

    // Draw baseline
    painter.setPen(Ht::HPen(Ht::HColor::Red(), 1.0f));
    painter.drawLine(550.0f, baselineY, 950.0f, baselineY);

    // Draw ascent line
    painter.setPen(Ht::HPen(Ht::HColor::Blue(), 1.0f));
    painter.drawLine(550.0f, baselineY - guideMetrics.ascent(),
                     950.0f, baselineY - guideMetrics.ascent());

    // Draw descent line
    painter.setPen(Ht::HPen(Ht::HColor::Green(), 1.0f));
    painter.drawLine(550.0f, baselineY + guideMetrics.descent(),
                     950.0f, baselineY + guideMetrics.descent());

    // Draw text on baseline
    painter.setPen(Ht::HColor::fromRgb(40, 40, 40));
    painter.drawText(550.0f, baselineY, guideText);

    // Legend
    painter.setFont(smallFont);
    y = 600.0f;
    painter.setPen(Ht::HColor::Red());
    painter.drawText(550.0f, y, "— Baseline");
    y += 20.0f;
    painter.setPen(Ht::HColor::Blue());
    painter.drawText(550.0f, y, "— Ascent");
    y += 20.0f;
    painter.setPen(Ht::HColor::Green());
    painter.drawText(550.0f, y, "— Descent");

    // Footer
    painter.setFont(smallFont);
    painter.setPen(Ht::HColor::fromRgb(150, 150, 150));
    painter.drawText(50.0f, 760.0f, "Generated with Hultrix Graphics2D using Inter Variable Font");

    // End painting
    painter.end();

    // Save to PNG
    std::cout << "\nSaving to output/text_rendering.png...\n";
    if (image.save("output/text_rendering.png")) {
        std::cout << "Successfully saved image!\n";
    } else {
        std::cerr << "Failed to save image!\n";
        return 1;
    }

    std::cout << "\n✓ Text rendering example completed successfully!\n";
    return 0;
}
