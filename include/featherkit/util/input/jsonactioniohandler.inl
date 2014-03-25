template<class Action>
void JsonActionIOHandler<Action>::loadBindingsFile(const std::string& path, std::function<std::string(Action)> stringToAction)
{
    mPrimaryBindings.clear();
    mSecondaryBindings.clear();

    std::ifstream file(path);

    if(!file)
    {
        std::stringstream ss;
        ss << "Error! Entity file not found: " << path << "\n";
        throw fea::InputFileNotFoundException(ss.str());
    }

    json::Value root;
    root.SetObject();
    json::read(file, root);

    if(root.HasMember("primary"))
    {
        json::Value primaryArray = root.GetArrayMember("primary");
        uint32_t bindingAmount = primaryArray.GetNumElements();

        for(uint32_t i = 0; i < bindingAmount; i++)
        {
            json::Value binding = primaryArray.GetElement(i);
            std::string type = binding.GetStringMember("type");

            ActionTrigger tempTrigger;
            Action tempAction = stringToAction(binding.GetStringMember("action"));

            if(type == "keypress")
            {
                tempTrigger.type = ActionTrigger::KEYPRESS;
                tempTrigger.keyCode = (Keyboard::Code) std::stoi(binding.GetStringMember("key"));
            }
            else if(type == "keyrelease")
            {
                tempTrigger.type = ActionTrigger::KEYRELEASE;
                tempTrigger.keyCode = (Keyboard::Code) std::stoi(binding.GetStringMember("key"));
            }
            else if(type == "mousepress")
            {
                tempTrigger.type = ActionTrigger::MOUSEPRESS;
                tempTrigger.mouseButton = (Mouse::Button) std::stoi(binding.GetStringMember("mousebutton"));
            }
            else if(type == "mouserelease")
            {
                tempTrigger.type = ActionTrigger::MOUSERELEASE;
                tempTrigger.mouseButton = (Mouse::Button) std::stoi(binding.GetStringMember("mousebutton"));
            }
            else if(type == "gamepadpress")
            {
                tempTrigger.type = ActionTrigger::GAMEPADPRESS;
                tempTrigger.gamepadButton = (uint32_t) std::stoi(binding.GetStringMember("gamepadbutton"));
                tempTrigger.gamepadId = (uint32_t) std::stoi(binding.GetStringMember("gamepadid"));
            }
            else if(type == "gamepadrelease")
            {
                tempTrigger.type = ActionTrigger::GAMEPADRELEASE;
                tempTrigger.gamepadButton = (uint32_t) std::stoi(binding.GetStringMember("gamepadbutton"));
                tempTrigger.gamepadId = (uint32_t) std::stoi(binding.GetStringMember("gamepadid"));
            }

            mPrimaryBindings.insert(std::pair<ActionTrigger, Action>(tempTrigger, tempAction));
        }
    }

    if(root.HasMember("secondary"))
    {
        json::Value secondaryArray = root.GetArrayMember("secondary");
        uint32_t bindingAmount = secondaryArray.GetNumElements();

        for(uint32_t i = 0; i < bindingAmount; i++)
        {
            json::Value binding = secondaryArray.GetElement(i);
            std::string type = binding.GetStringMember("type");

            ActionTrigger tempTrigger;
            Action tempAction = stringToAction(binding.GetStringMember("action"));

            if(type == "keypress")
            {
                tempTrigger.type = ActionTrigger::KEYPRESS;
                tempTrigger.keyCode = (Keyboard::Code) std::stoi(binding.GetStringMember("key"));
            }
            else if(type == "keyrelease")
            {
                tempTrigger.type = ActionTrigger::KEYRELEASE;
                tempTrigger.keyCode = (Keyboard::Code) std::stoi(binding.GetStringMember("key"));
            }
            else if(type == "mousepress")
            {
                tempTrigger.type = ActionTrigger::MOUSEPRESS;
                tempTrigger.mouseButton = (Mouse::Button) std::stoi(binding.GetStringMember("mousebutton"));
            }
            else if(type == "mouserelease")
            {
                tempTrigger.type = ActionTrigger::MOUSERELEASE;
                tempTrigger.mouseButton = (Mouse::Button) std::stoi(binding.GetStringMember("mousebutton"));
            }
            else if(type == "gamepadpress")
            {
                tempTrigger.type = ActionTrigger::GAMEPADPRESS;
                tempTrigger.gamepadButton = (uint32_t) std::stoi(binding.GetStringMember("gamepadbutton"));
                tempTrigger.gamepadId = (uint32_t) std::stoi(binding.GetStringMember("gamepadid"));
            }
            else if(type == "gamepadrelease")
            {
                tempTrigger.type = ActionTrigger::GAMEPADRELEASE;
                tempTrigger.gamepadButton = (uint32_t) std::stoi(binding.GetStringMember("gamepadbutton"));
                tempTrigger.gamepadId = (uint32_t) std::stoi(binding.GetStringMember("gamepadid"));
            }

            mSecondaryBindings.insert(std::pair<ActionTrigger, Action>(tempTrigger, tempAction));
        }
    }
}

