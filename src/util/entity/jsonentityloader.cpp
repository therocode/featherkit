#include <featherkit/util/entity/jsonentityloader.hpp>
#include <featherkit/json/json_reader.h>
#include <fstream>
#include <sstream>

namespace fea
{
    namespace util
    {
        std::vector<std::pair<std::string, EntityTemplate>> JsonEntityLoader::loadEntityTemplates(const std::string& path)
        {
            std::vector<std::pair<std::string, EntityTemplate>> result;

            std::ifstream file(path);

            if(!file)
            {
                std::stringstream ss;
                ss << "Error! Entity file not found: " << path << "\n";
                throw FileNotFoundException(ss.str());
            }

            json::Value root;
            root.SetObject();
            json::read(file, root);
            json::Value main = root.GetMember(0).value;

            size_t entityTypeAmount = main.GetNumElements();
            for(unsigned int i = 0; i < entityTypeAmount; i++)
            {
                EntityTemplate entityTemplate;
                json::Member temp = main.GetElement(i).GetMember(0);
                std::string entityName = temp.name;

                if(temp.value.HasMember("inherits"))
                {
                    json::Value parents = temp.value.GetArrayMember("inherits");

                    for(unsigned int j = 0; j < parents.GetNumElements(); j++)
                    {
                        entityTemplate.mInherits.push_back(parents.GetElement(j).GetString());
                    }
                }

                size_t attributeAmount = temp.value.GetObjectMember("attributes").GetNumMembers();

                for(unsigned int j = 0; j < attributeAmount; j++)
                {
                    json::Member attributesObject = temp.value.GetObjectMember("attributes").GetMember(j);
                    entityTemplate.mAttributes.emplace(attributesObject.name, attributesObject.value.GetString());
                }
                result.push_back({entityName, entityTemplate});
            }
            return result;
        }
        
        std::unordered_map<std::string, std::string> JsonEntityLoader::loadEntityAttributes(const std::string& path)
        {
            std::unordered_map<std::string, std::string> result;

            std::ifstream file(path);

            if(!file)
            {
                std::stringstream ss;
                ss << "Error! Entity file not found: " << path << "\n";
                throw FileNotFoundException(ss.str());
            }

            json::Value root;
            root.SetObject();
            json::read(file, root);

            std::size_t entityTypeAmount = root.GetNumMembers();
            for(unsigned int i = 0; i < entityTypeAmount; i++)
            {
                json::Member temp = root.GetMember(i);
                result.emplace(temp.name, temp.value.GetString());
            }

            return result;
        }
    }
}
