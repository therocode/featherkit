#include <featherkit/entity/entitymanager.h>
#include <featherkit/entity/entityexceptions.h>
#include <featherkit/entity/entity.h>
#include <sstream>

namespace fea
{
    WeakEntityPtr EntityManager::createEntity(const std::vector<std::string>& attributes)
    {
        EntityId createdId = mStorage.addEntity(attributes);
        EntityPtr created = std::make_shared<Entity>(createdId, *this);
        mEntities.insert(std::pair<EntityId, EntityPtr>(createdId, created));
        return WeakEntityPtr(created);
    }

    WeakEntityPtr EntityManager::findEntity(EntityId id) const
    {
        try
        {
            return mEntities.at(id);
        }
        catch(std::out_of_range e)
        {
            return WeakEntityPtr();
        }
    }
    
    void EntityManager::removeEntity(const EntityId id)
    {
        mStorage.removeEntity(id);
        mEntities.erase(id);
    }
    
    bool EntityManager::attributeIsValid(const std::string& attributeName) const
    {
        return mStorage.attributeIsValid(attributeName);
    }

    EntitySet EntityManager::getAll() const
    {
        EntitySet all;
        for(const auto& pair : mEntities)
            all.insert(pair.second);
        return all;
    }
    
    bool EntityManager::hasAttribute(const EntityId id, const std::string& attribute) const
    {
        return mStorage.hasData(id, attribute);
    }

    void EntityManager::removeAll()
    {
        while(mEntities.size() > 0)
            removeEntity(mEntities.begin()->first);
    }

    void EntityManager::clear()
    {
        mEntities.clear();
        mStorage.clear();
    }
}
