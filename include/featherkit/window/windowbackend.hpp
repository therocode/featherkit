#pragma once
#include <featherkit/window/videomode.hpp>
#include <featherkit/window/windowstyle.hpp>
#include <featherkit/window/contextsettings.hpp>
#include <featherkit/window/vec2i.hpp>
#include <string>

namespace fea
{
    class WindowBackend
    {
        public:
            virtual void create(VideoMode mode, const std::string& title, uint32_t style=Style::Default, const ContextSettings& settings=ContextSettings()) = 0;
            virtual void close() = 0;
            virtual bool isOpen() const = 0;
            virtual const ContextSettings getSettings() const = 0;
            virtual Vec2I getPosition() const = 0;
            virtual void setPosition(int32_t x, int32_t y) = 0;
            virtual Vec2I getSize() const = 0;
            virtual void setSize (int32_t w, int32_t h) = 0;
            virtual void setTitle(const std::string& title) = 0;
            virtual void setIcon(uint32_t width, uint32_t height, const uint8_t* pixels) = 0;
            virtual void setVisible(bool visible) = 0;
            virtual void setVSyncEnabled(bool enabled) = 0;
            virtual void setMouseCursorVisible(bool visible) = 0;
            virtual void setFramerateLimit(uint32_t limit) = 0;
            virtual bool setRenderingActive(bool active=true) const = 0;
            virtual void swapBuffers() = 0;
			virtual void lockCursor(bool lock) = 0;
            virtual ~WindowBackend(){};
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
     *  @fn Vec2I WindowBackend::getPosition() const
     *  @brief Get the current position of the Window on the screen.
     *  @return Vector with the x and y coordinates.
     ***
     *  @fn void WindowBackend::setPosition(int32_t x, int32_t y)
     *  @brief Set the Window position on the screen.
     *  @param x X coordinate to set the window position to.
     *  @param y Y coordinate to set the window position to.
     ***
     *  @fn Vec2I WindowBackend::getSize() const
     *  @brief Get the current size of the Window.
     *  @return Vector with the width and height of the Window.
     ***
     *  @fn void WindowBackend::setSize(int32_t w, int32_t h)
     *  @brief Set the current size of the Window.
     *  @param w Width.
     *  @param h Height.
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
     *  @fn void WindowBackend::swapBuffers()
     *  @brief Swaps the front and back buffers, causing what has been rendered on the Window so far to be displayed.
     ***
     *  @fn virtual WindowBackend::~WindowBackend()
     *  @brief Destructor.
	 ***
     *  @fn void WindowBackend::lockCursor(bool lock)
     *  @brief Clips the cursor to the window bounds.
     *  @param lock wether or not to lock.
     ***/
}
