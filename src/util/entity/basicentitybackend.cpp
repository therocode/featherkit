#include "framework/util/entity/basicentitybackend.h"
#include "framework/entity/entityexceptions.h"
#include <sstream>
#include <cstring>

namespace windgale
{
    BasicEntityBackend::BasicBackendEntity::BasicBackendEntity(AttributeList attributeLists, BasicEntityBackend& p) : parent(p)
    {
        for(auto attribute : attributeLists.getSet())
        {
            attributeData.insert(std::pair<AttributeHash, char*>(attribute, new char[parent.attributes.at(attribute)]));
        }
    }
    
    void BasicEntityBackend::BasicBackendEntity::setData(const AttributeHash identifier, const char* inData)
    {
        memcpy(attributeData.at(identifier), inData, (uint32_t) parent.attributes.at(identifier));
    }

    void BasicEntityBackend::BasicBackendEntity::getData(const AttributeHash identifier, char* outData) const
    {
        memcpy(outData, attributeData.at(identifier), (uint32_t) parent.attributes.at(identifier));
    }

    bool BasicEntityBackend::BasicBackendEntity::hasData(const AttributeHash identifier) const
    {
        return attributeData.find(identifier) != attributeData.end();
    }
    
    void BasicEntityBackend::BasicBackendEntity::kill()
    {
       for(auto data : attributeData)
           delete [] data.second; 
    }
    
    BasicEntityBackend::BasicEntityBackend()
    {
        nextEntityId = 0;
    }
    
    EntityId BasicEntityBackend::addEntity(AttributeList attributeList)
    {
        if(attributeList.getSize() > 0)
        {
            for(auto attribute : attributeList.getSet())
            {
                if(attributes.find(attribute) == attributes.end())
                {
                    throw InvalidAttributeException("Error! Invalid attribute given: ", attribute);
                }
            }

            int createdId;
            if(freeEntityIds.size() > 0)
            {
                createdId = freeEntityIds.top();
                freeEntityIds.pop();
            }
            else
            {
                createdId = nextEntityId;
                nextEntityId++;
            }

            entities.insert(std::pair<EntityId, BasicBackendEntity>(createdId, BasicBackendEntity(attributeList, *this)));
            return createdId;
        }
        else
        {
            throw InvalidAttributeException("Error! Zero attributes given!", 0);
        }

        return -1;
    }

    void BasicEntityBackend::removeEntity(const EntityId id)
    {
        if(entities.find(id) == entities.end())
        {
            std::stringstream ss;
            ss << "Error! Cannot remove entity number " << id << "! It is not a valid entity!\n";
            throw InvalidIdException(ss.str());
        }

        freeEntityIds.push(id);

        entities.at(id).kill();
        entities.erase(id);
    }

    void BasicEntityBackend::registerAttribute(const AttributeHash identifier, const ElementSize elementSize)
    {
        if(attributes.find(identifier) != attributes.end())
        {
            std::stringstream ss;
            ss << "Error! Attribute " << identifier << " is already added!\n";
            throw InvalidAttributeException(ss.str(), identifier);
        }
        attributes.insert(std::pair<AttributeHash, ElementSize>(identifier, elementSize));
    }
            
    void BasicEntityBackend::setData(const AttributeHash identifier, const EntityId id, const char* inData)
    {
        entities.at(id).setData(identifier, inData);
    }

    void BasicEntityBackend::getData(const AttributeHash identifier, const EntityId id, char* outData) const
    {
        entities.at(id).getData(identifier, outData);
    }

    bool BasicEntityBackend::hasData(const AttributeHash identifier, const EntityId id) const
    {
        return entities.at(id).hasData(identifier);
    }

    bool BasicEntityBackend::attributeIsValid(AttributeHash identifier)
    {
        return(attributes.find(identifier) != attributes.end());
    }
    
    void BasicEntityBackend::clear()
    {
        for(auto entity : entities)
        {
            entity.second.kill();
        }

       attributes.clear();
       entities.clear();
       freeEntityIds = std::stack<EntityId>();
       nextEntityId = 0;
    }
    
    BasicEntityBackend::~BasicEntityBackend()
    {
        clear();
    }
}
