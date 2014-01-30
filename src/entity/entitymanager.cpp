#include <featherkit/entity/entitymanager.h>
#include <featherkit/entity/entityexceptions.h>
#include <featherkit/entity/entity.h>
#include <sstream>

namespace fea
{
    WeakEntityPtr EntityManager::createEntity(const EntityTemplate& temp)
    {
        if(entityTemplates.find(temp) == entityTemplates.end())
        {
            std::stringstream ss;
            ss << "Error! Entity template '" << temp << "' does not exist!\n";
            throw(EntityException(ss.str()));
        }
        EntityId createdId;// = dataStorage->addEntity(entityTemplates.at(temp).attributeSet);
        EntityPtr created = std::make_shared<Entity>(createdId, *this);
        entities.insert(std::pair<EntityId, EntityPtr>(createdId, created));

        
        if(!entityTemplates.at(temp).defaultStrings.empty())
        {
            for(const auto& pair : entityTemplates.at(temp).defaultStrings)
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
    
    void EntityManager::removeEntities(const EntitySet group)
    {
        for(auto entity : group)
            removeEntity(entity.lock()->getId());
    }

    void EntityManager::registerAttribute(const std::string& attribute, const uint32_t size)
    {
        std::hash<std::string> hasher;
        //dataStorage->registerAttribute(hasher(attribute), size);
    }

    void EntityManager::registerAttributes(const std::map<std::string, uint32_t>& attributes)
    {
        std::hash<std::string> hasher;
        for(const auto& pair : attributes)
        {
            //dataStorage->registerAttribute(hasher(pair.first), pair.second);
        }
    }

    void EntityManager::registerEntityTemplate(const EntityTemplate& temp, const std::map<std::string, std::string>& attributes)
    {
        std::hash<std::string> hasher;
        if(entityTemplates.find(temp) == entityTemplates.end())
        {
            EntityTemplateData tempData;

            for(const auto& pair : attributes)
            {
                tempData.attributeSet.insert(hasher(pair.first));


                if(pair.second != "")
                    tempData.defaultStrings.insert(std::pair<std::string, std::string>(pair.first, pair.second));
            }
            entityTemplates.insert(std::pair<EntityTemplate, EntityTemplateData>(temp, tempData));
        }
        else
        {
            std::stringstream ss;
            ss << "Error! Entity template '" << temp << "' already exist!\n";
            throw(EntityException(ss.str()));
        }
    }

    void EntityManager::registerEntityTemplates(const std::map<EntityTemplate, std::map<std::string, std::string> > templates)
    {
        for(const auto& pair : templates)
        {
            registerEntityTemplate(pair.first, pair.second);
        }
    }
    
    void EntityManager::registerDefaultSetter(std::string attribute, std::function<void(std::string, std::vector<std::string>&, WeakEntityPtr)> defaultFunc)
    {
        std::hash<std::string> hasher;
        //if(dataStorage->attributeIsValid(hasher(attribute)))
        //{
        //    defaultSetters.insert(std::pair<std::string, std::function<void(std::string, std::vector<std::string>&, WeakEntityPtr)> >(attribute, defaultFunc));
        //}
        //else
        //{
        //    std::stringstream ss;
        //    ss << "Error! Cannot register default function for attribute '" << attribute << "' since it isn't valid!\n";
        //    throw(EntityException(ss.str()));
        //}
    }

    EntitySet EntityManager::getAll() const
    {
        EntitySet all;
        for(const auto& pair : entities)
            all.insert(pair.second);
        return all;
    }
    
    bool EntityManager::hasAttribute(const std::string& attribute, const EntityId id) const
    {
        std::hash<std::string> hasher;
        return true;//dataStorage->hasData(hasher(attribute), id);
    }

    void EntityManager::removeAll()
    {
        while(entities.size() > 0)
            removeEntity(entities.begin()->first);
    }

    void EntityManager::reset()
    {
        entities.clear();
        entityTemplates.clear();
        defaultSetters.clear();
        //dataStorage->clear();
    }
}
