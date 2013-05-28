#include <framework/window/windowbackend.h>
#include <framework/internal/vec2.h>
#include <SFML/Window.hpp>

namespace windbreeze
{
    class SFMLWindowBackend : public WindowBackend
    {
        public:
            SFMLWindowBackend(sf::Window& w) : window(w) {}
            
            void create(VideoMode mode, const std::string& title, uint32_t style=Style::Default, const ContextSettings& settings=ContextSettings()) override;
            void close() override;
            bool isOpen() const override;
            const ContextSettings getSettings() const override;
            IntVec2 getPosition() const override;
            void setPosition(const IntVec2& position) override;
            IntVec2 getSize() const override;
            void setSize(const IntVec2& size) override;
            void setTitle(const std::string& title) override;
            void setIcon(uint32_t width, uint32_t height, const uint8_t* pixels) override;
            void setVisible(bool visible) override;
            void setVSyncEnabled(bool enabled) override;
            void setMouseCursorVisible(bool visible) override;
            void setFramerateLimit(uint32_t limit) override;

            bool setRenderingActive(bool active=true) const override;
            void display() override;

        private:
            sf::Window& window;
    };
}
