#include <featherkit/window/window.h>
#include <featherkit/window/windowbackend.h>

namespace fea
{
    Window::Window(WindowBackend* backend) : windowBackend(backend)
    {
    }

    void Window::create(VideoMode mode, const std::string& title, uint32_t style, const ContextSettings& settings)
    {
        windowBackend->create(mode, title, style, settings);
    }

    void Window::close()
    {
        windowBackend->close();
    }

    bool Window::isOpen() const
    {
        return windowBackend->isOpen();
    }

    const ContextSettings Window::getSettings() const
    {
        return windowBackend->getSettings();
    }

    Vec2I Window::getPosition() const
    {
        return windowBackend->getPosition();
    }

    void Window::setPosition(int32_t x, int32_t y)
    {
        windowBackend->setPosition(x, y);
    }

    Vec2I Window::getSize() const
    {
        return windowBackend->getSize();
    }

    void Window::setSize(int32_t w, int32_t h)
    {
        windowBackend->setSize(w, h);
    }
    
    void Window::setTitle(const std::string& title)
    {
        windowBackend->setTitle(title);
    }

    void Window::setIcon(uint32_t width, uint32_t height, const uint8_t* pixels)
    {
        windowBackend->setIcon(width, height, pixels);
    }
    
    void Window::setVisible(bool visible)
    {
        windowBackend->setVisible(visible);
    }

    void Window::setVSyncEnabled(bool enabled)
    {
        windowBackend->setVSyncEnabled(enabled);
    }

    void Window::setMouseCursorVisible(bool visible)
    {
        windowBackend->setMouseCursorVisible(visible);
    }

    void Window::setFramerateLimit(uint32_t limit)
    {
        windowBackend->setFramerateLimit(limit);
    }

    bool Window::setRenderingActive(bool active) const
    {
        return windowBackend->setRenderingActive(active);
    }

    void Window::swapBuffers()
    {
        windowBackend->swapBuffers();
    }

	void Window::lockCursor(bool lock)
	{
		windowBackend->lockCursor(lock);
	}

}
