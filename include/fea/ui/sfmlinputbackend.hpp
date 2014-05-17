#pragma once
#include <fea/ui/inputbackend.hpp>
#include <glm/glm.hpp>
#include <SFML/Window.hpp>

namespace fea
{
    class SFMLInputBackend : public InputBackend
    {
        public:
            SFMLInputBackend(sf::Window& window);

            std::queue<Event> fetchEvents() override;

            bool isKeyPressed(Keyboard::Code code) override;

            bool isMouseButtonPressed(Mouse::Button b) override;
            glm::ivec2 getMouseGlobalPosition() override;
            glm::ivec2 getMouseWindowPosition() override;
            void setMouseGlobalPosition(int32_t x, int32_t y) override;
            void setMouseWindowPosition(int32_t x, int32_t y) override;

            bool isGamepadConnected(uint32_t id) override;
            uint32_t getGamepadButtonCount(uint32_t id) override;
            bool isGamepadButtonPressed(uint32_t id, uint32_t button) override;
            bool gamepadHasAxis(uint32_t id, Gamepad::Axis axis) override;
            float getGamepadAxisPosition(uint32_t id, Gamepad::Axis axis) override;

            void setGamepadThreshold(float threshold) override;
            void setKeyRepeatEnabled(bool enabled) override;
        private:
            Event closed();
            Event resized(sf::Event& event);
            Event lostFocus();
            Event gainedFocus();
            Event textEntered(sf::Event& event);
            Event keyPressed(sf::Event& event);
            Event keyReleased(sf::Event& event);
            Event mouseWheelMoved(sf::Event& event);
            Event mouseButtonPressed(sf::Event& event);
            Event mouseButtonReleased(sf::Event& event);
            Event mouseMoved(sf::Event& event);
            Event mouseEntered();
            Event mouseLeft();
            Event gamepadButtonPressed(sf::Event& event);
            Event gamepadButtonReleased(sf::Event& event);
            Event gamepadMoved(sf::Event& event);
            Event gamepadConnected(sf::Event& event);
            Event gamepadDisconnected(sf::Event& event);
            sf::Window& mWindow;
    };
}
