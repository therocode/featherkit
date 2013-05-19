#pragma once
#include <framework/input/keyboard.h>
#include <framework/input/mouse.h>
#include <cstdint>

namespace windbreeze
{

    class ActionTrigger
    {
        public:
        enum ActionType {KEYPRESS, KEYRELEASE, MOUSEPRESS, MOUSERELEASE, GAMEPADPRESS, GAMEPADRELEASE};

        ActionType type;
        uint32_t gamepadId = 0;
        union
        {
            Keyboard::Code keyCode;
            Mouse::Button mouseButton;
            uint32_t gamepadButton;
        };

        bool operator>(const ActionTrigger& other) const;
        bool operator<(const ActionTrigger& other) const;
    };
}
