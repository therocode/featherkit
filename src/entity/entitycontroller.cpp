#include <fea/entity/entitycontroller.hpp>

namespace fea
{
    void EntityController::entityCreated(WeakEntityPtr entity)
    {
        if(keepEntity(entity))
        {
            entityKept(entity);
            mEntities.emplace(entity.lock()->getId(), entity);
        }
    }
    
    void EntityController::entityRemoved(EntityId entityId)
    {
        if(mEntities.find(entityId) != mEntities.end())
        {
            entityDropped(mEntities.at(entityId));
            mEntities.erase(entityId);
        }
    }
    
    bool EntityController::keepEntity(WeakEntityPtr entity) const
    {
        return false;
    }
            
    void EntityController::entityKept(WeakEntityPtr entity)
    {
    }

    void EntityController::entityDropped(WeakEntityPtr entity)
    {
    }

    const std::unordered_map<EntityId, WeakEntityPtr>& EntityController::getEntities() const
    {
        return mEntities;
    }
    
    EntityController::~EntityController()
    {
    }
}
