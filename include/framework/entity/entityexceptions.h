#pragma once
#include <stdexcept>

namespace windgale
{
    using AttributeHash = std::size_t;

    class InvalidIdException : public std::runtime_error 
    {
        public:
            InvalidIdException(const std::string& message) 
                : std::runtime_error(message) { };
    };

    class InvalidAttributeException : public std::runtime_error 
    {
        public:
            InvalidAttributeException(const std::string& m, const AttributeHash h) 
                : std::runtime_error(m), hash(h) { };
            AttributeHash hash;
    };
    /** @addtogroup EntitySystem
     *@{
     *  @class InvalidIdException
     *  
     *  @class InvalidAttributeException
     *@}
     ***
     *  @class InvalidIdException
     *  @brief Exception used by the Entity System when something related to EntityId handling goes wrong.
     *
     *  @fn InvalidIdException::InvalidIdException(const std::string& message)
     *  @brief Construct an exception to throw containing a message.
     *  @param message Message further describing the error.
     ***
     *  @class InvalidAttributeException
     *  @brief Exception used by the Entity System when something related to attribute handling goes wrong.
     *
     *  @fn InvalidAttributeException::InvalidAttributeException
     *  @param message Message further describing the error.
     ***/
}
