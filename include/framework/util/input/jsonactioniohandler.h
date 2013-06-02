#include <map>
#include <string>
#include <framework/util/filenotfoundexception.h>
#include <framework/input/actiontrigger.h>
#include <framework/json/json.h>
#include <fstream>
#include <sstream>

namespace windbreeze
{
    template<class Action>
    class JsonActionIOHandler
    {
        public:
            void loadBindingsFile(const std::string& path) const;
            void saveBindingsFile(const std::string& path, const std::map<ActionTrigger, Action>& primaryActions) const;
            void saveBindingsFile(const std::string& path, const std::map<ActionTrigger, Action>& primaryActions, const std::map<ActionTrigger, Action>& secondaryActions) const;
            const std::map<ActionTrigger, Action> getPrimaryBindings() const;
            const std::map<ActionTrigger, Action> getSecondaryBindings() const;
        private:
            std::map<ActionTrigger, Action> primaryBindings;
            std::map<ActionTrigger, Action> secondaryBindings;
    };

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
            throw windgale::FileNotFoundException(ss.str());
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
                    bindingEntry.SetStringMember("type", "keypress");
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
                    bindingEntry.SetStringMember("type", "keypress");
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
    /** @addtogroup UserInterface
     *@{
     *  @class JsonActionIOHandler
     *@}
     ***
     *  @class JsonActionIOHandler
     *  @brief This class is for loading and saving json files describing Action bindings.
     *
     *  The output of the loading functions of this class can directly be passed to the ActionHandler to bind the actions saved. To bind the actions, first load a json file using JsonActionIOHandler::loadBindingsFile. Then pass the output of JsonActionIOHandler::getPrimaryBindings into ActionHandler::setPrimaryBindings and JsonActionIOHandler::getSecondaryBindings into ActionHandler::setSecondaryBindings if needed.
     ***
     *  @fn void JsonActionIOHandler::loadBindingsFile(const std::string& path) const
     *  @brief Load a json file defining bindings for actions.
     *
     *  Use this function to load an attribute file. When the bindings are loaded, they can be accessed with JsonActionIOHandler::getPrimaryBindings and JsonActionIOHandler::getSecondaryBindings.
     *  @param path File to open.
     ***
     *  @fn void JsonActionIOHandler::saveBindingsFile(const std::string& path, const std::map<ActionTrigger, Action>& primaryActions) const
     *  @brief Save action bindings to a json formatted file.
     *  
     *  @param path File to save the bindings in.
     *  @param primaryActions Map of primary actions. Obtainable through the ActionHandler.
     ***
     *  @fn void JsonActionIOHandler::saveBindingsFile(const std::string& path, const std::map<ActionTrigger, Action>& primaryActions, const std::map<ActionTrigger, Action>& secondaryActions) const
     *  @brief Save action bindings to a json formatted file.
     *
     *  @param path File to save the bindings in.
     *  @param primaryActions Map of primary actions. Obtainable through the ActionHandler.
     *  @param secondaryActions Map of secondary actions. Obtainable through the ActionHandler.
     ***
     *  @fn const std::map<ActionTrigger, Action> JsonActionIOHandler::getPrimaryBindings() const
     *  @brief Retrieve loaded primary bindings.
     *
     *  JsonActionIOHandler::loadBindingsFile must be called before this function or the returned map will be empty.
     *  @return Map containing primary bindings.
     ***
     *  @fn const std::map<ActionTrigger, Action> JsonActionIOHandler::getSecondaryBindings() const
     *  @brief Retrieve loaded secondary bindings.
     *
     *  JsonActionIOHandler::loadBindingsFile must be called before this function or the returned map will be empty.
     *  @return Map containing secondary bindings.
     **/
}