template<class Action>
void JsonActionIOHandler<Action>::saveBindingsFile(const std::string& path, const std::map<ActionTrigger, Action>& primaryActions) const
{
    std::map<ActionTrigger, Action> emptyActions;
    saveBindingsFile(path, primaryActions, emptyActions);
}

template<class Action>
void JsonActionIOHandler<Action>::saveBindingsFile(const std::string& path, const std::map<ActionTrigger, Action>& primaryActions, const std::map<ActionTrigger, Action>& secondaryActions) const
{
    json::Value root;
    root.SetObject();

    json::Value primaryArray;
    primaryArray.SetArray();

    json::Value secondaryArray;
    secondaryArray.SetArray();

    std::ofstream file(path);

    if(!file)
    {
        std::stringstream ss;
        ss << "Error! Action bindings file not found: " << path << "\n";
        throw fea::InputFileNotFoundException(ss.str());
    }

    for(auto binding : primaryActions)
    {
        ActionTrigger::ActionType type = binding.first.type;

        json::Value bindingEntry;
        bindingEntry.SetObject();

        switch(type)
        {
            case ActionTrigger::KEYPRESS:
                bindingEntry.SetStringMember("type", "keypress");
                bindingEntry.SetStringMember("key", std::to_string(binding.first.keyCode));
                break;
            case ActionTrigger::KEYRELEASE:
                bindingEntry.SetStringMember("type", "keyrelease");
                bindingEntry.SetStringMember("key", std::to_string(binding.first.keyCode));
                break;
            case ActionTrigger::MOUSEPRESS:
                bindingEntry.SetStringMember("type", "mousepress");
                bindingEntry.SetStringMember("mousebutton", std::to_string(binding.first.mouseButton));
                break;
            case ActionTrigger::MOUSERELEASE:
                bindingEntry.SetStringMember("type", "mouserelease");
                bindingEntry.SetStringMember("mousebutton", std::to_string(binding.first.mouseButton));
                break;
            case ActionTrigger::GAMEPADPRESS:
                bindingEntry.SetStringMember("type", "gamepadpress");
                bindingEntry.SetStringMember("gamepadid", std::to_string(binding.first.gamepadId));
                bindingEntry.SetStringMember("gamepadbutton", std::to_string(binding.first.gamepadButton));
                break;
            case ActionTrigger::GAMEPADRELEASE:
                bindingEntry.SetStringMember("type", "gamepadrelease");
                bindingEntry.SetStringMember("gamepadid", std::to_string(binding.first.gamepadId));
                bindingEntry.SetStringMember("gamepadbutton", std::to_string(binding.first.gamepadButton));
                break;
            default:
                break;
        }

        std::stringstream ss;
        ss << binding.second;

        bindingEntry.SetStringMember("action", ss.str());

        primaryArray.AddObject(bindingEntry);
    }

    if(primaryActions.size() > 0)
    {
        root.SetObjectMember("primary", primaryArray);
    }

    for(auto binding : secondaryActions)
    {
        ActionTrigger::ActionType type = binding.first.type;

        json::Value bindingEntry;
        bindingEntry.SetObject();

        switch(type)
        {
            case ActionTrigger::KEYPRESS:
                bindingEntry.SetStringMember("type", "keypress");
                bindingEntry.SetStringMember("key", std::to_string(binding.first.keyCode));
                break;
            case ActionTrigger::KEYRELEASE:
                bindingEntry.SetStringMember("type", "keyrelease");
                bindingEntry.SetStringMember("key", std::to_string(binding.first.keyCode));
                break;
            case ActionTrigger::MOUSEPRESS:
                bindingEntry.SetStringMember("type", "mousepress");
                bindingEntry.SetStringMember("mousebutton", std::to_string(binding.first.mouseButton));
                break;
            case ActionTrigger::MOUSERELEASE:
                bindingEntry.SetStringMember("type", "mouserelease");
                bindingEntry.SetStringMember("mousebutton", std::to_string(binding.first.mouseButton));
                break;
            case ActionTrigger::GAMEPADPRESS:
                bindingEntry.SetStringMember("type", "gamepadpress");
                bindingEntry.SetStringMember("gamepadid", std::to_string(binding.first.gamepadId));
                bindingEntry.SetStringMember("gamepadbutton", std::to_string(binding.first.gamepadButton));
                break;
            case ActionTrigger::GAMEPADRELEASE:
                bindingEntry.SetStringMember("type", "gamepadrelease");
                bindingEntry.SetStringMember("gamepadid", std::to_string(binding.first.gamepadId));
                bindingEntry.SetStringMember("gamepadbutton", std::to_string(binding.first.gamepadButton));
                break;
            default:
                break;
        }

        std::stringstream ss;
        ss << binding.second;

        bindingEntry.SetStringMember("action", ss.str());

        secondaryArray.AddObject(bindingEntry);
    }

    if(secondaryActions.size() > 0)
    {
        root.SetObjectMember("secondary", secondaryArray);
    }

    json::write(file, root);
}

template<class Action>
const std::map<ActionTrigger, Action>& JsonActionIOHandler<Action>::getPrimaryBindings() const
{
    return mPrimaryBindings;
}

template<class Action>
const std::map<ActionTrigger, Action>& JsonActionIOHandler<Action>::getSecondaryBindings() const
{
    return mSecondaryBindings;
}
