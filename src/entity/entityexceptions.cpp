#include <featherkit/entity/entityexceptions.h>

namespace fea
{
    InvalidIdException::InvalidIdException(const std::string& message) : std::runtime_error(message)
    {
    }

    InvalidAttributeException::InvalidAttributeException(const std::string& m, const std::string& n) : std::runtime_error(m), name(n) 
    {
    }
    
    EntityException::EntityException(const std::string& message) : std::runtime_error(message)
    {
    }
}
