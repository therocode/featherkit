#include <fea/ui/inputbackend.hpp>
#include <fea/ui/inputhandler.hpp>

namespace fea
{
    InputHandler::InputHandler(InputBackend* backend) : mInputBackend(backend)
    {
    }
    
    bool InputHandler::pollEvent(Event& event)
    {
        processEvents();
        if(mEventQueue.size() > 0)
        {
            event = mEventQueue.front();
            mEventQueue.pop();
            return true;
        }
        else 
        {
            return false;
        }
    }
    
    const std::queue<Event>& InputHandler::getEventQueue() const
    {
        return mEventQueue;
    }
    
    bool InputHandler::isKeyPressed(Keyboard::Code code) const
    {
        return mInputBackend->isKeyPressed(code);
    }
    
    bool InputHandler::isMouseButtonPressed(Mouse::Button b) const
    {
        return mInputBackend->isMouseButtonPressed(b);
    }
    
    Vec2I InputHandler::getMouseGlobalPosition() const
    {
        return mInputBackend->getMouseGlobalPosition();
    }

    Vec2I InputHandler::getMouseWindowPosition() const
    {
        return mInputBackend->getMouseWindowPosition();
    }
    
    void InputHandler::setMouseGlobalPosition(int32_t x, int32_t y)
    {
        mInputBackend->setMouseGlobalPosition(x, y);
    }
    
    void InputHandler::setMouseWindowPosition(int32_t x, int32_t y)
    {
        mInputBackend->setMouseWindowPosition(x, y);
    }

    bool InputHandler::isGamepadConnected(uint32_t id) const
    {
        return mInputBackend->isGamepadConnected(id);
    }

    uint32_t InputHandler::getGamepadButtonCount(uint32_t id) const
    {
        return mInputBackend->getGamepadButtonCount(id);
    }

    bool InputHandler::isGamepadButtonPressed(uint32_t id, uint32_t button) const
    {
        return mInputBackend->isGamepadButtonPressed(id, button);
    }

    bool InputHandler::gamepadHasAxis(uint32_t id, Gamepad::Axis axis) const
    {
        return mInputBackend->gamepadHasAxis(id, axis);
    }

    float InputHandler::getGamepadAxisPosition(uint32_t id, Gamepad::Axis axis) const
    {
        return mInputBackend->getGamepadAxisPosition(id, axis);
    }

    void InputHandler::setGamepadThreshold(float threshold)
    {
        mInputBackend->setGamepadThreshold(threshold);
    }

    void InputHandler::setKeyRepeatEnabled(bool enabled)
    {
        mInputBackend->setKeyRepeatEnabled(enabled);
    }

    void InputHandler::processEvents()
    {
        std::queue<Event> newEvents = mInputBackend->fetchEvents();

        while(!newEvents.empty())
        {
            mEventQueue.push(newEvents.front());
            newEvents.pop();
        }
    }
}
