#pragma once
#include <fea/config.hpp>
#include <vector>
#include <string>
#include <fea/entity/filenotfoundexception.hpp>
#include <fea/entity/entityfactory.hpp>
#include <json/value.h>

namespace fea
{
    class FEA_API JsonEntityLoader
    {
        public:
            std::unordered_map<std::string, std::string> jsonObjToStringMap(const Json::Value&);

            std::vector<std::pair<std::string, EntityTemplate>> loadEntityTemplates(const std::string& path);
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
     *      "entities":[
     *      {"physics_entity":{
     *          "attributes":
     *          {
     *              "position":"0.0f,0.0f", "velocity":"0.0f,0.0f", "acceleration":"0.0f,0.0f"
     *          }
     *      }},
     *      {"enemy":{
     *          "inherits" : ["physics_entity"]
     *          ,
     *          "attributes":
     *          {
     *              "health":""
     *          }
     *      }},
     *      {"player":{
     *          "inherits" : ["physics_entity"]
     *          ,
     *          "attributes":
     *          {
     *              "health":"100", "jump_strength":"1.0f", "position":"50.0f, 60.0f"
     *          }
     *      }}]
     *  }
     *  @endcode
     *  The file is divided into entity template definitions. The three entities defined in this files are "physics_entity", "enemy" and "player". Every entity template internally defines a sequence of attributes that they should have and/or which other entity templates they inherit. The attributes might come with default values. For instance, the first attribute of the entity template "player" is "health" with a default value of "100".
     *
     *  If a template inherits another template, it means that the inheriting template will obtain all attributes and default values from the inherited templates. Inheriting templates can override default values by restating the attributes like the template "player" does in the above example with the "position" attribute.
     ***
     *  @fn std::vector<std::pair<std::string, EntityTemplate> > JsonEntityLoader::loadEntityTemplates(const std::string& path)
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
