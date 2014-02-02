#include <featherkit/entity/entity.h>

namespace fea
{
    Entity::Entity(EntityId i, EntityManager& d) : id(i), entityDatabase(d)
    {
    }

    bool Entity::hasAttribute(const std::string& attribute) const
    {
        return entityDatabase.hasAttribute(id, attribute);
    }
    
    EntityId Entity::getId() const
    {
        return id;
    }
}
