#include <fea/entity/jsonentityloader.hpp>
#include <fstream>
#include <json/reader.h>
#include <json/value.h>

namespace fea
{
    std::vector<std::pair<std::string, EntityTemplate>> JsonEntityLoader::loadEntityTemplates(const std::string& path)
    {
        std::ifstream file(path);

        if(!file)
            throw FileNotFoundException("Error! Entity file not found: " + path + '\n');

        Json::Value root;
        Json::Reader reader;

        reader.parse(file, root, false);
        file.close();

        std::vector<std::pair<std::string, EntityTemplate>> result;

        Json::Value entities = root["entities"];
        if(entities.isArray())
        {
            for(const Json::Value& entity : entities)
            {
                EntityTemplate entityTemplate;

                std::string entityName = entity.getMemberNames().front();
                Json::Value entityData = entity[entityName];

                Json::Value parents = entityData["inherits"];
                if(parents.isArray())
                {
                    for(Json::Value& parent : parents)
                        entityTemplate.mInherits.push_back(parent.asString());
                }

                Json::Value attributes = entityData["attributes"];
                if(attributes.isObject())
                {
                    for(const std::string& a : attributes.getMemberNames())
                        entityTemplate.mAttributes.emplace(a, attributes[a].asString());
                }

                result.emplace_back(entityName, entityTemplate);
            }
        }
        return result;
    }
    
    std::unordered_map<std::string, std::string> JsonEntityLoader::loadEntityAttributes(const std::string& path)
    {
        std::ifstream file(path);

        if(!file)
            throw FileNotFoundException("Error! Entity file not found: " + path + '\n');

        Json::Value root;
        Json::Reader reader;

        reader.parse(file, root, false);

        std::unordered_map<std::string, std::string> result;

        for(const std::string& attribute : root.getMemberNames())
            result.emplace(attribute, root[attribute].asString());

        return result;
    }
}
