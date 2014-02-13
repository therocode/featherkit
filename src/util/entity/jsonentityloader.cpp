#include <featherkit/util/entity/jsonentityloader.h>
#include <featherkit/json/json_reader.h>
#include <fstream>
#include <sstream>

namespace fea
{
    namespace util
    {
        std::unordered_map<std::string, EntityTemplate> JsonEntityLoader::loadEntityTemplates(const std::string& path)
        {
            std::unordered_map<std::string, EntityTemplate> result;

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
                std::string entityName = temp.name;
                std::size_t attributeAmount = temp.value.GetNumMembers();

                EntityTemplate entityTemplate;
                for(unsigned int j = 0; j < attributeAmount; j++)
                {
                    json::Member attributesObject = temp.value.GetMember(j);
                    entityTemplate.emplace(attributesObject.name, attributesObject.value.GetString());
                }
                result.emplace(entityName, entityTemplate);
            }
            return result;
        }
    }
}
