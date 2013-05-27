#pragma once
#include <map>
#include <string>
#include <queue>
#include <framework/input/actiontrigger.h>
#include <framework/input/inputhandler.h>


namespace windbreeze
{
    class InputHandler;


    template<class Action>
    class ActionHandler
    {
        public:
            void processActions(const InputHandler& input, bool keepLast = false);
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
            std::map<ActionTrigger, Action> primaryBindings;
            std::map<ActionTrigger, Action> secondaryBindings;
            std::queue<Action> actions;
    };

    template<class Action>
    void ActionHandler<Action>::processActions(const InputHandler& input, bool keepLast)
    {
        std::queue<Action> newActions;
        std::queue<Event> events = input.getEventQueue();

        while(events.size() > 0)
        {
            Event& event = events.front();
            events.pop();
            ActionTrigger trigger;
            typename std::map<ActionTrigger, Action>::iterator binding;

            switch(event.type)
            {
                case Event::KEYPRESSED:
                    trigger.type = ActionTrigger::KEYPRESS;
                    trigger.keyCode = event.key.code;
                    break;

                case Event::KEYRELEASED:
                    trigger.type = ActionTrigger::KEYRELEASE;
                    trigger.keyCode = event.key.code;
                    break;

                case Event::MOUSEBUTTONPRESSED:
                    trigger.type = ActionTrigger::MOUSEPRESS;
                    trigger.mouseButton = event.mouseButton.button;
                    break;

                case Event::MOUSEBUTTONRELEASED:
                    trigger.type = ActionTrigger::MOUSERELEASE;
                    trigger.mouseButton = event.mouseButton.button;
                    break;

                case Event::GAMEPADBUTTONPRESSED:
                    trigger.type = ActionTrigger::GAMEPADPRESS;
                    trigger.gamepadButton = event.gamepadButton.button;
                    trigger.gamepadId = event.gamepadButton.gamepadId;
                    break;

                case Event::GAMEPADBUTTONRELEASED:
                    trigger.type = ActionTrigger::GAMEPADRELEASE;
                    trigger.gamepadButton = event.gamepadButton.button;
                    trigger.gamepadId = event.gamepadButton.gamepadId;
                    break;

                default:
                    continue;
            }
            
            
            binding = primaryBindings.find(trigger);

            if(binding != primaryBindings.end())
            {
                newActions.push(binding->second);
            }
            else
            {
                binding = secondaryBindings.find(trigger);
                if(binding != secondaryBindings.end())
                {
                    newActions.push(binding->second);
                }
            }
        }

        if(keepLast)
        {
            while(newActions.size() > 0)
            {
                actions.push(newActions.front());
                newActions.pop();
            }
        }
        else
        {
            actions = newActions;
        }
    }
    
    template<class Action>
    bool ActionHandler<Action>::pollAction(Action& action)
    {
        if(actions.size() > 0)
        {
            action = actions.front();
            actions.pop();
            return true;
        }
        else
            return false;            
    }
    
    template<class Action>
    void ActionHandler<Action>::bindKeyPress(Keyboard::Code code, const Action& action, bool secondary)
    {
        ActionTrigger trigger;
        trigger.type = ActionTrigger::KEYPRESS;
        trigger.keyCode = code;

        if(!secondary)
        {
            for(auto bound = primaryBindings.begin(); bound != primaryBindings.end();)
            {
                if(bound->second == action)
                    bound = primaryBindings.erase(bound);
                else
                    bound++;
            }
            primaryBindings[trigger] = action;
        }
        else
        {
            for(auto bound = secondaryBindings.begin(); bound != secondaryBindings.end();)
            {
                if(bound->second == action)
                    bound = secondaryBindings.erase(bound);
                else
                    bound++;
            }
            secondaryBindings[trigger] = action;
        }
    }

    template<class Action>
    void ActionHandler<Action>::bindKeyRelease(Keyboard::Code code, const Action& action, bool secondary)
    {
        ActionTrigger trigger;
        trigger.type = ActionTrigger::KEYRELEASE;
        trigger.keyCode = code;

        if(!secondary)
        {
            for(auto bound = primaryBindings.begin(); bound != primaryBindings.end();)
            {
                if(bound->second == action)
                    bound = primaryBindings.erase(bound);
                else
                    bound++;
            }
            primaryBindings[trigger] = action;
        }
        else
        {
            for(auto bound = secondaryBindings.begin(); bound != secondaryBindings.end();)
            {
                if(bound->second == action)
                    bound = secondaryBindings.erase(bound);
                else
                    bound++;
            }
            secondaryBindings[trigger] = action;
        }
    }

    template<class Action>
    void ActionHandler<Action>::bindMousePress(Mouse::Button button, const Action& action, bool secondary)
    {
        ActionTrigger trigger;
        trigger.type = ActionTrigger::MOUSEPRESS;
        trigger.mouseButton = button;

        if(!secondary)
        {
            for(auto bound = primaryBindings.begin(); bound != primaryBindings.end();)
            {
                if(bound->second == action)
                    bound = primaryBindings.erase(bound);
                else
                    bound++;
            }
            primaryBindings[trigger] = action;
        }
        else
        {
            for(auto bound = secondaryBindings.begin(); bound != secondaryBindings.end();)
            {
                if(bound->second == action)
                    bound = secondaryBindings.erase(bound);
                else
                    bound++;
            }
            secondaryBindings[trigger] = action;
        }
    }

