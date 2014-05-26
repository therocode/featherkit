#pragma once
#include <fea/config.hpp>
#include <fea/ui/keyboard.hpp>
#include <fea/ui/mouse.hpp>
#include <cstdint>

namespace fea
{

    class FEA_API ActionTrigger
    {
        public:
            enum ActionType {KEYPRESS, KEYRELEASE, MOUSEPRESS, MOUSERELEASE, GAMEPADPRESS, GAMEPADRELEASE};

            ActionType type;
            uint32_t gamepadId;
            union
            {
                Keyboard::Code keyCode;         ///< Numerical value representing the key needed to trigger this action.
                Mouse::Button mouseButton;      ///< Numerical value representing the mouse button needed to trigger this action.
                uint32_t gamepadButton;         ///< Numerical value representing the gamepad button needed to trigger this action.
            };

            ActionTrigger();
            bool operator>(const ActionTrigger& other) const;
            bool operator<(const ActionTrigger& other) const;
    };
    /** @addtogroup UserInterface
     *@{
     *  @class ActionTrigger
     *@}
     ***
     *  @enum ActionTrigger::ActionType
     *  @brief Defines the type of an ActionTrigger.
     ***
     *  @class ActionTrigger
     *  @brief Represents a trigger for an action.
     *
     *  In the ActionHandler, bound actions are defined with an ActionTrigger mapped to an action. The ActionTrigger holds the type of the action, and the data necessary to identify it.
     ***
     *  @fn bool ActionTrigger::operator>(const ActionTrigger& other) const
     *  @brief Compare two ActionTrigger instances.
     *  @param other ActionTrigger instance to compare to.
     *  @return True if the left side instance is greater than the right side one.
     ***
     *  @fn bool ActionTrigger::operator<(const ActionTrigger& other) const
     *  @brief Compare two ActionTrigger instances.
     *  @param other ActionTrigger instance to compare to.
     *  @return True if the left side instance is less than the right side one.
     ***
     *  @var ActionTrigger::type
     *  @brief The type of an ActionTrigger.
     ***
     *  @var ActionTrigger::gamepadId
     *  @brief The ID of the gamepad which this ActionTrigger is triggered by.
     ***/
}
