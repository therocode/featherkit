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
     *  This class let's you poll actions in a way similar to how the InputHandler lets you poll input events. These actions can the be used to control the game. By using actions instead of raw input in the game, key configurations and platform portability is a lot easier to setup since only the bindings need to be changed. 
     *
     *  Actions are of an arbitrary type, provided as a template argument upon class creation. The event types that can be bound are KEYPRESSED, KEYRELEASED, MOUSEBUTTONPRESSED, MOUSEBUTTONRELEASED, GAMEPADBUTTONPRESSED and GAMEPADBUTTONRELEASED. When an event which is bound is fired, the corresponding action it is bound to is fired as well. Actions that have been fired are stored until the user accesses or deletes them. Actions are polled in a very similar way to events.
     *  @tparam Action Type which is used as the action type.
     ***
     *  @fn void ActionHandler::processActions(const InputHandler& input, bool keepLast = false)
     *  @brief Scans an InputHandler instance for generated events.
     *
     *  Scans an InputHandler instance for generated events and fires appropriate actions if any of the generated events are bound. Must be called before InputHandler::pollEvent() since that function removes generated events.
     *  @param input InputHandler instance to scan.
     *  @param keepLast If this is false, the ActionHandler will discard all unhandled actions. Otherwise, new actions will be queued after the old ones. Default value is false.
     ***
     *  @fn bool ActionHandler::pollAction(Action& action)
     ***
     *  @fn void ActionHandler::bindKeyPress(Keyboard::Code code, const Action& action, bool secondary = false)
     ***
     *  @fn void ActionHandler::bindKeyRelease(Keyboard::Code code, const Action& action, bool secondary = false)
     ***
     *  @fn void ActionHandler::bindMousePress(Mouse::Button button, const Action& action, bool secondary = false)
     ***
     *  @fn void ActionHandler::bindMouseRelease(Mouse::Button button, const Action& action, bool secondary = false)
     ***
     *  @fn void ActionHandler::bindGamepadPress(uint32_t id, uint32_t button, const Action& action, bool secondary = false)
     ***
     *  @fn void ActionHandler::bindGamepadRelease(uint32_t id, uint32_t button, const Action& action, bool secondary = false)
     ***
     *  @fn const std::map<ActionTrigger, Action>& ActionHandler::getPrimaryBindings()
     ***
     *  @fn const std::map<ActionTrigger, Action>& ActionHandler::getSecondaryBindings()
     ***
     *  @fn void ActionHandler::setPrimaryBindings(const std::map<ActionTrigger, Action>& bindings)
     ***
     *  @fn void ActionHandler::setSecondaryBindings(const std::map<ActionTrigger, Action>& bindings)
     ***
     *  @fn void ActionHandler::removePrimaryBinding(const Action& action)
     ***
     *  @fn void ActionHandler::removeSecondaryBinding(const Action& action)
     ***
     *  @fn void ActionHandler::clearBindings()
     ***
     *  @fn void ActionHandler::clearActions()
     **/
}
