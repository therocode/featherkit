#include <featherkit/util/window/sfml/sfmlwindowbackend.h>
#ifdef __WIN32__
#include <windows.h>
#endif
namespace fea
{
    namespace util
    {
        SFMLWindowBackend::SFMLWindowBackend(sf::Window& w) : window(w)
        {
        }

        void SFMLWindowBackend::create(VideoMode mode, const std::string& title, uint32_t style, const ContextSettings& settings)
        {
            sf::VideoMode vidMode(mode.width, mode.height, mode.bitsPerPixel);
            sf::ContextSettings conSettings(settings.depthBits, settings.stencilBits, settings.antialiasingLevel, settings.majorVersion, settings.minorVersion);
            window.create(vidMode, title, style, conSettings);
        }

        void SFMLWindowBackend::close()
        {
            window.close();
        }

        bool SFMLWindowBackend::isOpen() const
        {
            return window.isOpen();
        }

        const ContextSettings SFMLWindowBackend::getSettings() const
        {
            const sf::ContextSettings& settings = window.getSettings();
            const fea::ContextSettings toReturn(settings.depthBits, settings.stencilBits, settings.antialiasingLevel, settings.majorVersion, settings.minorVersion);
            return toReturn;
        }

        Vec2I SFMLWindowBackend::getPosition() const
        {
            sf::Vector2i position = window.getPosition();
            return {position.x, position.y};
        }

        void SFMLWindowBackend::setPosition(int32_t x, int32_t y)
        {
            window.setPosition({x, y});
        }

        Vec2I SFMLWindowBackend::getSize() const
        {
            sf::Vector2u position = window.getSize();
            return {(int32_t)position.x, (int32_t)position.y};
        }

        void SFMLWindowBackend::setSize(int32_t w, int32_t h)
        {
            window.setSize({(uint32_t)w, (uint32_t)h});
        }

        void SFMLWindowBackend::setTitle(const std::string& title)
        {
            window.setTitle({title});
        }

        void SFMLWindowBackend::setIcon(uint32_t width, uint32_t height, const uint8_t* pixels)
        {
            window.setIcon(width, height, pixels);
        }

        void SFMLWindowBackend::setVisible(bool visible)
        {
            window.setVisible(visible);
        }

        void SFMLWindowBackend::setVSyncEnabled(bool enabled)
        {
            window.setVerticalSyncEnabled(enabled);
        }

        void SFMLWindowBackend::setMouseCursorVisible(bool visible)
        {
            window.setMouseCursorVisible(visible);
        }

        void SFMLWindowBackend::setFramerateLimit(uint32_t limit)
        {
            window.setFramerateLimit(limit);
        }

        bool SFMLWindowBackend::setRenderingActive(bool active) const
        {
            return window.setActive(active);
        }

        void SFMLWindowBackend::swapBuffers()
        {
            window.display();
        }
		
		void SFMLWindowBackend::lockCursor(bool lock)
		{
		
			//#ifdef __WIN32__
			//HWND hwnd = (HWND)window.getSystemHandle();

			//if (lock) {
			//	RECT rect;
			//	GetClientRect(hwnd, &rect);
			//	ClientToScreen(hwnd, (LPPOINT) & rect);
			//	ClientToScreen(hwnd, (LPPOINT) & rect + 1);
			//	ClipCursor(&rect);
			//} else {
			//	ClipCursor(NULL);
			//}
			//#endif
		}
		
		//For X11
		
		   // SDL_WindowData *data = (SDL_WindowData *) window->driverdata;
			// Display *display = data->videodata->display;
			// SDL_bool oldstyle_fullscreen;
			// SDL_bool grab_keyboard;
			// const char *hint;

			// /* ICCCM2.0-compliant window managers can handle fullscreen windows
			   // If we're using XVidMode to change resolution we need to confine
			   // the cursor so we don't pan around the virtual desktop.
			 // */
			// oldstyle_fullscreen = X11_IsWindowLegacyFullscreen(_this, window);

			// if (oldstyle_fullscreen || grabbed) {
				// /* Try to grab the mouse */
				// for (;;) {
					// int result =
						// XGrabPointer(display, data->xwindow, True, 0, GrabModeAsync,
									 // GrabModeAsync, data->xwindow, None, CurrentTime);
					// if (result == GrabSuccess) {
						// break;
					// }
					// SDL_Delay(50);
				// }

				// /* Raise the window if we grab the mouse */
				// XRaiseWindow(display, data->xwindow);

				// /* Now grab the keyboard */
				// hint = SDL_GetHint(SDL_HINT_GRAB_KEYBOARD);
				// if (hint && SDL_atoi(hint)) {
					// grab_keyboard = SDL_TRUE;
				// } else {
					// /* We need to do this with the old style override_redirect
					   // fullscreen window otherwise we won't get keyboard focus.
					// */
					// grab_keyboard = oldstyle_fullscreen;
				// }
				// if (grab_keyboard) {
					// XGrabKeyboard(display, data->xwindow, True, GrabModeAsync,
								  // GrabModeAsync, CurrentTime);
				// }
			// } else {
				// XUngrabPointer(display, CurrentTime);
				// XUngrabKeyboard(display, CurrentTime);
			// }
			// XSync(display, False);
		
    }
}
