#include <featherkit/util/window/sfml/sfmlwindowbackend.h>
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
		
    }
}
