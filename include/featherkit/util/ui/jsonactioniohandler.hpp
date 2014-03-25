#pragma once
#include <map>
#include <string>
#include <featherkit/ui/inputfilenotfoundexception.hpp>
#include <featherkit/ui/actiontrigger.hpp>
#include <featherkit/json/json.h>
#include <fstream>
#include <sstream>

namespace fea
{
    namespace util
    {
        template<class Action>
            class JsonActionIOHandler
            {
                public:
                    void loadBindingsFile(const std::string& path, std::function<std::string(Action)> stringToAction = [] (Action a) { return a;});
                    void saveBindingsFile(const std::string& path, const std::map<ActionTrigger, Action>& primaryActions) const;
                    void saveBindingsFile(const std::string& path, const std::map<ActionTrigger, Action>& primaryActions, const std::map<ActionTrigger, Action>& secondaryActions) const;
                    const std::map<ActionTrigger, Action>& getPrimaryBindings() const;
                    const std::map<ActionTrigger, Action>& getSecondaryBindings() const;
                private:
                    std::map<ActionTrigger, Action> mPrimaryBindings;
                    std::map<ActionTrigger, Action> mSecondaryBindings;
            };

#include <featherkit/util/ui/jsonactioniohandler.inl>

        /** @addtogroup UserInterface
         *@{
         *  @class JsonActionIOHandler
         *@}
         ***
         *  @class JsonActionIOHandler
         *  @brief This class is for loading and saving json files describing Action bindings.
         *
         *  The output of the loading functions of this class can directly be passed to the ActionHandler to bind the actions saved. To bind the actions, first load a json file using JsonActionIOHandler::loadBindingsFile. Then pass the output of JsonActionIOHandler::getPrimaryBindings into ActionHandler::setPrimaryBindings and JsonActionIOHandler::getSecondaryBindings into ActionHandler::setSecondaryBindings if needed.
         *
         *  The type used as actions must support string serialisations using the << operator for this to work.
         *
         *  @tparam Type used as actions.
         ***
         *  @fn void JsonActionIOHandler::loadBindingsFile(const std::string& path, std::function<std::string(Action)> stringToAction = [] (Action a) { return a;});
         *  @brief Load a json file defining bindings for actions.
         *
         *  Use this function to load an attribute file. When the bindings are loaded, they can be accessed with JsonActionIOHandler::getPrimaryBindings and JsonActionIOHandler::getSecondaryBindings.
         *  Throws FileNotFoundException when the file does not exist.
         *
         *  Since actions can be of an arbitrary type, a converter function must be supplied that converts the action type from an std::string (since they are saved as string in the json file). The default value of this parameter is sufficient if std::string is used as the action type.
         *  @param path File to open.
         *  @param stringToAction Function to use for the string to action conversion. Default works for std::string as the action type.
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
         *  @fn const std::map<ActionTrigger, Action>& JsonActionIOHandler::getPrimaryBindings() const
         *  @brief Retrieve loaded primary bindings.
         *
         *  JsonActionIOHandler::loadBindingsFile must be called before this function or the returned map will be empty.
         *  @return Map containing primary bindings.
         ***
         *  @fn const std::map<ActionTrigger, Action>& JsonActionIOHandler::getSecondaryBindings() const
         *  @brief Retrieve loaded secondary bindings.
         *
         *  JsonActionIOHandler::loadBindingsFile must be called before this function or the returned map will be empty.
         *  @return Map containing secondary bindings.
         **/
    }
}
