#include "sfmlwindowbackend.h"

namespace windbreeze
{
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
        const windbreeze::ContextSettings toReturn(settings.depthBits, settings.stencilBits, settings.antialiasingLevel, settings.majorVersion, settings.minorVersion);
        return toReturn;
    }

    IntVec2 SFMLWindowBackend::getPosition() const
    {
        sf::Vector2i position = window.getPosition();
        IntVec2 toReturn({position.x, position.y});
        return toReturn;
    }

    void SFMLWindowBackend::setPosition(const IntVec2& position)
    {
        window.setPosition({position.x, position.y});
    }

    IntVec2 SFMLWindowBackend::getSize() const
    {
        sf::Vector2u position = window.getSize();
        IntVec2 toReturn({(int32_t)position.x, (int32_t)position.y});
        return toReturn;
    }

    void SFMLWindowBackend::setSize(const IntVec2& size)
    {
        window.setSize({(uint32_t)size.x, (uint32_t)size.y});
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

    void SFMLWindowBackend::display()
    {
        window.display();
    }
}
