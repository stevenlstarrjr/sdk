#pragma once

#include <memory>
#include <string>

namespace Ht {

class HWindow;
class HScreen;

/**
 * @brief HApplication manages the GUI application lifecycle
 * Qt Equivalent: QGuiApplication / QApplication
 * Wayland Backend: wl_display (client-side)
 *
 * This is the entry point for Wayland client applications.
 * Manages the connection to the compositor, event loop, and windows.
 */
class HApplication {
public:
    // Constructor
    HApplication(int& argc, char** argv);
    ~HApplication();

    // Non-copyable, movable
    HApplication(const HApplication&) = delete;
    HApplication& operator=(const HApplication&) = delete;
    HApplication(HApplication&&) noexcept;
    HApplication& operator=(HApplication&&) noexcept;

    // Singleton instance access
    static HApplication* instance();

    // Execute the application event loop (blocks until quit)
    int exec();

    // Request application termination
    void quit();
    void exit(int returnCode = 0);

    // Application Metadata
    const std::string& applicationName() const;
    void setApplicationName(const std::string& name);

    const std::string& organizationName() const;
    void setOrganizationName(const std::string& name);

    const std::string& organizationDomain() const;
    void setOrganizationDomain(const std::string& domain);

    const std::string& applicationVersion() const;
    void setApplicationVersion(const std::string& version);

    // Input Devices
    class HKeyboard* keyboard() const;

    // Event Loop
    void processEvents();

    // Get all screens/outputs
    // const std::vector<HScreen*>& screens() const;

    // Get primary screen
    // HScreen* primaryScreen() const;

    // Wayland connection status
    bool isConnected() const;

    // Get Wayland display name (e.g., "wayland-0")
    const char* displayName() const;

    // Internal wayland display access (for gui internals)
    struct Impl;
    Impl* impl() const { return m_impl.get(); }

private:
    std::unique_ptr<Impl> m_impl;
    static HApplication* s_instance;
};

} // namespace Ht
