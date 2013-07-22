#include <featherkit/util/window/sfml/sfmlwindowbackend.h>

namespace fku
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
        const fk::ContextSettings toReturn(settings.depthBits, settings.stencilBits, settings.antialiasingLevel, settings.majorVersion, settings.minorVersion);
        return toReturn;
    }

    glm::ivec2 SFMLWindowBackend::getPosition() const
    {
        sf::Vector2i position = window.getPosition();
        return glm::ivec2(position.x, position.y);
    }

    void SFMLWindowBackend::setPosition(const glm::ivec2& position)
    {
        window.setPosition({position.x, position.y});
    }

    glm::ivec2 SFMLWindowBackend::getSize() const
    {
        sf::Vector2u position = window.getSize();
        glm::ivec2 toReturn(glm::ivec2((int32_t)position.x, (int32_t)position.y));
        return toReturn;
    }

    void SFMLWindowBackend::setSize(const glm::ivec2& size)
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
