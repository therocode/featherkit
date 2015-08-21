#pragma once
#include <fea/config.hpp>
#include <fea/ui/videomode.hpp>
#include <fea/ui/contextsettings.hpp>
#include <fea/ui/windowstyle.hpp>
#include <fea/ui/vec2i.hpp>
#include <string>
#include <memory>
            /* from videomode and should be here
            static VideoMode getDesktopMode();
            static const std::vector<VideoMode>& getFullscreenModes();
            bool isValid() const; */

namespace fea
{
    class WindowBackend;

    class FEA_API Window
    {

        public:
            Window(WindowBackend* windowBackend);
            Window(WindowBackend* windowBackend, VideoMode mode, const std::string& title, uint32_t style = Style::Default, const ContextSettings& settings = ContextSettings());
            void open(VideoMode mode, const std::string& title, uint32_t style = Style::Default, const ContextSettings& settings = ContextSettings());
            void close();
            bool isOpen() const;
            const ContextSettings getSettings() const;
            Vec2I getPosition() const;
            void setPosition(int32_t x, int32_t y);
            Vec2I getSize() const;
            void setSize(int32_t w, int32_t h);
            void setTitle(const std::string& title);
            void setIcon(uint32_t width, uint32_t height, const uint8_t* pixels);
            void setVisible(bool visible);
            void setVSyncEnabled(bool enabled);
            void setMouseCursorVisible(bool visible);
            void setFramerateLimit(uint32_t limit);
            bool setRenderingActive(bool active = true) const;
            void swapBuffers();
			void lockCursor(bool enabled);
        private:
            std::unique_ptr<WindowBackend> mWindowBackend;
    };
    /** @addtogroup UserInterface
     *@{
     *  @class Window
     *@}
     *  @class Window
     *  @brief Class that manages a window instance for the application.
     *
     *  The window can be opened with different settings, including resolution and title. To make the window cross platform and flexible, it needs a backend implementation. This backend could for instance be based on OpenGL, Direct X or even ncurses. Depending on the backend, the window's capabilities and settings may vary.
     *
     *  The API of this class is heavily inspired by the window class of [SFML](http://www.sfml-dev.org/).
     ***
     *  @fn Window::Window(WindowBackend* windowBackend)
     *  @brief Construct a window using the specified backend.
     *  @param windowBackend Backend to use with the window instance. Will be stored as an std::unique_ptr and therefore memory will be managed.
     ***
     *  @fn Window::Window(WindowBackend* windowBackend, VideoMode mode, const std::string& title, uint32_t style = Style::Default, const ContextSettings& settings = ContextSettings())
     *  @brief Construct a window using the specified backend and open it with the given parameters.
     *  @param windowBackend Backend to use with the window instance. Will be stored as an std::unique_ptr and therefore memory will be managed.
     *  @param mode Video mode to use.
     *  @param title Desired title bar name.
     *  @param style Window style to use.
     *  @param settings OpenGL context settings to use.
     ***
     *  @fn void Window::open(VideoMode mode, const std::string& title, uint32_t style=Style::Default, const ContextSettings& settings=ContextSettings())
     *  @brief Create a window and open it.
     *
     *  This opens the window with the given settings.
     *  @param mode Video mode to use.
     *  @param title Desired title bar name.
     *  @param style Window style to use.
     *  @param settings OpenGL context settings to use.
     ***
     *  @fn void Window::close()
     *  @brief Close the window.
     ***
     *  @fn bool Window::isOpen() const
     *  @brief Check if the window is currently open.
     *  @return True if the window is open, otherwise false.
     ***
     *  @fn const ContextSettings Window::getSettings() const
     *  @brief Access the OpenGL settings of the Window.
     *  @return Struct containing the settings.
     ***
     *  @fn Vec2I Window::getPosition() const
     *  @brief Get the current position of the Window on the screen.
     *  @return Vector with the x and y coordinates.
     ***
     *  @fn void Window::setPosition(int32_t x, int32_t y)
     *  @brief Set the Window position on the screen.
     *  @param x X coordinate.
     *  @param y Y coordinate.
     ***
     *  @fn Vec2I Window::getSize() const
     *  @brief Get the current size of the Window.
     *  @return Vector with the width and height of the Window.
     ***
     *  @fn void Window::setSize(int32_t w, int32_t h)
     *  @brief Set the current size of the Window.
     *  @param w Width.
     *  @param h Height.
     ***
     *  @fn void Window::setTitle(const std::string& title)
     *  @brief Set the title name of the window.
     *  @param title Name to set.
     ***
     *  @fn void Window::setIcon(uint32_t width, uint32_t height, const uint8_t* pixels)
     *  @brief Set the icon of the window.
     *  @param width Width of the icon.
     *  @param height Height of the icon.
     *  @param pixels Array of pixel data of an image to use for the icon.
     ***
     *  @fn void Window::setVisible(bool visible)
     *  @brief Set visibility of the Window.
     *  @param visible Visibility to set. True is visible and false is hidden.
     ***
     *  @fn void Window::setVSyncEnabled(bool enabled)
     *  @brief Enable or disable VSync.
     *  @param enabled True for on, false for off.
     ***
     *  @fn void Window::setMouseCursorVisible(bool visible)
     *  @brief Toggle visibility of the mouse cursor.
     *  @param visible True for on, false for off.
     ***
     *  @fn void Window::setFramerateLimit(uint32_t limit)
     *  @brief Set the framerate limit of the Window.
     *  @param limit Limit to set in Hertz.
     ***
     *  @fn bool Window::setRenderingActive(bool active=true) const
     *  @brief Toggle this Window as a target for rendering.
     *  @param active True to set rendering to on, false for off. Default is true.
     *  @return True if the operation succeeded, otherwise false.
     ***
     *  @fn void Window::swapBuffers()
     *  @brief Swaps the front and back buffers, causing what has been rendered on the Window so far to be displayed.
	 ***
     *  @fn void Window::lockCursor(bool enabled)
     *  @brief Locks the cursor to the window.
     *  @param enabled True to lock, false to unlock.
     **/
}
