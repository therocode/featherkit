#pragma once
#include <stdexcept>

namespace fk
{
    using AttributeHash = std::size_t;

    class InvalidIdException : public std::runtime_error 
    {
        public:
            InvalidIdException(const std::string& message);
    };

    class InvalidAttributeException : public std::runtime_error 
    {
        public:
            InvalidAttributeException(const std::string& m, const AttributeHash h);
            AttributeHash hash;
    };

    class EntityException : public std::runtime_error 
    {
        public:
            EntityException(const std::string& message);
    };
    /** @addtogroup EntitySystem
     *@{
     *  @class InvalidIdException
     *  
     *  @class InvalidAttributeException
     *
     *  @class EntityException
     *@}
     ***
     *  @class InvalidIdException
     *  @brief Exception used by the Entity System when something related to EntityId handling goes wrong.
     ***
     *  @fn InvalidIdException::InvalidIdException(const std::string& message)
     *  @brief Construct an exception to throw containing a message.
     *  @param message Message further describing the error.
     ***
     *  @class InvalidAttributeException
     *  @brief Exception used by the Entity System when something related to attribute handling goes wrong.
     ***
     *  @fn InvalidAttributeException::InvalidAttributeException
     *  @brief Construct an exception to throw containing a message.
     *  @param m Message further describing the error.
     *  @param h AttributeHash describing which attribute the error is related to.
     ***
     *  @var InvalidAttributeException::hash 
     *  @brief The AttributeHash given to the constructor will be stored here.
     ***
     *  @class EntityException
     *  @brief Exception used by the Entity System when something goes wrong.
     ***
     *  @fn EntityException::EntityException(const std::string& message)
     *  @brief Construct an exception to throw containing a message.
     *  @param message Message further describing the error.
     ***/
}
