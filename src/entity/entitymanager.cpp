#include <featherkit/entity/entitymanager.h>
#include <featherkit/entity/entityexceptions.h>
#include <featherkit/entity/entity.h>
#include <sstream>

namespace fea
{
    WeakEntityPtr EntityManager::createEntity(const std::vector<std::string>& attributes)
    {
        EntityId createdId = storage.addEntity(attributes);
        EntityPtr created = std::make_shared<Entity>(createdId, *this);
        entities.insert(std::pair<EntityId, EntityPtr>(createdId, created));
        return WeakEntityPtr(created);
    }

    WeakEntityPtr EntityManager::getEntity(EntityId id) const
    {
        return entities.at(id);
    }
    
    void EntityManager::removeEntity(const EntityId id)
    {
        //dataStorage->removeEntity(id);
        entities.erase(id);
    }
    
    bool EntityManager::attributeIsValid(const std::string& attributeName) const
    {
        return storage.attributeIsValid(attributeName);
    }

    EntitySet EntityManager::getAll() const
    {
        EntitySet all;
        for(const auto& pair : entities)
            all.insert(pair.second);
        return all;
    }
    
    bool EntityManager::hasAttribute(const EntityId id, const std::string& attribute) const
    {
        return storage.hasData(id, attribute);
    }

    void EntityManager::removeAll()
    {
        while(entities.size() > 0)
            removeEntity(entities.begin()->first);
    }

    void EntityManager::clear()
    {
        entities.clear();
        storage.clear();
    }
}
