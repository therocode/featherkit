#include <framework/entity/entitygroup.h>
#include <algorithm>

namespace windgale
{
    void EntityGroup::add(const WeakEntityPtr entity)
    {
        entities.insert(entity);
    }

    void EntityGroup::add(const EntityGroup& other)
    {
        entities.insert(other.entities.begin(), other.entities.end());
    }

    void EntityGroup::remove(const WeakEntityPtr entity)
    {
        entities.erase(entity);
    }

    void EntityGroup::remove(const EntityGroup& other)
    {
        entities.erase(other.entities.begin(), other.entities.end());
    }

    void EntityGroup::clear()
    {
        entities.clear();
    }

    EntityGroup EntityGroup::operator+(const EntityGroup& other) const
    {
        EntityGroup newGroup;
        newGroup.entities.insert(entities.begin(), entities.end());
        newGroup.entities.insert(other.entities.begin(), other.entities.end());
        return newGroup;
    }
    
    EntityGroup EntityGroup::operator+(const WeakEntityPtr& entity) const
    {
        EntityGroup newGroup;
        newGroup.entities = entities;
        newGroup.entities.insert(entity);
        return newGroup;
    }

    EntityGroup EntityGroup::operator-(const EntityGroup& other) const
    {
        EntityGroup newGroup;
        std::set_difference(entities.begin(), entities.end(), other.entities.begin(), other.entities.end(), std::inserter(newGroup.entities, newGroup.entities.end()), std::owner_less<WeakEntityPtr>());
        return newGroup;
    }
    
    EntityGroup EntityGroup::operator-(const WeakEntityPtr& entity) const
    {
        EntityGroup newGroup;
        newGroup.entities = entities;
        newGroup.entities.erase(entity);
        return newGroup;
    }
    
    const EntitySet& EntityGroup::getSet() const
    {
        return entities;
    }

    size_t EntityGroup::size()
    {
        return entities.size();
    }

    EntityGroup EntityGroup::applyFilter(std::function<bool(WeakEntityPtr)> filterFunc)
    {
        EntityGroup newGroup;

        for(auto entity : entities)
        {
            if(filterFunc(entity))
                newGroup.add(entity);
        }

        return newGroup;
    }

    void EntityGroup::removeInvalid()
    {
        auto iter = entities.begin();
        while(iter != entities.end())
        {
            if(iter->expired())
                iter = entities.erase(iter);
            else
                iter++;
        }
    }
}
