#include <featherkit/entity/entity.h>

namespace fk
{
    Entity::Entity(EntityId i, EntityManager& m) : id(i), entityManager(m)
    {
    }

    bool Entity::hasAttribute(const std::string& attribute) const
    {
        return entityManager.hasAttribute(attribute, id);
    }
    
    EntityId Entity::getId() const
    {
        return id;
    }
}
