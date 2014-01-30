#include <featherkit/entity/entity.h>

namespace fea
{
    Entity::Entity(EntityId i, EntityManager& d) : id(i), entityDatabase(d)
    {
    }

    bool Entity::hasAttribute(const std::string& attribute) const
    {
        return entityDatabase.hasAttribute(attribute, id);
    }
    
    EntityId Entity::getId() const
    {
        return id;
    }
}
