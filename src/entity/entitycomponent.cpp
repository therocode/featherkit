#include <featherkit/entity/entitycomponent.h>

namespace fea
{
    void EntityComponent::entityCreated(WeakEntityPtr entity)
    {
        if(keepEntity(entity))
            mEntities.insert(entity);
    }
    
    void EntityComponent::entityRemoved(EntityId entityId)
    {
        for(const auto entity : mEntities)
        {
            if(entity.lock()->getId() == entityId)
                mEntities.erase(entity);
        }
    }
    
    bool EntityComponent::keepEntity(WeakEntityPtr entity) const
    {
        return false;
    }

    const std::set<WeakEntityPtr, std::owner_less<WeakEntityPtr>>& EntityComponent::getEntities() const
    {
        return mEntities;
    }
    
    EntityComponent::~EntityComponent()
    {
    }
}
