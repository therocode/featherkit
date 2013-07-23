#pragma once
#include <map>
#include <unordered_map>
#include <string>
#include <featherkit/util/filenotfoundexception.h>

namespace fea
{
    namespace util
    {
        class JsonEntityLoader
        {
            public:
                JsonEntityLoader();
                std::map<std::string, int> loadAttributesJson(const std::string& path);
                std::map<std::string, std::map<std::string, std::string> > loadEntitiesJson(const std::string& path);
                void registerType(std::string type, uint32_t size);
            private:
                std::unordered_map<std::string, uint32_t> registeredTypes;
        };
        /** @addtogroup EntitySystem
         *@{
         *  @class FileNotFoundException
         *
         *  @class JsonEntityLoader
         *@}
         ***
         *  @class FileNotFoundException
         *  @brief Exception used when a file is not found.
         ***
         *  @fn FileNotFoundException::FileNotFoundException()
         *  @brief Construct a FileNotFoundException instance to throw.
         ***
         *  @fn FileNotFoundException::FileNotFoundException(std::string msg)
         *  @brief Construct a FileNotFoundException instance to throw.
         *  @param msg Message further explaining the error.
         ***
         *  @class JsonEntityLoader
         *  @brief This class is for loading json files describing attribute and Entity types.
         *
         *  The output of the loading functions of this class can directly be passed to the EntityManager to register the attribute and Entity types. To register attributes, pass the output of JsonEntityLoader::loadAttributesJson into EntityManager::registerAttributes and to register Entity types, pass the output of JsonEntityLoader::loadEntitiesJson into EntityManager::registerEntityTypes. The attribute types must be loaded before the Entity types.
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
         *  It is also possible to have special data type tags instead of numbers. These tags directly correspond to sizes of C++ data types. Here is a list of the data type tags and the C++ types they correspond to that are added from the start. More types can be added using the JsonEntityLoader::registerEntityTypes function.
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
            ***
            *  @fn void JsonEntityLoader::registerType(std::string type, uint32_t size)
            *  @brief Register a data type so that it can be used in the loaded file.
            *  @param type String with the type name to register. The convention of the default types is that the names should be surrounded by ##.
            *  @param size Size in bytes of the data type. A good idea is to use the result of the sizeof operator.
            **/
    }
}
