#include <featherkit/util/window/sfmlwindowbackend.h>
namespace fea
{
    namespace util
    {
        SFMLWindowBackend::SFMLWindowBackend(sf::Window& window) : mWindow(window)
        {
        }

        void SFMLWindowBackend::create(VideoMode mode, const std::string& title, uint32_t style, const ContextSettings& settings)
        {
            sf::VideoMode vidMode(mode.mWidth, mode.mHeight, mode.mBitDepth);
            sf::ContextSettings conSettings(settings.mDepthBits, settings.mStencilBits, settings.mAntialiasingLevel, settings.mMajorVersion, settings.mMinorVersion);
            mWindow.create(vidMode, title, style, conSettings);
        }

        void SFMLWindowBackend::close()
        {
            mWindow.close();
        }

        bool SFMLWindowBackend::isOpen() const
        {
            return mWindow.isOpen();
        }

        const ContextSettings SFMLWindowBackend::getSettings() const
        {
            const sf::ContextSettings& settings = mWindow.getSettings();
            const fea::ContextSettings toReturn(settings.depthBits, settings.stencilBits, settings.antialiasingLevel, settings.majorVersion, settings.minorVersion);
            return toReturn;
        }

        Vec2I SFMLWindowBackend::getPosition() const
        {
            sf::Vector2i position = mWindow.getPosition();
            return {position.x, position.y};
        }

        void SFMLWindowBackend::setPosition(int32_t x, int32_t y)
        {
            mWindow.setPosition({x, y});
        }

        Vec2I SFMLWindowBackend::getSize() const
        {
            sf::Vector2u position = mWindow.getSize();
            return {(int32_t)position.x, (int32_t)position.y};
        }

        void SFMLWindowBackend::setSize(int32_t w, int32_t h)
        {
            mWindow.setSize({(uint32_t)w, (uint32_t)h});
        }

        void SFMLWindowBackend::setTitle(const std::string& title)
        {
            mWindow.setTitle({title});
        }

        void SFMLWindowBackend::setIcon(uint32_t width, uint32_t height, const uint8_t* pixels)
        {
            mWindow.setIcon(width, height, pixels);
        }

        void SFMLWindowBackend::setVisible(bool visible)
        {
            mWindow.setVisible(visible);
        }

        void SFMLWindowBackend::setVSyncEnabled(bool enabled)
        {
            mWindow.setVerticalSyncEnabled(enabled);
        }

        void SFMLWindowBackend::setMouseCursorVisible(bool visible)
        {
            mWindow.setMouseCursorVisible(visible);
        }

        void SFMLWindowBackend::setFramerateLimit(uint32_t limit)
        {
            mWindow.setFramerateLimit(limit);
        }

        bool SFMLWindowBackend::setRenderingActive(bool active) const
        {
            return mWindow.setActive(active);
        }

        void SFMLWindowBackend::swapBuffers()
        {
            mWindow.display();
        }
		
		void SFMLWindowBackend::lockCursor(bool lock)
		{
		
			//#ifdef __WIN32__
			//HWND hwnd = (HWND)mWindow.getSystemHandle();

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
