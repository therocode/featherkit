#include <featherkit/entity/entity.hpp>

namespace fea
{
    Entity::Entity(EntityId id, EntityManager& entityManager) : mId(id), mEntityManager(entityManager)
    {
    }

    bool Entity::hasAttribute(const std::string& attribute) const
    {
        return mEntityManager.hasAttribute(mId, attribute);
    }
    
    EntityId Entity::getId() const
    {
        return mId;
    }
    
    std::unordered_set<std::string> Entity::getAttributes() const
    {
        return mEntityManager.getAttributes(mId);
    }
}
