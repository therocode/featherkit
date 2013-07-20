#include <framework/util/entity/basicentitybackend.h>
#include <framework/entity/entityexceptions.h>
#include <sstream>
#include <cstring>

namespace fku
{
    BasicEntityBackend::BasicBackendEntity::BasicBackendEntity(AttributeList attributeLists, BasicEntityBackend& p) : parent(p)
    {
        for(auto attribute : attributeLists.getSet())
        {
            attributeData.insert(std::pair<AttributeHash, std::shared_ptr<char> >(attribute, std::shared_ptr<char>(new char[parent.attributes.at(attribute)], [](char* arr) { delete [] arr;} )));
        }
    }
    
    void BasicEntityBackend::BasicBackendEntity::setData(const AttributeHash identifier, const char* inData)
    {
        try
        {
            memcpy(attributeData.at(identifier).get(), inData, (uint32_t) parent.attributes.at(identifier));
        }
        catch(std::out_of_range)
        {
            std::stringstream ss;
            ss << "Error! The given attribute '" << identifier << "' does not exist!\n";
            throw InvalidAttributeException(ss.str(), identifier);
        }
    }

    void BasicEntityBackend::BasicBackendEntity::getData(const AttributeHash identifier, char* outData) const
    {
        try
        {
            memcpy(outData, attributeData.at(identifier).get(), (uint32_t) parent.attributes.at(identifier));
        }
        catch(std::out_of_range)
        {
            std::stringstream ss;
            ss << "Error! The given attribute '" << identifier << "' does not exist!\n";
            throw InvalidAttributeException(ss.str(), identifier);
        }
    }

    bool BasicEntityBackend::BasicBackendEntity::hasData(const AttributeHash identifier) const
    {
        return attributeData.find(identifier) != attributeData.end();
    }
    
    BasicEntityBackend::BasicEntityBackend()
    {
        nextEntityId = 0;
    }
    
    EntityId BasicEntityBackend::addEntity(AttributeList attributeList)
    {
        if(attributeList.size() > 0)
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

    bool BasicEntityBackend::attributeIsValid(AttributeHash identifier) const
    {
        return(attributes.find(identifier) != attributes.end());
    }
    
    void BasicEntityBackend::clear()
    {
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