    template<class Action>
    void ActionHandler<Action>::bindMouseRelease(Mouse::Button button, const Action& action, bool secondary)
    {
        ActionTrigger trigger;
        trigger.type = ActionTrigger::MOUSERELEASE;
        trigger.mouseButton = button;

        if(!secondary)
        {
            for(auto bound = primaryBindings.begin(); bound != primaryBindings.end();)
            {
                if(bound->second == action)
                    bound = primaryBindings.erase(bound);
                else
                    bound++;
            }
            primaryBindings[trigger] = action;
        }
        else
        {
            for(auto bound = secondaryBindings.begin(); bound != secondaryBindings.end();)
            {
                if(bound->second == action)
                    bound = secondaryBindings.erase(bound);
                else
                    bound++;
            }
            secondaryBindings[trigger] = action;
        }
    }

    template<class Action>
    void ActionHandler<Action>::bindGamepadPress(uint32_t id, uint32_t button, const Action& action, bool secondary)
    {
        ActionTrigger trigger;
        trigger.type = ActionTrigger::GAMEPADPRESS;
        trigger.gamepadButton = button;
        trigger.gamepadId = id;
        
        if(!secondary)
        {
            for(auto bound = primaryBindings.begin(); bound != primaryBindings.end();)
            {
                if(bound->second == action)
                    bound = primaryBindings.erase(bound);
                else
                    bound++;
            }
            primaryBindings[trigger] = action;
        }
        else
        {
            for(auto bound = secondaryBindings.begin(); bound != secondaryBindings.end();)
            {
                if(bound->second == action)
                    bound = secondaryBindings.erase(bound);
                else
                    bound++;
            }
            secondaryBindings[trigger] = action;
        }
    }

    template<class Action>
    void ActionHandler<Action>::bindGamepadRelease(uint32_t id, uint32_t button, const Action& action, bool secondary)
    {
        ActionTrigger trigger;
        trigger.type = ActionTrigger::GAMEPADRELEASE;
        trigger.gamepadButton = button;
        trigger.gamepadId = id;
        
        if(!secondary)
        {
            for(auto bound = primaryBindings.begin(); bound != primaryBindings.end();)
            {
                if(bound->second == action)
                    bound = primaryBindings.erase(bound);
                else
                    bound++;
            }
            primaryBindings[trigger] = action;
        }
        else
        {
            for(auto bound = secondaryBindings.begin(); bound != secondaryBindings.end();)
            {
                if(bound->second == action)
                    bound = secondaryBindings.erase(bound);
                else
                    bound++;
            }
            secondaryBindings[trigger] = action;
        }
    }

    template<class Action>
    const std::map<ActionTrigger, Action>& ActionHandler<Action>::getPrimaryBindings()
    {
        return primaryBindings;
    }
    
    template<class Action>
    const std::map<ActionTrigger, Action>& ActionHandler<Action>::getSecondaryBindings()
    {
        return secondaryBindings;
    }
    
    template<class Action>        
    void ActionHandler<Action>::setPrimaryBindings(const std::map<ActionTrigger, Action>& bindings)
    {
        primaryBindings = bindings;
    }

    template<class Action>
    void ActionHandler<Action>::setSecondaryBindings(const std::map<ActionTrigger, Action>& bindings)
    {
        secondaryBindings = bindings;
    }
    
    template<class Action>
    void ActionHandler<Action>::removePrimaryBinding(const Action& action)
    {
        for(auto bound = primaryBindings.begin(); bound != primaryBindings.end();)
        {
            if(bound->second == action)
                bound = primaryBindings.erase(bound);
            else
                bound++;
        }
    }

    template<class Action>
    void ActionHandler<Action>::removeSecondaryBinding(const Action& action)
    {
        for(auto bound = secondaryBindings.begin(); bound != secondaryBindings.end();)
        {
            if(bound->second == action)
                bound = secondaryBindings.erase(bound);
            else
                bound++;
        }
    }
    
    template<class Action>
    void ActionHandler<Action>::clearBindings()
    {
        primaryBindings.clear();
        secondaryBindings.clear();
    }
    
    template<class Action>
    void ActionHandler<Action>::clearActions()
    {
        actions = std::queue<Action>();
    }

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
     *  Both primary and secondary bindings can be bound to an action. Both the primary and secondary input event will trigger the action. For instance, if you bind BITE primarily to Keyboard::SPACE and secondarily to Keyboard::G, pressing either space or g will generate the action.
     *
     *  If a binding is created for an input or action so that it would conflict an already existing binding, the old binding will be overwritten and not valid anymore.
     *  @tparam Type which is used as the action type.
     ***
     *  @fn void ActionHandler::processActions(const InputHandler& input, bool keepLast = false)
     *  @brief Generate actions from the generated events of an InputHandler.
     *
     *  The InputHandler given as an argument will be scanned for generated input events. If the ActionHandler currently has bindings related to the events found, appropriate actions will be generated and stored. 
     *  This function must be called before InputHandler::pollEvent is called, since that function deletes input events from the InputHandler. It also has to be called before ActionHandler::pollAction, or there will be no actions to poll.
     *
     *  @param input InputHandler instance to generate actions from.
     *  @param keepLast If this is false, the ActionHandler will discard all unhandled actions. Otherwise, new actions will be queued after the old ones. Default value is false.
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
