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
#include "HItem.h"
#include "HColor.h"
#include "HPen.h"
#include "HRectangle.h"
#include "HInput.h"
#include "HPainter.h"
#include "HRectF.h"
#include <iostream>
#include <functional>
#include <string>

// Custom item to test input events
class CustomRect : public Ht::HRectangle {
public:
    std::string m_name;

    CustomRect(const std::string& name, const Ht::HColor& color) 
        : Ht::HRectangle(color), m_name(name) {}

    // Callback to switch focus
    std::function<void()> onTabPressed;

    void onKeyPress(Ht::HKeyEvent& event) override {
        std::cout << "CustomRect(" << m_name << ")::onKeyPress: " << (int)event.key << std::endl;
        if (event.key == Ht::HKey::Space) {
            // Toggle color on Space
            static bool toggle = false;
            setColor(toggle ? Ht::HColor::fromHex("#FFFF00") : Ht::HColor::fromHex("#00FF00"));
            toggle = !toggle;
            update(); // Trigger repaint
        } else if (event.key == Ht::HKey::Tab) {
            if (onTabPressed) {
                onTabPressed();
            }
        }
    }

    void paintContent(Ht::HPainter& painter) override {
        // Draw default rect
        Ht::HRectangle::paintContent(painter);

        // Draw focus border if focused
        if (hasFocus()) {
            Ht::HPen pen(Ht::HColor::Red(), 4.0f);
            painter.setPen(pen);
            painter.setBrush(Ht::HColor::Transparent());
            painter.drawRect(Ht::HRectF(0, 0, (float)width(), (float)height()));
        }
    }
};

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

        // Create a root container
        auto* root = new Ht::HItem();

        // Add a custom rectangle that responds to input
        auto* rect1 = new CustomRect("Yellow", Ht::HColor::fromHex("#FFFF00"));
        rect1->setFixedSize(100, 100);
        rect1->setTop(50);
        rect1->setLeft(50);
        rect1->setNeedsOwnLayer(true);  // Enable layer-based compositing
        root->addChild(rect1);

        // Add a second custom rectangle
        auto* rect2 = new CustomRect("Cyan", Ht::HColor::fromHex("#00FFFF"));
        rect2->setFixedSize(100, 100);
        rect2->setTop(50);
        rect2->setLeft(200);
        rect2->setNeedsOwnLayer(true);  // Enable layer-based compositing
        root->addChild(rect2);
        
        // Wire up focus switching
        rect1->onTabPressed = [&window, rect2]() { window.setFocusItem(rect2); };
        rect2->onTabPressed = [&window, rect1]() { window.setFocusItem(rect1); };
        
        window.setContent(root);
        
        // Set focus to receive key events
        window.setFocusItem(rect1);

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

