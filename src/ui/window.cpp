#include <fea/ui/window.hpp>
#include <fea/ui/windowbackend.hpp>

namespace fea
{
    Window::Window(WindowBackend* windowBackend, VideoMode mode, const std::string& title, uint32_t style, const ContextSettings& settings): mWindowBackend(windowBackend)
    {
        mWindowBackend->open(mode, title, style, settings);
    }

    const ContextSettings Window::getSettings() const
    {
        return mWindowBackend->getSettings();
    }

    Vec2I Window::getPosition() const
    {
        return mWindowBackend->getPosition();
    }

    void Window::setPosition(int32_t x, int32_t y)
    {
        mWindowBackend->setPosition(x, y);
    }

    Vec2I Window::getSize() const
    {
        return mWindowBackend->getSize();
    }

    void Window::setSize(int32_t w, int32_t h)
    {
        mWindowBackend->setSize(w, h);
    }
    
    void Window::setTitle(const std::string& title)
    {
        mWindowBackend->setTitle(title);
    }

    void Window::setIcon(uint32_t width, uint32_t height, const uint8_t* pixels)
    {
        mWindowBackend->setIcon(width, height, pixels);
    }
    
    void Window::setVisible(bool visible)
    {
        mWindowBackend->setVisible(visible);
    }

    void Window::setVSyncEnabled(bool enabled)
    {
        mWindowBackend->setVSyncEnabled(enabled);
    }

    void Window::setMouseCursorVisible(bool visible)
    {
        mWindowBackend->setMouseCursorVisible(visible);
    }

    void Window::setFramerateLimit(uint32_t limit)
    {
        mWindowBackend->setFramerateLimit(limit);
    }

    bool Window::setRenderingActive(bool active) const
    {
        return mWindowBackend->setRenderingActive(active);
    }

    void Window::swapBuffers()
    {
        mWindowBackend->swapBuffers();
    }

	void Window::lockCursor(bool enabled)
	{
		mWindowBackend->lockCursor(enabled);
	}
}
