#include <fea/entity/jsonentityloader.hpp>
#include <fstream>
#include <json/reader.h>

namespace fea
{
    std::unordered_map<std::string, std::string> JsonEntityLoader::jsonObjToStringMap(const Json::Value& obj)
    {
        std::unordered_map<std::string, std::string> result;

        for(const std::string& attribute : obj.getMemberNames())
            result.emplace(attribute, obj[attribute].asString());

        return result;
    }

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

        const Json::Value& entities = root["entities"];
        if(entities.isArray())
        {
            for(const Json::Value& entity : entities)
            {
                EntityTemplate entityTemplate;

                std::string entityName = entity["name"].asString();

                const Json::Value& parents = entity["inherits"];
                if(parents.isArray())
                {
                    for(const Json::Value& parent : parents)
                        entityTemplate.mInherits.push_back(parent.asString());
                }

                entityTemplate.mAttributes = jsonObjToStringMap(entity["attributes"]);

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
        file.close();

        return jsonObjToStringMap(root);
    }
}
