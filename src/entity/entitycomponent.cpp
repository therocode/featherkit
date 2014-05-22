#include <fea/entity/entitycomponent.hpp>

namespace fea
{
    void EntityComponent::entityCreated(WeakEntityPtr entity)
    {
        if(keepEntity(entity))
        {
            entityKept(entity);
            mEntities.emplace(entity.lock()->getId(), entity);
        }
    }
    
    void EntityComponent::entityRemoved(EntityId entityId)
    {
        if(mEntities.find(entityId) != mEntities.end())
        {
            entityDropped(mEntities.at(entityId));
            mEntities.erase(entityId);
        }
    }
    
    bool EntityComponent::keepEntity(WeakEntityPtr entity) const
    {
        return false;
    }
            
    void EntityComponent::entityKept(WeakEntityPtr entity)
    {
    }

    void EntityComponent::entityDropped(WeakEntityPtr entity)
    {
    }

    const std::unordered_map<EntityId, WeakEntityPtr>& EntityComponent::getEntities() const
    {
        return mEntities;
    }
    
    EntityComponent::~EntityComponent()
    {
    }
}
