#include "entity.h"

namespace windgale
{
    bool Entity::hasAttribute(const std::string& attribute)
    {
        return entityManager.hasAttribute(attribute, id);
    }
    
    EntityId Entity::getId()
    {
        return id;
    }
}
