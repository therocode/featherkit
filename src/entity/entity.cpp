#include "framework/entity/entity.h"

namespace windgale
{
    bool Entity::hasAttribute(const std::string& attribute) const
    {
        return entityManager.hasAttribute(attribute, id);
    }
    
    EntityId Entity::getId() const
    {
        return id;
    }
}
