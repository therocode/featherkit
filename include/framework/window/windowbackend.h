#pragma once
#include <framework/window/videomode.h>
#include <framework/window/windowstyle.h>
#include <framework/window/contextsettings.h>
#include <framework/internal/vec2.h>
#include <string>

namespace windbreeze
{
    class WindowBackend
    {
        public:
            virtual void create(VideoMode mode, const std::string& title, uint32_t style=Style::Default, const ContextSettings& settings=ContextSettings()) = 0;
            virtual void close() = 0;
            virtual bool isOpen() const = 0;
            virtual const ContextSettings getSettings() const = 0;
            virtual IntVec2 getPosition() const = 0;
            virtual void setPosition(const IntVec2& position) = 0;
            virtual IntVec2 getSize() const = 0;
            virtual void setSize (const IntVec2& size) = 0;
            virtual void setTitle(const std::string& title) = 0;
            virtual void setIcon(uint32_t width, uint32_t height, const uint8_t* pixels) = 0;
            virtual void setVisible(bool visible) = 0;
            virtual void setVSyncEnabled(bool enabled) = 0;
            virtual void setMouseCursorVisible(bool visible) = 0;
            virtual void setFramerateLimit(uint32_t limit) = 0;
            virtual bool setRenderingActive(bool active=true) const = 0;
            virtual void display() = 0;
    };
    /** @addtogroup UserInterface
     *@{
     *  @class WindowBackend
     *@}
     ***
     *  @class WindowBackend
     *  @brief Abstract base class for implementing varous Window backends.
     ***
     *  @fn void WindowBackend::create(VideoMode mode, const std::string& title, uint32_t style=Style::Default, const ContextSettings& settings=ContextSettings())
     *  @brief Create a window and open it.
     *
     *  This opens the window with the given settings.
     *  @param mode Video mode to use.
     *  @param title Desired title bar name.
     *  @param style Window style to use.
     *  @param settings OpenGL context settings to use.
     ***
     *  @fn void WindowBackend::close()
     *  @brief Close the window.
     ***
     *  @fn bool WindowBackend::isOpen() const
     *  @brief Check if the window is currently open.
     *  @return True if the window is open, otherwise false.
     ***
     *  @fn const ContextSettings WindowBackend::getSettings() const
     *  @brief Access the OpenGL settings of the Window.
     *  @return Struct containing the settings.
     ***
     *  @fn IntVec2 WindowBackend::getPosition() const
     *  @brief Get the current position of the Window on the screen.
     *  @return Vector with the x and y coordinates.
     ***
     *  @fn void WindowBackend::setPosition(const IntVec2& position)
     *  @brief Set the Window position on the screen.
     *  @param position Vector with the coordinates to set the window position to.
     ***
     *  @fn IntVec2 WindowBackend::getSize() const
     *  @brief Get the current size of the Window.
     *  @return Vector with the width and height of the Window.
     ***
     *  @fn void WindowBackend::setSize(const IntVec2& size)
     *  @brief Set the current size of the Window.
     *  @param size Vector with the height and width of the desired Window size.
     ***
     *  @fn void WindowBackend::setTitle(const std::string& title)
     *  @brief Set the title name of the window.
     *  @param title Name to set.
     ***
     *  @fn void WindowBackend::setIcon(uint32_t width, uint32_t height, const uint8_t* pixels)
     *  @brief Set the icon of the window.
     *  @param width Width of the icon.
     *  @param height Height of the icon.
     *  @param pixels Array of pixel data of an image to use for the icon.
     ***
     *  @fn void WindowBackend::setVisible(bool visible)
     *  @brief Set visibility of the Window.
     *  @param visible Visibility to set. True is visible and false is hidden.
     ***
     *  @fn void WindowBackend::setVSyncEnabled(bool enabled)
     *  @brief Enable or disable VSync.
     *  @param enabled True for on, false for off.
     ***
     *  @fn void WindowBackend::setMouseCursorVisible(bool visible)
     *  @brief Toggle visibility of the mouse cursor.
     *  @param visible True for on, false for off.
     ***
     *  @fn void WindowBackend::setFramerateLimit(uint32_t limit)
     *  @brief Set the framerate limit of the Window.
     *  @param limit Limit to set in Hertz.
     ***
     *  @fn bool WindowBackend::setRenderingActive(bool active=true) const
     *  @brief Toggle this Window as a target for rendering.
     *  @param active True to set rendering to on, false for off. Default is true.
     *  @return True if the operation succeeded, otherwise false.
     ***
     *  @fn void WindowBackend::display()
     *  @brief Displays what has been rendered on the Window so far.
     **/
}
