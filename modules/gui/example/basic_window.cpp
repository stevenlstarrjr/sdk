/**
 * @file basic_window.cpp
 * @brief Example demonstrating HWindow with custom visual properties
 *
 * Creates a single top-level window using XDG shell with customizable:
 * - Border radius (rounded corners)
 * - Border pen (stroke)
 * - Background color
 * - Drop shadow (features beyond Qt!)
 */

#include "HApplication.h"
#include "HWindow.h"
#include "HColor.h"
#include "HPen.h"
#include "HRectangle.h"
#include <iostream>

int main(int argc, char** argv) {
    try {
        Ht::HApplication app(argc, argv);

        Ht::HWindow window(&app);
        window.setTitle("Hultrix GUI - Custom Window");

        // Customize visual appearance (features beyond Qt!)
        window.setBorderRadius(20.0f);  // Large rounded corners for visibility

        // Custom border using hex colors
        Ht::HPen borderPen(Ht::HColor::fromHex("#FF6DD9"), 2.0f, Ht::HPen::Style::SolidLine);
        window.setBorderPen(borderPen);

        // Dark blue-gray background using hex
        window.setBackgroundColor(Ht::HColor::fromHex("#DC00A3"));

        // Enable drop shadow
        window.setDropShadowEnabled(true);
        window.setDropShadowOffset(0.0f, 0.0f);  // No offset, evenly distributed
        window.setDropShadowBlurRadius(5.0f);    // Slightly larger blur
        window.setDropShadowColor(Ht::HColor::fromHex("#000000DC"));  // Very dark with alpha

        window.resize(600, 400);

        // Add a simple rectangle
        auto* rect = new Ht::HRectangle(Ht::HColor::fromHex("#FFFF00"));
        rect->setFixedSize(100, 100);
        rect->setTop(50);
        rect->setLeft(50);
        
        // Manual layout update since HWindow doesn't do it automatically anymore
        rect->updateLayout();
        
        window.setContent(rect);

        window.show();

        std::cout << "Connected to Wayland display: "
                  << (app.displayName() ? app.displayName() : "(unknown)")
                  << std::endl;
        std::cout << "Window customization: radius=" << window.borderRadius()
                  << "px, shadow=" << (window.dropShadowEnabled() ? "on" : "off") << std::endl;

        return app.exec();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}

