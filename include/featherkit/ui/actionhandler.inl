template<class Action>
void ActionHandler<Action>::feedEvent(const Event& event)
{

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
            break;
    }


    binding = mPrimaryBindings.find(trigger);

    if(binding != mPrimaryBindings.end())
    {
        mActions.push(binding->second);
    }
    else
    {
        binding = mSecondaryBindings.find(trigger);
        if(binding != mSecondaryBindings.end())
        {
            mActions.push(binding->second);
        }
    }
}

    template<class Action>
bool ActionHandler<Action>::pollAction(Action& action)
{
    if(mActions.size() > 0)
    {
        action = mActions.front();
        mActions.pop();
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
        for(auto bound = mPrimaryBindings.begin(); bound != mPrimaryBindings.end();)
        {
            if(bound->second == action)
                bound = mPrimaryBindings.erase(bound);
            else
                bound++;
        }
        mPrimaryBindings[trigger] = action;
    }
    else
    {
        for(auto bound = mSecondaryBindings.begin(); bound != mSecondaryBindings.end();)
        {
            if(bound->second == action)
                bound = mSecondaryBindings.erase(bound);
            else
                bound++;
        }
        mSecondaryBindings[trigger] = action;
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
        for(auto bound = mPrimaryBindings.begin(); bound != mPrimaryBindings.end();)
        {
            if(bound->second == action)
                bound = mPrimaryBindings.erase(bound);
            else
                bound++;
        }
        mPrimaryBindings[trigger] = action;
    }
    else
    {
        for(auto bound = mSecondaryBindings.begin(); bound != mSecondaryBindings.end();)
        {
            if(bound->second == action)
                bound = mSecondaryBindings.erase(bound);
            else
                bound++;
        }
        mSecondaryBindings[trigger] = action;
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
        for(auto bound = mPrimaryBindings.begin(); bound != mPrimaryBindings.end();)
        {
            if(bound->second == action)
                bound = mPrimaryBindings.erase(bound);
            else
                bound++;
        }
        mPrimaryBindings[trigger] = action;
    }
    else
    {
        for(auto bound = mSecondaryBindings.begin(); bound != mSecondaryBindings.end();)
        {
            if(bound->second == action)
                bound = mSecondaryBindings.erase(bound);
            else
                bound++;
        }
        mSecondaryBindings[trigger] = action;
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
        for(auto bound = mPrimaryBindings.begin(); bound != mPrimaryBindings.end();)
        {
            if(bound->second == action)
                bound = mPrimaryBindings.erase(bound);
            else
                bound++;
        }
        mPrimaryBindings[trigger] = action;
    }
    else
    {
        for(auto bound = mSecondaryBindings.begin(); bound != mSecondaryBindings.end();)
        {
            if(bound->second == action)
                bound = mSecondaryBindings.erase(bound);
            else
                bound++;
        }
        mSecondaryBindings[trigger] = action;
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
        for(auto bound = mPrimaryBindings.begin(); bound != mPrimaryBindings.end();)
        {
            if(bound->second == action)
                bound = mPrimaryBindings.erase(bound);
            else
                bound++;
        }
        mPrimaryBindings[trigger] = action;
    }
    else
    {
        for(auto bound = mSecondaryBindings.begin(); bound != mSecondaryBindings.end();)
        {
            if(bound->second == action)
                bound = mSecondaryBindings.erase(bound);
            else
                bound++;
        }
        mSecondaryBindings[trigger] = action;
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
        for(auto bound = mPrimaryBindings.begin(); bound != mPrimaryBindings.end();)
        {
            if(bound->second == action)
                bound = mPrimaryBindings.erase(bound);
            else
                bound++;
        }
        mPrimaryBindings[trigger] = action;
    }
    else
    {
        for(auto bound = mSecondaryBindings.begin(); bound != mSecondaryBindings.end();)
        {
            if(bound->second == action)
                bound = mSecondaryBindings.erase(bound);
            else
                bound++;
        }
        mSecondaryBindings[trigger] = action;
    }
}

    template<class Action>
const std::map<ActionTrigger, Action>& ActionHandler<Action>::getPrimaryBindings()
{
    return mPrimaryBindings;
}

    template<class Action>
const std::map<ActionTrigger, Action>& ActionHandler<Action>::getSecondaryBindings()
{
    return mSecondaryBindings;
}

    template<class Action>        
void ActionHandler<Action>::setPrimaryBindings(const std::map<ActionTrigger, Action>& bindings)
{
    mPrimaryBindings = bindings;
}

    template<class Action>
void ActionHandler<Action>::setSecondaryBindings(const std::map<ActionTrigger, Action>& bindings)
{
    mSecondaryBindings = bindings;
}

    template<class Action>
void ActionHandler<Action>::removePrimaryBinding(const Action& action)
{
    for(auto bound = mPrimaryBindings.begin(); bound != mPrimaryBindings.end();)
    {
        if(bound->second == action)
            bound = mPrimaryBindings.erase(bound);
        else
            bound++;
    }
}

    template<class Action>
void ActionHandler<Action>::removeSecondaryBinding(const Action& action)
{
    for(auto bound = mSecondaryBindings.begin(); bound != mSecondaryBindings.end();)
    {
        if(bound->second == action)
            bound = mSecondaryBindings.erase(bound);
        else
            bound++;
    }
}

    template<class Action>
void ActionHandler<Action>::clearBindings()
{
    mPrimaryBindings.clear();
    mSecondaryBindings.clear();
}

    template<class Action>
void ActionHandler<Action>::clearActions()
{
    mActions = std::queue<Action>();
}

