#pragma once
#include <stdexcept>
#include <string>

namespace fea
{
    class InvalidAttributeException : public std::runtime_error 
    {
        public:
            InvalidAttributeException(const std::string& message, const std::string& attribute);
            std::string mAttribute;
    };

    class EntityException : public std::runtime_error 
    {
        public:
            EntityException(const std::string& message);
    };
    /** @addtogroup EntitySystem
     *@{
     *  @class InvalidAttributeException
     *
     *  @class EntityException
     *@}
     ***/
}
