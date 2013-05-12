#pragma once
#include <queue>
#include "event.h"
#include "intvec2.h"

namespace windbreeze
{
    class InputBackend;

    class InputHandler
    {
        public:
            InputHandler(InputBackend& backend) : inputBackend(backend){}
            void processEvents(bool keepLast = false);
            bool pollEvent(Event& event);
            const std::queue<Event>& getEventQueue() const;

            bool isKeyPressed(Keyboard::Code code);

            bool isMouseButtonPressed(Mouse::Button b);
            IntVec2 getMouseGlobalPosition();
            IntVec2 getMouseWindowPosition();
            void setMouseGlobalPosition(int32_t x, int32_t y);
            void setMouseWindowPosition(int32_t x, int32_t y);

            bool isGamepadConnected(uint32_t id);
            uint32_t getGamepadButtonCount(uint32_t id);
            bool isGamepadButtonPressed(uint32_t id, uint32_t button);
            bool gamepadHasAxis(uint32_t id, Gamepad::Axis axis);
            float getGamepadAxisPosition(uint32_t id, Gamepad::Axis axis);

            void setGamepadThreshold(float threshold);
            void setKeyRepeatEnabled(bool enabled);
        private:
            InputBackend& inputBackend;
            std::queue<Event> eventQueue;
    };
/** @class InputHandler
 *  Provides an access to input events, as well as the current state of devices.
 *  
 *
 */

/** @fn InputHandler::InputHandler(InputBackend& backend) 
 *  Constructor that does stuff!
 *
 *
 */

/** @fn void InputHandler::processEvents(bool keepLast = false)
 *  Grabs the events from the backend
 */
}

