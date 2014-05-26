#pragma once
#include <fea/config.hpp>

namespace fea
{
    class EntityFactory;

    namespace util
    {
        void FEA_API addBasicDataTypes(EntityFactory& factory);

        /** @addtogroup EntitySystem
         *@{
         *  @fn void addBasicDataTypes(EntityFactory& factory)
         *  @brief Register basic data types to use with the EntityFactory.
         *  
         *  All types registered provide a parser for setting default values.
         *
         *  There are a few categories of the types registered by this function.
         *
         *  <b>Floating point types</b>
         *  - "float"
         *  - "double"
         *  
         *  The parser for floating point types follows the convention of std::stof and std::stod.
         *
         *  <b>Integer types</b>
         *  - "int8"
         *  - "uint8"
         *  - "int16"
         *  - "uint16"
         *  - "int32"
         *  - "uint32"
         *  - "int64"
         *  - "uint64"
         *
         *  The parser for integer types follows the convention of the std string-to-int parsing functions (std::stoi and the like) with additional range checks.
         *
         *  <b>Other types</b>
         *  - "bool"
         *  - "string"
         *  - "entityptr"
         *
         *  The parser for the bool type allows only the exact string "true" or "false".
         *
         *  The string type corresponds to std::string and the parser accepts any string.
         *
         *  entityptr represents a fea::WeakEntityPtr instance and can be used to store a pointer to an instance of fea::Entity. The parser accepts a name for another entity template. If a name for another template is provided, that entity template will be instantiated and pointed to by the entityptr attribute.
         *@}
         ***/
    }
}
