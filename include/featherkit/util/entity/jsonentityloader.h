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
        };
        /** @addtogroup EntitySystem
         *@{
         *  @class JsonEntityLoader
         *@}
         ***
         *  @class JsonEntityLoader
         *  @brief This class is for loading json files describing entity templates.
         *
         *  The content of the returned map can directly be passed to the EntityFactory to register the attribute and Entity templates.
         *
         *  Here is an example of how an Entity template file should be formatted:
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
         *  The file is divided into Entity template definitions. The two entities defined in this files are "particle" and "spawner". Every Entity template internally defines a sequence of attributes that they should have. The attributes might come with default values. For instance, the first attribute of the Entity template "particle" is "position" with a default value of "20.0f,40.0".
         ***
         *  @fn std::unordered_map<std::string, EntityTemplate> JsonEntityLoader::loadEntityTemplates(const std::string& path)
         *  @brief Load a json file defining Entity templates.
         *
         *  Use this function to load an Entity template file. The content of the return value can be given to the EntityFactory::addTemplate function.
         *  @param path File to open.
         *  @return A map with the Entity templates.
         **/
    }
}
