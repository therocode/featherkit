#include <fea/entity/entitycontroller.hpp>

namespace fea
{
    void EntityController::entityCreated(EntityPtr entity)
    {
        if(keepEntity(entity))
        {
            entityKept(entity);
            mEntities.emplace(entity->getId(), entity);
        }
    }
    
    void EntityController::entityRemoved(EntityId entityId)
    {
        if(mEntities.find(entityId) != mEntities.end())
        {
            entityDestroyed(mEntities.at(entityId));
            mEntities.erase(entityId);
        }
    }
    
    bool EntityController::keepEntity(EntityPtr entity) const
    {
        return false;
    }
            
    void EntityController::entityKept(EntityPtr entity)
    {
    }

    void EntityController::entityDestroyed(EntityPtr entity)
    {
    }

    const std::unordered_map<EntityId, EntityPtr>& EntityController::getEntities() const
    {
        return mEntities;
    }
    
    EntityController::~EntityController()
    {
    }
}
