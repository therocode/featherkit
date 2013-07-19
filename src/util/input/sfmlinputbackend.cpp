#include <framework/util/input/sfmlinputbackend.h>

namespace windbreeze
{
    SFMLInputBackend::SFMLInputBackend(sf::Window& w) : window(w)
    {
    }

    std::queue<Event> SFMLInputBackend::fetchEvents()
    {
        sf::Event event;
        std::queue<Event> result;

        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                result.push(closed());
            else if(event.type == sf::Event::Resized)
                result.push(resized(event));
            else if(event.type == sf::Event::LostFocus)
                result.push(lostFocus());
            else if(event.type == sf::Event::GainedFocus)
                result.push(gainedFocus());
            else if(event.type == sf::Event::TextEntered)
                result.push(textEntered(event));
            else if(event.type == sf::Event::KeyPressed)
                result.push(keyPressed(event));
            else if(event.type == sf::Event::KeyReleased)
                result.push(keyReleased(event));
            else if(event.type == sf::Event::MouseWheelMoved)
                result.push(mouseWheelMoved(event));
            else if(event.type == sf::Event::MouseButtonPressed)
                result.push(mouseButtonPressed(event));
            else if(event.type == sf::Event::MouseButtonReleased)
                result.push(mouseButtonReleased(event));
            else if(event.type == sf::Event::MouseMoved)
                result.push(mouseMoved(event));
            else if(event.type == sf::Event::MouseEntered)
                result.push(mouseEntered());
            else if(event.type == sf::Event::MouseLeft)
                result.push(mouseLeft());
            else if(event.type == sf::Event::JoystickButtonPressed)
                result.push(gamepadButtonPressed(event));
            else if(event.type == sf::Event::JoystickButtonReleased)
                result.push(gamepadButtonReleased(event));
            else if(event.type == sf::Event::JoystickMoved)
                result.push(gamepadMoved(event));
            else if(event.type == sf::Event::JoystickConnected)
                result.push(gamepadConnected(event));
            else if(event.type == sf::Event::JoystickDisconnected)
                result.push(gamepadDisconnected(event));
        }

