#include <featherkit/util/window/sdl2/sdl2windowbackend.h>

namespace fea
{
	namespace util
	{
		SDL2WindowBackend::SDL2WindowBackend() : window(nullptr)
		{
			SDL_Init(SDL_INIT_VIDEO);
		}

		void SDL2WindowBackend::create(VideoMode mode, const std::string& title, uint32_t style, const ContextSettings& settings)
		{
			//todo: fix style
			(void) style;
			(void) settings;
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
			window = SDL_CreateWindow(title.c_str(), 
					SDL_WINDOWPOS_CENTERED, 
					SDL_WINDOWPOS_CENTERED, 
					mode.width, mode.height, 
					SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
			glContext = SDL_GL_CreateContext(window);
			setVSyncEnabled(true);
		}

		void SDL2WindowBackend::close()
		{
			SDL_DestroyWindow(window);
			SDL_Quit();
			window = nullptr;
		}

		
		bool SDL2WindowBackend::isOpen() const
		{
			return window != nullptr;
		}

		const ContextSettings SDL2WindowBackend::getSettings() const
		{
			//settings not finalised;
			return ContextSettings();
		}

		Vec2I SDL2WindowBackend::getPosition() const
		{
			//not sure
			//SDL_getenv("SDL_VIDEO_WINDOW_POS");
			int x, y;
			x = 0;
			y = 0;
			if(isOpen())
				SDL_GetWindowPosition(window, &x, &y);

			Vec2I s;
			s.x = x;
			s.y = y;
			return s;
		}

		void SDL2WindowBackend::setPosition(int32_t x, int32_t y)
		{
			(void)x;
			(void)y;
			if(isOpen())
			{
				int _x = x;
				int _y = y;
				SDL_SetWindowPosition(window, _x, _y);
			}
			//not sure
			//std::stringstream ss;
			//ss << "SDL_VIDEO_WINDOW_POS=" << x << ", " << y;
			//SDL_putenv(ss.str());
		}

		Vec2I SDL2WindowBackend::getSize() const
		{
			int w, h;
			w = -1;
			h = -1;
			if(isOpen())
			{
				SDL_GetWindowSize(window, &w, &h);
			}
			Vec2I s;
			s.x = w;
			s.y = h;
			return s;
		}

		void SDL2WindowBackend::setSize(int32_t w, int32_t h)
		{
			SDL_SetWindowSize(window, w, h);
		}

		void SDL2WindowBackend::setTitle(const std::string& title)
		{
			SDL_SetWindowTitle(window, title.c_str());
		}

		void SDL2WindowBackend::setIcon(uint32_t width, uint32_t height, const uint8_t* pixels)
		{
			//should be fixed
			(void)width;
			(void)height;
			//SDL_WM_SetCaption("shouldbetitle", (char*)pixels);
		}

		void SDL2WindowBackend::setVisible(bool visible)
		{
			//should be fixed
			(void) visible;
		}

		void SDL2WindowBackend::setVSyncEnabled(bool enabled)
		{
			//should be fixed
			(void) enabled;
			if(enabled)
			{
				SDL_GL_SetSwapInterval(1);
			}else
			{
				SDL_GL_SetSwapInterval(0);
			}
		}

		void SDL2WindowBackend::setMouseCursorVisible(bool visible)
		{
			//should be fixed
			(void)visible;
		}

		void SDL2WindowBackend::setFramerateLimit(uint32_t limit)
		{
			//should be fixed
			(void)limit;
		}

		bool SDL2WindowBackend::setRenderingActive(bool active) const
		{
			//should be fixed
			(void)active;
			return true;
		}

		void SDL2WindowBackend::swapBuffers()
		{
			SDL_GL_SwapWindow(window);
		}

		void SDL2WindowBackend::lockCursor(bool lock)
		{
			if(isOpen())
			{
				SDL_SetRelativeMouseMode((SDL_bool)lock);
				SDL_SetWindowGrab(window, (SDL_bool)lock);
			}
		}

		SDL2WindowBackend::~SDL2WindowBackend()
		{
			free(window);
		}
	}
}
