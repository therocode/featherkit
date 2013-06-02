#include <framework/util/entity/jsonentityloader.h>
#include <framework/json/json_reader.h>
#include <fstream>
#include <sstream>

namespace windgale
{
    std::map<std::string, int> JsonEntityLoader::loadAttributesJson(const std::string& path)
    {
        std::map<std::string, int> result;

        std::ifstream file(path);
        
        if(!file)
        {
            std::stringstream ss;
            ss << "Error! Attribute file not found: " << path << "\n";
            throw FileNotFoundException(ss.str());
        }

        json::Value root;
        root.SetObject();
        json::read(file, root);

        std::size_t attributeAmount = root.GetNumMembers();
        for(unsigned int i = 0; i < attributeAmount; i++)
        {
            json::Member temp = root.GetMember(i);
            std::string typeName = temp.name;
            std::string sizeString = temp.value.GetString();
            int typeSize = 0;

            if(sizeString == "#float#")
                typeSize = sizeof(float);
            else if(sizeString == "#double#")
                typeSize = sizeof(double);
            else if(sizeString == "#int32#")
                typeSize = sizeof(int32_t);
            else if(sizeString == "#uint32#")
                typeSize = sizeof(uint32_t);
            else if(sizeString == "#bool#")
                typeSize = sizeof(bool);
            else if(sizeString == "#byte#" || sizeString == "#char#")
                typeSize = sizeof(char);
            else
                typeSize = std::stoi(sizeString);

            result.insert(std::pair<std::string, int>(typeName, typeSize));
        }

        return result;
    }
    
    std::map<std::string, std::map<std::string, std::string> > JsonEntityLoader::loadEntitiesJson(const std::string& path)
    {
        std::map<std::string, std::map<std::string, std::string> > result;

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
            
            std::map<std::string, std::string> attributes;
            for(unsigned int j = 0; j < attributeAmount; j++)
            {
                json::Member attributesObject = temp.value.GetMember(j);
                attributes.insert(std::pair<std::string, std::string>(attributesObject.name, attributesObject.value.GetString()));
            }
            result.insert(std::pair<std::string, std::map<std::string, std::string> >(entityName, attributes));
        }
        return result;
    }
}
