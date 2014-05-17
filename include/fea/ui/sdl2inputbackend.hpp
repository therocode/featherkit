#pragma once
#define NO_SDL_GLEXT
#include <fea/ui/inputbackend.hpp>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

namespace fea
{
    class SDL2InputBackend : public InputBackend
    {
        public:
            SDL2InputBackend();

            std::queue<Event> fetchEvents() override;

            bool isKeyPressed(Keyboard::Code code) override;

            bool isMouseButtonPressed(Mouse::Button b) override;
            glm::ivec2 getMouseGlobalPosition() override; //not supported
            glm::ivec2 getMouseWindowPosition() override;
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
            Event closed();
            Event resized(SDL_Event& event);
            Event windowFocus(bool focus);
            Event keyPressed(SDL_Event& event); //alt/control/shift/system modifiers not supported
            Event keyReleased(SDL_Event& event); //alt/control/shift/system modifiers not supported
            Event mouseButtonPressed(SDL_Event& event);
            Event mouseButtonReleased(SDL_Event& event);
            Event mouseMoved(SDL_Event& event);
            Event gamepadButtonPressed(SDL_Event& event);  //not supported
            Event gamepadButtonReleased(SDL_Event& event); //not supported
            Event gamepadMoved(SDL_Event& event); //not supported
            Event mouseWheel(SDL_Event& event);
            Keyboard::Code sdlKeyCodeToFea(SDL_Keycode sdlCode) const;
            SDL_Keycode feaKeyCodeToSdl(Keyboard::Code feaCode) const;
            uint8_t feaMouseButtonToSdl(Mouse::Button feaMouseButton) const;
            Mouse::Button sdlMouseButtonToFea(uint32_t sdlMouseButton) const;
    };
}
