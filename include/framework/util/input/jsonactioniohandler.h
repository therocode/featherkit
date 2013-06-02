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
    /** @addtogroup EntitySystem
     *@{
     *  @class JsonActionIOHandler
     *@}
     ***
     *  @class JsonActionIOHandler
     *  @brief This class is for loading and saving json files describing Action bindings.
     *
     *  The output of the loading functions of this class can directly be passed to the ActionHandler to bind the actions saved. To bind the actions, first load a json file using JsonActionIOHandler::loadBindingsFile. Then pass the output of JsonActionIOHandler::getPrimaryBindings into ActionHandler::setPrimaryBindings and JsonActionIOHandler::getSecondaryBindings into ActionHandler::setSecondaryBindings if needed.
     *
     *  Here is an example of how an attribute file should be formatted:
     *  @code
     *  {
     *      "position":"8",
     *      "velocity":"8",
     *      "originalcolour":"12",
     *      "currentcolour":"12",
     *      "spawnrate":"#uint32#",
     *      "spawnpower":"#float#",
     *      "deathrate":"#uint32#",
     *      "id":"#uint32#"
     *  }
     *  @endcode
     *  The formatting is very simple. Every row defines an attribute that could be used in an Entity type definition. The two values needed per row are firstly the name of the attribute, and secondly the amount of memory needed to store it in bytes. For example, the first row defines an attribute called "position". Since the position in the application will be implemented using a struct composed of two floats, one for X and one for Y, and floats are 4 bytes each, a total of 8 bytes are needed.
     *
     *  It is also possible to have special data type tags instead of numbers. These tags directly correspond to sizes of C++ data types. Here is a complete list of data type tags and the C++ types they correspond to.
     *  - \#uint32\# - uint32_t
     *  - \#int32\# - int32_t
     *  - \#float\# - float
     *  - \#double\# - double
     *  - \#bool\# - bool
     *  - \#byte\# - char
     *  - \#char\# - char
     *
     *  Here is an example of how an Entity type file should be formatted:
     *  @code
     *  {
     *      "particle":
     *      {
     *          "position":"20.0f,40.0f", "velocity":"0.0f,0.0f", "currentcolour":"1.0f, 0.0f, 0.0f", "deathrate":"9000", "id":"#ID#"
     *      },
     *      "spawner":
     *      {
     *          "position":"30.0f,50.0f", "currentcolour":"", "spawnrate":"100", "spawnpower":"5.0f", "id":"#ID#"
     *      }
     *  }
     *  @endcode
     *  The file is divided into Entity type definitions. The two entities defined in this files are "particle" and "spawner". Every Entity type internally defines a sequence of attributes that they should have. The attributes might come with default values. For instance, the first attribute of the Entity type "particle" is "position" with a default value of "20.0f,40.0".
     ***
     *  @fn std::map<std::string, int> JsonEntityLoader::loadAttributesJson(const std::string& path)
     *  @brief Load a json file defining Entity attributes.
     *
     *  Use this function to load an attribute file. The return value can be given to the EntityManager::loadAttributes function.
     *  @param path File to open.
     *  @return A map with the attributes, to pass to the EntityManager.
     ***
     *  @fn std::map<std::string, std::map<std::string, std::string> > JsonEntityLoader::loadEntitiesJson(const std::string& path)
     *  @brief Load a json file defining Entity types.
     *
     *  Use this function to load an Entity type file. The return value can be given to the EntityManager::loadEntityTypes function.
     *  @param path File to open.
     *  @return A map with the Entity types, to pass to the EntityManager.
     **/
}
