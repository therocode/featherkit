#pragma once

#include <cstdint>
#include "keyboard.h"
#include "mouse.h"
#include "gamepad.h"

namespace windbreeze
{
    class Event
    {
        public:
            struct ResizeEvent
            {
                uint32_t width;
                uint32_t height;
            };
            
            struct KeyEvent
            {
                Keyboard::Code code;
                bool alt;
                bool control;
                bool shift;
                bool system;
            };

            struct TextEvent
            {
                uint32_t unicode;
            };

            struct MouseMoveEvent
            {
                int32_t x;
                int32_t y;
            };

            struct MouseButtonEvent
            {
                Mouse::Button button;
                int32_t x;
                int32_t y;
            };

            struct MouseWheelEvent
            {
                int32_t delta;
                int32_t x;
                int32_t y;
            };

            struct GamepadConnectEvent
            {
                uint32_t gamepadId;
            };

            struct GamepadMoveEvent
            {
                uint32_t gamepadId;
                Gamepad::Axis axis;
                float position;
            };

            struct GamepadButtonEvent
            {
                uint32_t gamepadId;
                uint32_t button;
            };

            enum EventType
            {
                CLOSED,
                RESIZED,
                LOSTFOCUS,
                GAINEDFOCUS,
                TEXTENTERED,
                KEYPRESSED,
                KEYRELEASED,
                MOUSEWHEELMOVED,
                MOUSEBUTTONPRESSED,
                MOUSEBUTTONRELEASED,
                MOUSEMOVED,
                MOUSEENTERED,
                MOUSELEFT,
                GAMEPADBUTTONPRESSED,
                GAMEPADBUTTONRELEASED,
                GAMEPADMOVED,
                GAMEPADCONNECTED,
                GAMEPADDISCONNECTED
            };
            
            EventType type;

            union
            {
                ResizeEvent size;
                KeyEvent key;
                TextEvent text;
                MouseMoveEvent mouseMove;
                MouseButtonEvent mouseButton;
                MouseWheelEvent mouseWheel;
                GamepadMoveEvent gamepadMove;
                GamepadButtonEvent gamepadButton;
                GamepadConnectEvent gamepadConnect;
            };
    };
}
