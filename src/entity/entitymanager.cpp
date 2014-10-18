#include <fea/entity/entitymanager.hpp>
#include <fea/entity/entity.hpp>
#include <sstream>

namespace fea
{
    WeakEntityPtr EntityManager::createEntity(const std::set<std::string>& attributes)
    {
        EntityId createdId = mStorage.addEntity(attributes);
        EntityPtr created = std::make_shared<Entity>(createdId, *this);
        mEntities.insert(std::pair<EntityId, EntityPtr>(createdId, created));
        return WeakEntityPtr(created);
    }

    WeakEntityPtr EntityManager::findEntity(EntityId id) const
    {
        auto iterator = mEntities.find(id);

        if(iterator != mEntities.end())
        {
            return iterator->second;
        }
        else    
        {
            return WeakEntityPtr();
        }
    }
    
    void EntityManager::removeEntity(const EntityId id)
    {
        FEA_ASSERT(mEntities.find(id) != mEntities.end(), "Trying to delete entity ID '" + std::to_string(id) + "' but it doesn't exist!");
        mStorage.removeEntity(id);
        mEntities.erase(id);
    }
    
    bool EntityManager::hasAttribute(const EntityId id, const std::string& attribute) const
    {
        FEA_ASSERT(mEntities.find(id) != mEntities.end(), "Trying to check if entity ID '" + std::to_string(id) + "' has attribute '" + attribute + "' but that entity doesn't exist!");
        return mStorage.hasData(id, attribute);
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
    
    std::unordered_set<std::string> EntityManager::getAttributes(EntityId id) const
    {
        FEA_ASSERT(mEntities.find(id) != mEntities.end(), "Trying to get the attributes of entity entity ID '" + std::to_string(id) + "' but such an entity doesn't exist!");
        return mStorage.getAttributes(id);
    }
}
