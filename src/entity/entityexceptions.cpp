#include <featherkit/entity/entityexceptions.h>

namespace fea
{
    InvalidAttributeException::InvalidAttributeException(const std::string& message, const std::string& attribute) : std::runtime_error(message), mAttribute(attribute) 
    {
    }
    
    EntityException::EntityException(const std::string& message) : std::runtime_error(message)
    {
    }
}
