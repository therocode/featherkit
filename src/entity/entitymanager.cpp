#include <framework/entity/entitymanager.h>
#include <framework/entity/entityexceptions.h>
#include <framework/entity/entity.h>
#include <framework/entity/entitygroup.h>
#include <sstream>
#include <iostream>

namespace windgale
{
    EntityManager::EntityManager(EntityBackend* b) : backend(b)
    {
    }

    WeakEntityPtr EntityManager::createEntity(const EntityType& type)
    {
        if(entityTypes.find(type) == entityTypes.end())
        {
            std::stringstream ss;
            ss << "Error! Entity type '" << type << "' does not exist!\n";
            throw(EntityException(ss.str()));
        }
        EntityId createdId = backend->addEntity(entityTypes.at(type).attributeList);
        EntityPtr created = std::make_shared<Entity>(createdId, *this);
        entities.insert(std::pair<EntityId, EntityPtr>(createdId, created));

        
        if(!entityTypes.at(type).defaultStrings.empty())
        {
            for(const auto& pair : entityTypes.at(type).defaultStrings)
            {
                if(defaultSetters.find(pair.first) == defaultSetters.end())
                {
                    std::stringstream ss; 
                    ss << "Error! Default value '" << pair.second << "' given to attribute '" << pair.first << "' but no default setter function registered!\n";
                    throw(EntityException(ss.str()));
                }
                else
                {
                    std::vector<std::string> parameters;
                    std::stringstream splitter(pair.second);
                    std::string parameter;
                    while(std::getline(splitter, parameter, ','))
                        parameters.push_back(parameter);
                    defaultSetters.at(pair.first)(pair.first, parameters, WeakEntityPtr(created));
                }
            }
        }
        //std::cout << "created entity " << createdId << " of type " << type << "\n";
        return WeakEntityPtr(created);
    }

    WeakEntityPtr EntityManager::getEntity(EntityId id) const
    {
        return entities.at(id);
    }
    
    void EntityManager::removeEntity(const EntityId id)
    {
        backend->removeEntity(id);
        entities.erase(id);
    }
    
    void EntityManager::removeEntities(const EntityGroup group)
    {
        for(auto entity : group.getSet())
            removeEntity(entity.lock()->getId());
    }

    void EntityManager::registerAttribute(const std::string& attribute, const int size)
    {
        std::hash<std::string> hasher;
        backend->registerAttribute(hasher(attribute), size);
    }

    void EntityManager::registerAttributes(const std::map<std::string, int>& attributes)
    {
        std::hash<std::string> hasher;
        for(const auto& pair : attributes)
        {
            backend->registerAttribute(hasher(pair.first), pair.second);
        }
    }

    void EntityManager::registerEntityType(const EntityType& type, const std::map<std::string, std::string>& attributes)
    {
        std::hash<std::string> hasher;
        if(entityTypes.find(type) == entityTypes.end())
        {
            EntityTypeData tempData;

            for(const auto& pair : attributes)
            {
                tempData.attributeList.addAttribute(hasher(pair.first));


                if(pair.second != "")
                    tempData.defaultStrings.insert(std::pair<std::string, std::string>(pair.first, pair.second));
            }
            entityTypes.insert(std::pair<EntityType, EntityTypeData>(type, tempData));
        }
        else
        {
            std::stringstream ss;
            ss << "Error! Entity type '" << type << "' already exist!\n";
            throw(EntityException(ss.str()));
        }
    }

    void EntityManager::registerEntityTypes(const std::map<EntityType, std::map<std::string, std::string> > types)
    {
        for(const auto& pair : types)
        {
            registerEntityType(pair.first, pair.second);
        }
    }
    
    void EntityManager::registerDefaultSetter(std::string attribute, std::function<void(std::string, std::vector<std::string>&, WeakEntityPtr)> defaultFunc)
    {
        std::hash<std::string> hasher;
        if(backend->attributeIsValid(hasher(attribute)))
        {
            defaultSetters.insert(std::pair<std::string, std::function<void(std::string, std::vector<std::string>&, WeakEntityPtr)> >(attribute, defaultFunc));
        }
        else
        {
            std::stringstream ss;
            ss << "Error! Cannot register default function for attribute '" << attribute << "' since it isn't valid!\n";
            throw(EntityException(ss.str()));
        }
    }

    EntityGroup EntityManager::getAll() const
    {
        EntityGroup all;
        for(const auto& pair : entities)
            all.add(pair.second);
        return all;
    }
    
    bool EntityManager::hasAttribute(const std::string& attribute, const EntityId id) const
    {
        std::hash<std::string> hasher;
        return backend->hasData(hasher(attribute), id);
    }

    void EntityManager::removeAll()
    {
        while(entities.size() > 0)
            removeEntity(entities.begin()->first);
    }

    void EntityManager::reset()
    {
        entities.clear();
        entityTypes.clear();
        defaultSetters.clear();
        backend->clear();
    }
}
