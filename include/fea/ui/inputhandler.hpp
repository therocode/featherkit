#pragma once
#include <fea/config.hpp>
#include <queue>
#include <memory>
#include <fea/ui/event.hpp>
#include <fea/ui/vec2i.hpp>

namespace fea
{
    class InputBackend;

    class FEA_API InputHandler
    {
        public:
            InputHandler(InputBackend* backend);
            bool pollEvent(Event& event);
            const std::queue<Event>& getEventQueue() const;

            bool isKeyPressed(Keyboard::Code code) const;

            bool isMouseButtonPressed(Mouse::Button button) const;
            Vec2I getMouseGlobalPosition() const;
            Vec2I getMouseWindowPosition() const;
            void setMouseGlobalPosition(int32_t x, int32_t y);
            void setMouseWindowPosition(int32_t x, int32_t y);

            bool isGamepadConnected(uint32_t id) const;
            uint32_t getGamepadButtonCount(uint32_t id) const;
            bool isGamepadButtonPressed(uint32_t id, uint32_t button) const;
            bool gamepadHasAxis(uint32_t id, Gamepad::Axis axis) const;
            float getGamepadAxisPosition(uint32_t id, Gamepad::Axis axis) const;

            void setGamepadThreshold(float threshold);
            void setKeyRepeatEnabled(bool enabled);
        private:
            void processEvents();
            std::unique_ptr<InputBackend> mInputBackend;
            std::queue<Event> mEventQueue;
    };

    /** @addtogroup UI
     *@{
     *  @class InputHandler
     *@}
     ***
     *  @class InputHandler
     *  @brief Provides access to input events and settings, as well as the current state of the input devices.
     *
     *  Just about any game needs to access the input devices a lot to let the player control the game. This is what this class is for. The types of devices supported are keyboard, mouse and gamepad. This class relies on a system specific backend that must be given upon construction. The backend is stored internally as an std::unique_ptr. 
     ***
     *  @fn InputHandler::InputHandler(InputBackend* backend) 
     *  @brief Construct an InputHandler that will rely on the given backend.
     *  @param backend InputBackend given. The memory will be managed by the InputHandler.
     ***
     *  @fn bool InputHandler::pollEvent(Event& event)
     *  @brief Access the frontmost event in the event queue, removing it from the InputHandler in the process.
     *  @param event Event instance in which to store the frontmost event.
     *  @return True if an event was given, or false if the event queue was empty. If this is false, then the value of the event given as an argument will be undefined.
     ***
     *  @fn const std::queue<Event>& InputHandler::getEventQueue() const
     *  @brief Access the event queue.
     *  @return Const reference to the internal event queue.
     ***
     *  @fn bool InputHandler::isKeyPressed(Keyboard::Code code) const
     *  @brief Check if a key on the keyboard is pressed or not.
     *  @param code The key to check.
     *  @return True if the key is currently pushed down.
     ***
     *  @fn bool InputHandler::isMouseButtonPressed(Mouse::Button button) const
     *  @brief Check if a button on the mouse is pressed or not.
     *  @param button The button to check.
     *  @return True if the button is currently pushed down.
     ***
     *  @fn Vec2I InputHandler::getMouseGlobalPosition() const
     *  @brief Access the current mouse position relative to the whole screen.
     *  @return Coordinates as a vector.
     ***
     *  @fn Vec2I InputHandler::getMouseWindowPosition() const
     *  @brief Access the current mouse position relative to the window.
     *  @return Coordinates as a vector.
     ***
     *  @fn void InputHandler::setMouseGlobalPosition(int32_t x, int32_t y)
     *  @brief Set the mouse position relative to the whole screen.
     *  @param x X coordinate.
     *  @param y Y coordinate.
     ***
     *  @fn void InputHandler::setMouseWindowPosition(int32_t x, int32_t y)
     *  @brief Set the mouse position relative to the window.
     *  @param x X coordinate.
     *  @param y Y coordinate.
     ***
     *  @fn bool InputHandler::isGamepadConnected(uint32_t id) const
     *  @brief Check if a gamepad is connected.
     *  @param id Gamepad to check.
     *  @return True if connected.
     ***
     *  @fn uint32_t InputHandler::getGamepadButtonCount(uint32_t id) const
     *  @brief Get the amount of buttons available on a specific gamepad.
     *  @param id Gamepad to check.
     *  @return Amount of buttons.
     ***
     *  @fn bool InputHandler::isGamepadButtonPressed(uint32_t id, uint32_t button) const
     *  @brief Check if a button on a specific gamepad is being pressed down.
     *  @param id Gamepad to check.
     *  @param button Button to check.
     *  @return True if the button is currently pressed down.
     ***
     *  @fn bool InputHandler::gamepadHasAxis(uint32_t id, Gamepad::Axis axis) const
     *  @brief Check if a gamepad has a specific axis.
     *  @param id Gamepad to check.
     *  @param axis Axis to look for.
     *  @return True if the axis exists.
     ***
     *  @fn float InputHandler::getGamepadAxisPosition(uint32_t id, Gamepad::Axis axis) const
     *  @brief Access the current position of an axis on a specific gamepad.
     *  @param id Gamepad to check.
     *  @param axis Axis of which to get the position.
     *  @return Position of the axis.
     ***
     *  @fn void InputHandler::setGamepadThreshold(float threshold)
     *  @brief Set the threshold level for when Event::GAMEPADMOVED events are fired.
     *  @param threshold Threshold level.
     ***
     *  @fn void InputHandler::setKeyRepeatEnabled(bool enabled)
     *  @brief Set Event::KEYPRESSED events to only fire once instead of continuously if a key is being pressed down.
     *  @param enabled True for on, false for off.
     ***/
}

