#pragma once
#define NO_SDL_GLEXT
#include <featherkit/input/inputbackend.h>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

namespace fea
{
    namespace util
    {
        class SDL2InputBackend : public InputBackend
        {
            public:
                SDL2InputBackend();

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
                Event resized(SDL_Event& event);
                Event active(SDL_Event& event);
				Event windowFocus(bool focus);
                Event keyPressed(SDL_Event& event);
                Event keyReleased(SDL_Event& event);
                Event mouseButtonPressed(SDL_Event& event);
                Event mouseButtonReleased(SDL_Event& event);
                Event mouseMoved(SDL_Event& event);
                Event gamepadButtonPressed(SDL_Event& event);
                Event gamepadButtonReleased(SDL_Event& event);
                Event gamepadMoved(SDL_Event& event);
                Event mouseWheel(SDL_Event& event);
                Keyboard::Code sdlKeyCodeToFea(SDL_Keycode sdlCode) const;
                SDL_Keycode feaKeyCodeToSdl(Keyboard::Code feaCode) const;
                uint8_t feaMouseButtonToSdl(Mouse::Button feaMouseButton) const;
                Mouse::Button sdlMouseButtonToFea(uint32_t sdlMouseButton) const;
        };
    }
}
