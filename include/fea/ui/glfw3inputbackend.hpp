#pragma once
#include <fea/config.hpp>
#define NO_SDL_GLEXT
#include <fea/ui/inputbackend.hpp>

namespace fea
{
    class FEA_API GLFW3InputBackend : public InputBackend
    {
        public:
            GLFW3InputBackend();

            std::queue<Event> fetchEvents() override;

            bool isKeyPressed(Keyboard::Code code) override;

            bool isMouseButtonPressed(Mouse::Button b) override;
            Vec2I getMouseGlobalPosition() override; //not supported
            Vec2I getMouseWindowPosition() override;
            void setMouseGlobalPosition(int32_t x, int32_t y) override; //not supported
            void setMouseWindowPosition(int32_t x, int32_t y) override; //not supported

            bool isGamepadConnected(uint32_t id) override; //not supported
            uint32_t getGamepadButtonCount(uint32_t id) override; //not supported
            bool isGamepadButtonPressed(uint32_t id, uint32_t button) override; //not supported
            bool gamepadHasAxis(uint32_t id, Gamepad::Axis axis) override; //not supported
            float getGamepadAxisPosition(uint32_t id, Gamepad::Axis axis) override; //not supported

            void setGamepadThreshold(float threshold) override; //not supported
            void setKeyRepeatEnabled(bool enabled) override; //not supported
        private:
            bool mKeyRepeat;
    };
}
