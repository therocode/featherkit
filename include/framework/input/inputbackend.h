#include <framework/input/event.h>
#include <framework/internal/intvec2.h>
#include <queue>

namespace windbreeze
{
    class InputBackend
    {
        public:
            virtual std::queue<Event> fetchEvents() = 0;

            virtual bool isKeyPressed(Keyboard::Code code) = 0;

            virtual bool isMouseButtonPressed(Mouse::Button b) = 0;
            virtual IntVec2 getMouseGlobalPosition() = 0;
            virtual IntVec2 getMouseWindowPosition() = 0;
            virtual void setMouseGlobalPosition(int32_t x, int32_t y) = 0;
            virtual void setMouseWindowPosition(int32_t x, int32_t y) = 0;

            virtual bool isGamepadConnected(uint32_t id) = 0;
            virtual uint32_t getGamepadButtonCount(uint32_t id) = 0;
            virtual bool isGamepadButtonPressed(uint32_t id, uint32_t button) = 0;
            virtual bool gamepadHasAxis(uint32_t id, Gamepad::Axis axis) = 0;
            virtual float getGamepadAxisPosition(uint32_t id, Gamepad::Axis axis) = 0;

            virtual void setGamepadThreshold(float threshold) = 0;
            virtual void setKeyRepeatEnabled(bool enabled) = 0;
    };
}
