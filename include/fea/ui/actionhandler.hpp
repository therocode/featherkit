#pragma once
#include <fea/config.hpp>
#include <map>
#include <string>
#include <queue>
#include <fea/ui/actiontrigger.hpp>
#include <fea/ui/inputhandler.hpp>


namespace fea
{
    class InputHandler;


    template<class Action>
    class FEA_API ActionHandler
    {
        public:
            void feedEvent(const Event& event);
            bool pollAction(Action& action);
            void bindKeyPress(Keyboard::Code code, const Action& action, bool secondary = false);
            void bindKeyRelease(Keyboard::Code code, const Action& action, bool secondary = false);
            void bindMousePress(Mouse::Button button, const Action& action, bool secondary = false);
            void bindMouseRelease(Mouse::Button button, const Action& action, bool secondary = false);
            void bindGamepadPress(uint32_t id, uint32_t button, const Action& action, bool secondary = false);
            void bindGamepadRelease(uint32_t id, uint32_t button, const Action& action, bool secondary = false);
            const std::map<ActionTrigger, Action>& getPrimaryBindings();
            const std::map<ActionTrigger, Action>& getSecondaryBindings();
            void setPrimaryBindings(const std::map<ActionTrigger, Action>& bindings);
            void setSecondaryBindings(const std::map<ActionTrigger, Action>& bindings);
            void removePrimaryBinding(const Action& action);
            void removeSecondaryBinding(const Action& action);
            void clearBindings();
            void clearActions();
        private:
            std::map<ActionTrigger, Action> mPrimaryBindings;
            std::map<ActionTrigger, Action> mSecondaryBindings;
            std::queue<Action> mActions;
    };
#include <fea/ui/actionhandler.inl>
    /** @addtogroup UserInterface
     *@{
     *  @class ActionHandler
     *@}
     ***
     *  @class ActionHandler
     *  @brief Provides a way to bind raw input to actions. 
     *
     *  When an input which is bound to an action is received, the corresponding action is generated. Actions are not defined in any way and could be anything from a player jump action, to a quit the game action. For example, the keyboard key Keyboard::SPACE could be bound to the action BITE which would make the player bite in front of him. The data type of the actions is configurable using the template argument.
     *
     *  The ActionHandler lets you poll actions in a way similar to how the InputHandler lets you poll input events. These actions can the be used to control the game. By using actions instead of raw input in the game, key configurations and platform portability is a lot easier to setup since only the bindings need to be changed. Generated actions are stored until they are polled or until the action handler is cleared using the ActionHandler::clearActions() function.
     *
     *  The event types that can be bound are EventType::KEYPRESSED, EventType::KEYRELEASED, EventType::MOUSEBUTTONPRESSED, EventType::MOUSEBUTTONRELEASED, EventType::GAMEPADBUTTONPRESSED and EventType::GAMEPADBUTTONRELEASED.
     *
     *  Both primary and secondary bindings can be bound to an action. Both the primary and secondary input event will trigger the action. For instance, if you bind BITE primarily to Keyboard::SPACE and secondarily to Keyboard::G, pressing either space or g will generate the action.
     *
     *  If a binding is created for an input or action so that it would conflict an already existing binding, the old binding will be overwritten and not valid anymore.
     *  @tparam Type which is used as the action type.
     ***
     *  @fn void ActionHandler::feedEvent(const Event& event)
     *  @brief Feed an event to the ActionHandler
     *
     *  If the ActionHandler currently has bindings related to the event given, appropriate actions will be generated and stored. 
     *  All events has to be fed to the ActionHandler using this function, or there will be no actions to poll.
     *
     *  @param event Event to feed.
     ***
     *  @fn bool ActionHandler::pollAction(Action& action)
     *  @brief Access the frontmost action in the action queue, removing it from the ActionHandler in the process.
     *  @param action Action instance in which to store the frontmost action.
     *  @return True if an action was given, or false if the action queue was empty. If this is false, then the value of the action given as an argument will be undefined.
     ***
     *  @fn void ActionHandler::bindKeyPress(Keyboard::Code code, const Action& action, bool secondary = false)
     *  @brief Bind an EventType::KEYPRESSED to the specified action.
     *  @param code The key to bind the action to.
     *  @param action The action to bind.
     *  @param secondary Set to true if it should be a secondary binding. Default is false.
     ***
     *  @fn void ActionHandler::bindKeyRelease(Keyboard::Code code, const Action& action, bool secondary = false)
     *  @brief Bind an EventType::KEYRELEASED to the specified action.
     *  @param code The key to bind the action to.
     *  @param action The action to bind.
     *  @param secondary Set to true if it should be a secondary binding. Default is false.
     ***
     *  @fn void ActionHandler::bindMousePress(Mouse::Button button, const Action& action, bool secondary = false)
     *  @brief Bind an EventType::MOUSEBUTTONPRESSED to the specified action.
     *  @param button The mouse button to bind the action to.
     *  @param action The action to bind.
     *  @param secondary Set to true if it should be a secondary binding. Default is false.
     ***
     *  @fn void ActionHandler::bindMouseRelease(Mouse::Button button, const Action& action, bool secondary = false)
     *  @brief Bind an EventType::MOUSEBUTTONRELEASED to the specified action.
     *  @param button The mouse button to bind the action to.
     *  @param action The action to bind.
     *  @param secondary Set to true if it should be a secondary binding. Default is false.
     ***
     *  @fn void ActionHandler::bindGamepadPress(uint32_t id, uint32_t button, const Action& action, bool secondary = false)
     *  @brief Bind an EventType::GAMEPADBUTTONPRESSED to the specified action.
     *  @param id The gamepad ID.
     *  @param button The gamepad button to bind the action to.
     *  @param action The action to bind.
     *  @param secondary Set to true if it should be a secondary binding. Default is false.
     ***
     *  @fn void ActionHandler::bindGamepadRelease(uint32_t id, uint32_t button, const Action& action, bool secondary = false)
     *  @brief Bind an EventType::GAMEPADBUTTONRELEASED to the specified action.
     *  @param id The gamepad ID.
     *  @param button The gamepad button to bind the action to.
     *  @param action The action to bind.
     *  @param secondary Set to true if it should be a secondary binding. Default is false.
     ***
     *  @fn const std::map<ActionTrigger, Action>& ActionHandler::getPrimaryBindings()
     *  @brief Access the internal map representing the current primary bindings. Useful for displaying or storing bindings.
     *  @return Map of bindings.
     ***
     *  @fn const std::map<ActionTrigger, Action>& ActionHandler::getSecondaryBindings()
     *  @brief Access the internal map representing the current secondary bindings. Useful for displaying or storing bindings.
     *  @return Map of bindings.
     ***
     *  @fn void ActionHandler::setPrimaryBindings(const std::map<ActionTrigger, Action>& bindings)
     *  @brief Set a whole set of primary bindings. This will erase any already existing bindings. Useful for setting stored configurations.
     *  @param bindings Map of bindings to set.
     ***
     *  @fn void ActionHandler::setSecondaryBindings(const std::map<ActionTrigger, Action>& bindings)
     *  @brief Set a whole set of secondary bindings. This will erase any already existing bindings. Useful for setting stored configurations.
     *  @param bindings Map of bindings to set.
     ***
     *  @fn void ActionHandler::removePrimaryBinding(const Action& action)
     *  @brief Unbind any primary binding bound to a certain action.
     *  @param action Action to remove binding of.
     ***
     *  @fn void ActionHandler::removeSecondaryBinding(const Action& action)
     *  @brief Unbind any secondary binding bound to a certain action.
     *  @param action Action to remove binding of.
     ***
     *  @fn void ActionHandler::clearBindings()
     *  @brief Clear all current bindings for all actions.
     ***
     *  @fn void ActionHandler::clearActions()
     *  @brief Clear all generated actions.
     **/
}