        return result;
    }
    
    bool SFMLInputBackend::isKeyPressed(Keyboard::Code code)
    {
        return sf::Keyboard::isKeyPressed((sf::Keyboard::Key) code);
    }
    
    bool SFMLInputBackend::isMouseButtonPressed(Mouse::Button b)
    {
        return sf::Mouse::isButtonPressed((sf::Mouse::Button) b);
    }
    
    glm::ivec2 SFMLInputBackend::getMouseGlobalPosition()
    {
        sf::Vector2i pos = sf::Mouse::getPosition();
        return glm::ivec2(pos.x, pos.y);
    }
    
    glm::ivec2 SFMLInputBackend::getMouseWindowPosition()
    {
        sf::Vector2i pos = sf::Mouse::getPosition(window);
        return glm::ivec2(pos.x, pos.y);
    }
    
    void SFMLInputBackend::setMouseGlobalPosition(int32_t x, int32_t y)
    {
        sf::Mouse::setPosition({x, y});
    }

    void SFMLInputBackend::setMouseWindowPosition(int32_t x, int32_t y)
    {
        sf::Mouse::setPosition({x, y}, window);
    }

    bool SFMLInputBackend::isGamepadConnected(uint32_t id)
    {
        return sf::Joystick::isConnected(id);
    }

    uint32_t SFMLInputBackend::getGamepadButtonCount(uint32_t id)
    {
        return sf::Joystick::getButtonCount(id);
    }

    bool SFMLInputBackend::isGamepadButtonPressed(uint32_t id, uint32_t button)
    {
        return sf::Joystick::isButtonPressed(id, button);
    }

    bool SFMLInputBackend::gamepadHasAxis(uint32_t id, Gamepad::Axis axis)
    {
        return sf::Joystick::hasAxis(id, (sf::Joystick::Axis) axis);
    }

    float SFMLInputBackend::getGamepadAxisPosition(uint32_t id, Gamepad::Axis axis)
    {
        return sf::Joystick::getAxisPosition(id, (sf::Joystick::Axis) axis);
    }

    Event SFMLInputBackend::closed()
    {
        Event result;

        result.type = Event::CLOSED;

        return result;
    }
    
    Event SFMLInputBackend::resized(sf::Event& event)
    {
        Event result;

        result.type = Event::RESIZED;
        result.size.width = event.size.width;
        result.size.height = event.size.height;

        return result;
    }
    
    Event SFMLInputBackend::lostFocus()
    {
        Event result;

        result.type = Event::LOSTFOCUS;

        return result;
    }

    Event SFMLInputBackend::gainedFocus()
    {
        Event result;

        result.type = Event::GAINEDFOCUS;

        return result;
    }
    
    Event SFMLInputBackend::textEntered(sf::Event& event)
    {
        Event result;

        result.type = Event::TEXTENTERED;
        result.text.unicode = event.text.unicode;

        return result;
    }

    Event SFMLInputBackend::keyPressed(sf::Event& event)
    {
        Event result;

        result.type = Event::KEYPRESSED;
        result.key.code = (Keyboard::Code) event.key.code;
        result.key.alt = event.key.alt;
        result.key.control = event.key.control;
        result.key.shift = event.key.shift;
        result.key.system = event.key.system;

        return result;
    }
    
    Event SFMLInputBackend::keyReleased(sf::Event& event)
    {
        Event result;

        result.type = Event::KEYRELEASED;
        result.key.code = (Keyboard::Code) event.key.code;
        result.key.alt = event.key.alt;
        result.key.control = event.key.control;
        result.key.shift = event.key.shift;
        result.key.system = event.key.system;

        return result;
    }
    
    Event SFMLInputBackend::mouseWheelMoved(sf::Event& event)
    {
        Event result;

        result.type = Event::MOUSEWHEELMOVED;
        result.mouseWheel.delta = event.mouseWheel.delta;
        result.mouseWheel.x = event.mouseWheel.x;
        result.mouseWheel.y = event.mouseWheel.y;

        return result;
    }

    Event SFMLInputBackend::mouseButtonPressed(sf::Event& event)
    {
        Event result;

        result.type = Event::MOUSEBUTTONPRESSED;
        result.mouseButton.button = (Mouse::Button) event.mouseButton.button;
        result.mouseButton.x = event.mouseButton.x;
        result.mouseButton.y = event.mouseButton.y;

        return result;
    }

    Event SFMLInputBackend::mouseButtonReleased(sf::Event& event)
    {
        Event result;

        result.type = Event::MOUSEBUTTONRELEASED;
        result.mouseButton.button = (Mouse::Button) event.mouseButton.button;
        result.mouseButton.x = event.mouseButton.x;
        result.mouseButton.y = event.mouseButton.y;

        return result;
    }
    
    Event SFMLInputBackend::mouseMoved(sf::Event& event)
    {
        Event result;

        result.type = Event::MOUSEMOVED;
        result.mouseMove.x = event.mouseMove.x;
        result.mouseMove.y = event.mouseMove.y;

        return result;
    }
    
    Event SFMLInputBackend::mouseEntered()
    {
        Event result;
        result.type = Event::MOUSEENTERED;
        return result;
    }

    Event SFMLInputBackend::mouseLeft()
    {
        Event result;
        result.type = Event::MOUSELEFT;
        return result;
    }
    
    Event SFMLInputBackend::gamepadButtonPressed(sf::Event& event)
    {
        Event result;
        result.type = Event::GAMEPADBUTTONPRESSED;
        result.gamepadButton.gamepadId = event.joystickButton.joystickId;
        result.gamepadButton.button = event.joystickButton.button;
        return result;
    }

    Event SFMLInputBackend::gamepadButtonReleased(sf::Event& event)
    {
        Event result;
        result.type = Event::GAMEPADBUTTONRELEASED;
        result.gamepadButton.gamepadId = event.joystickButton.joystickId;
        result.gamepadButton.button = event.joystickButton.button;
        return result;
    }
    
    Event SFMLInputBackend::gamepadMoved(sf::Event& event)
    {
        Event result;
        result.type = Event::GAMEPADMOVED;
        result.gamepadMove.axis = (Gamepad::Axis) event.joystickMove.axis; 
        result.gamepadMove.gamepadId = (Gamepad::Axis) event.joystickMove.joystickId;
        result.gamepadMove.position = event.joystickMove.position;
        return result;
    }
    
    Event SFMLInputBackend::gamepadConnected(sf::Event& event)
    {
        Event result;
        result.type = Event::GAMEPADCONNECTED;
        result.gamepadConnect.gamepadId = event.joystickConnect.joystickId;
        return result;
    }
    
    Event SFMLInputBackend::gamepadDisconnected(sf::Event& event)
    {
        Event result;
        result.type = Event::GAMEPADDISCONNECTED;
        result.gamepadConnect.gamepadId = event.joystickConnect.joystickId;
        return result;
    }

    void SFMLInputBackend::setGamepadThreshold(float threshold)
    {
        window.setJoystickThreshold(threshold);
    }

    void SFMLInputBackend::setKeyRepeatEnabled(bool enabled)
    {
        window.setKeyRepeatEnabled(enabled);
    }
}
