#include <featherkit/entity/entitystorage.h>

namespace fea
{
    EntityStorage::StorageEntity::StorageEntity(const std::vector<std::string>& attributeList)
    {
        for(const auto& attribute : attributeList)
            attributeData.emplace(attribute, std::shared_ptr<void>());
    }

    bool EntityStorage::StorageEntity::hasData(const std::string& attribute) const
    {
        return attributeData.find(attribute) != attributeData.end();
    }


    EntityStorage::EntityStorage() : mNextId(0)
    {
    }

    uint32_t EntityStorage::addEntity(const std::vector<std::string>& attributeList)
    {
        uint32_t newId;

        if(mFreeIds.size() != 0)
        {
            newId = mFreeIds.top();
            mFreeIds.pop();
        }
        else
        {
            newId = mNextId;
            mNextId++;
        }

        mEntities.emplace(newId, StorageEntity(attributeList));
        return newId;
    }
    
    void EntityStorage::removeEntity(uint32_t id)
    {
        mEntities.erase(id);
        mFreeIds.push(id);
    }

    bool EntityStorage::hasData(const uint32_t id, const std::string& attribute) const
    {
        try
        {
            return mEntities.at(id).hasData(attribute); 
        }
        catch(std::out_of_range)
        {
            throw EntityException("Error! Trying to check if entity ID '" + std::to_string(id) + "' has the attribute '" + attribute + "' but that entity does not exist!\n");
        }
    }

    bool EntityStorage::attributeIsValid(const std::string& attribute) const
    {
        return mAttributes.find(attribute) != mAttributes.end();
    }

    void EntityStorage::clear()
    {
        mAttributes.clear();
        mEntities.clear();
        mFreeIds = std::stack<uint32_t>();
        mNextId = 0;
    }
}
