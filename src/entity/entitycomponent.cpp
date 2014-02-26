#include <featherkit/entity/entitycomponent.h>

namespace fea
{
    void EntityComponent::entityCreated(WeakEntityPtr entity)
    {
        if(keepEntity(entity))
            mEntities.emplace(entity.lock()->getId(), entity);
    }
    
    void EntityComponent::entityRemoved(EntityId entityId)
    {
        if(mEntities.find(entityId) != mEntities.end())
            mEntities.erase(entityId);
    }
    
    bool EntityComponent::keepEntity(WeakEntityPtr entity) const
    {
        return false;
    }

    const std::unordered_map<EntityId, WeakEntityPtr>& EntityComponent::getEntities() const
    {
        return mEntities;
    }
    
    EntityComponent::~EntityComponent()
    {
    }
}
