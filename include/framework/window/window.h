#pragma once
#include <framework/window/videomode.h>
#include <framework/window/contextsettings.h>
#include <framework/window/windowstyle.h>
#include <framework/glm/glm.hpp>
#include <string>
            /* hej this is from VidyaMöåd and should be here
            static VideoMode getDesktopMode();
            static const std::vector<VideoMode>& getFullscreenModes();
            bool isValid() const; */

namespace windbreeze
{
    class WindowBackend;

    class Window
    {
        public:
            Window(WindowBackend& backend) : windowBackend(backend) {}
            void create(VideoMode mode, const std::string& title, uint32_t style=Style::Default, const ContextSettings& settings=ContextSettings());
            void close();
            bool isOpen() const;
            const ContextSettings getSettings() const;
            glm::ivec2 getPosition() const;
            void setPosition(const glm::ivec2& position);
            glm::ivec2 getSize() const;
            void setSize(const glm::ivec2& size);
            void setTitle(const std::string& title);
            void setIcon(uint32_t width, uint32_t height, const uint8_t* pixels);
            void setVisible(bool visible);
            void setVSyncEnabled(bool enabled);
            void setMouseCursorVisible(bool visible);
            void setFramerateLimit(uint32_t limit);
            bool setRenderingActive(bool active=true) const;
            void display();


        private:
            WindowBackend& windowBackend;
    };
    /** @addtogroup UserInterface
     *@{
     *  @class Window
     *@}
     ***
     *  @class Window
     *  @brief Class that manages a window instance for the application.
     *
     *  The window can be created with different settings, including resolution and title. To make the window cross platform and flexible, it needs a backend implementation. This backend could for instance be based on OpenGL, Direct X or even ncurses. Depending on the backend, the window's capabilities and settings may vary.
     *
     *  The API of this class is heavily inspired by the window class of [SFML](http://www.sfml-dev.org/).
     ***
     *  @fn Window::Window(WindowBackend& backend)
     *  @brief Construct a window using the specified backend.
     *  @param backend Backend to use with the window instance. Will be stored as a reference. Some Window functions will modify the backend.
     ***
     *  @fn void Window::create(VideoMode mode, const std::string& title, uint32_t style=Style::Default, const ContextSettings& settings=ContextSettings())
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
     *  @fn IntVec2 Window::getPosition() const
     *  @brief Get the current position of the Window on the screen.
     *  @return Vector with the x and y coordinates.
     ***
     *  @fn void Window::setPosition(const IntVec2& position)
     *  @brief Set the Window position on the screen.
     *  @param position Vector with the coordinates to set the window position to.
     ***
     *  @fn IntVec2 Window::getSize() const
     *  @brief Get the current size of the Window.
     *  @return Vector with the width and height of the Window.
     ***
     *  @fn void Window::setSize(const IntVec2& size)
     *  @brief Set the current size of the Window.
     *  @param size Vector with the height and width of the desired Window size.
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
     *  @fn void Window::display()
     *  @brief Displays what has been rendered on the Window so far.
     **/
}
