#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <featherkit/util/filenotfoundexception.h>
#include <featherkit/entity/entityfactory.h>

namespace fea
{
    namespace util
    {
        class JsonEntityLoader
        {
            public:
                std::unordered_map<std::string, EntityTemplate> loadEntityTemplates(const std::string& path);
                std::unordered_map<std::string, std::string> loadEntityAttributes(const std::string& path);
        };
        /** @addtogroup EntitySystem
         *@{
         *  @class JsonEntityLoader
         *@}
         ***
         *  @class JsonEntityLoader
         *  @brief This class is for loading json files describing entity templates and entity attributes.
         *
         *  The content of the returned maps can directly be passed to the EntityFactory to register the attributes and entity templates.
         *
         *  Here is an example of how an entity attribute file should be formatted:
         *  @code
         *  {
         *       "position":"vec2",
         *       "velocity":"vec2",
         *       "acceleration":"vec2",
         *       "maxvelocity":"float",
         *       "maxacceleration":"float",
         *  }
         *  @endcode
         *
         *  Here is an example of how an entity template file should be formatted:
         *  @code
         *  {
         *      "cow":
         *      {
         *          "position":"20.0f,40.0f", "velocity":"0.0f,0.0f", "acceleration":"1.0f,0.0f", "health":"9000"
         *      },
         *      "player":
         *      {
         *          "position":"30.0f,50.0f", "velocity":"0.0f,0.0f", "acceleration":"0.0f,0.0f", "health":"5"
         *      }
         *  }
         *  @endcode
         *  The file is divided into entity template definitions. The two entities defined in this files are "cow" and "player". Every entity template internally defines a sequence of attributes that they should have. The attributes might come with default values. For instance, the first attribute of the entity template "cow" is "player" with a default value of "20.0f,40.0".
         ***
         *  @fn std::unordered_map<std::string, EntityTemplate> JsonEntityLoader::loadEntityTemplates(const std::string& path)
         *  @brief Load a json file defining entity templates.
         *
         *  Use this function to load an entity template file. The content of the return value can be given to the EntityFactory::addTemplate function.
         *  Throws FileNotFoundException when the file does not exist.
         *  @param path File to open.
         *  @return A map with the entity templates.
         ***
         *  @fn std::unordered_map<std::string, std::string> JsonEntityLoader::loadEntityAttributes(const std::string& path)
         *  @brief Load a json file defining entity attributes.
         *
         *  Use this function to load an entity attribute file. The content of the return value can be given to the EntityFactory::registerAttribute function.
         *  Throws FileNotFoundException when the file does not exist.
         *  @param path File to open.
         *  @return A map with the entity attributes.
         **/
    }
}
