#include <featherkit/entity/entitystorage.h>

namespace fea
{
    EntityStorage::StorageEntity::StorageEntity(const std::set<std::string>& attributeList)
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

    uint32_t EntityStorage::addEntity(const std::set<std::string>& attributeList)
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

        for(auto& attribute : attributeList)
            FEA_ASSERT(mAttributes.find(attribute) != mAttributes.end(), "Trying to create an entity with the attribute '" + attribute + "' which is invalid!");

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
        return mEntities.at(id).hasData(attribute); 
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
