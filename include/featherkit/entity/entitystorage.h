#pragma once
#include <stack>
#include <unordered_map>
#include <memory>
#include <set>
#include <typeindex>
#include <featherkit/entity/entityexceptions.h>
#include <featherkit/assert.h>

namespace fea
{
    class EntityStorage
    {
        class StorageEntity
        {
            public:
                StorageEntity(const std::set<std::string>& attributeList);
                template<class DataType>
                void setData(const std::string& attribute, const DataType& inData);
                template<class DataType>
                DataType getData(const std::string& attribute) const;
                bool hasData(const std::string& attribute) const;
            private:
                std::unordered_map<std::string, std::shared_ptr<void>> attributeData;
        };

        public:
        EntityStorage();
        uint32_t addEntity(const std::set<std::string>& attributeList);
        void removeEntity(uint32_t id);
        template<class DataType>
        void registerAttribute(const std::string& attribute);
        template<class DataType>
        void setData(const uint32_t id, const std::string& attribute, const DataType& inData);
        template<class DataType>
        DataType getData(const uint32_t id, const std::string& attribute) const;
        bool hasData(const uint32_t id, const std::string& attribute) const;
        bool attributeIsValid(const std::string& attribute) const;
        void clear();

        std::unordered_map<std::string, std::type_index> mAttributes;
        std::unordered_map<uint32_t, StorageEntity> mEntities;
        std::stack<uint32_t> mFreeIds;
        uint32_t mNextId;
    };
    
    template<class DataType>
    void EntityStorage::StorageEntity::setData(const std::string& attribute, const DataType& inData)
    {
        FEA_ASSERT(attributeData.find(attribute) != attributeData.end(), "Trying to set the attribute '" + attribute + "' on an entity which does not have said attribute!");
        auto& valuePointer = attributeData.at(attribute);

        if(!valuePointer)
            valuePointer = std::make_shared<DataType>(inData);
        else
            *std::static_pointer_cast<DataType>(valuePointer) = inData;
    }

    template<class DataType>
    DataType EntityStorage::StorageEntity::getData(const std::string& attribute) const
    {
        FEA_ASSERT(attributeData.find(attribute) != attributeData.end(), "Trying to get the attribute '" + attribute + "' on an entity which does not have said attribute!");
        auto& valuePointer = attributeData.at(attribute);

        FEA_ASSERT(valuePointer, "Calling getData on attribute '" + attribute + "' which is not initialised!");
        return *std::static_pointer_cast<DataType>(valuePointer);
    }

    template<class DataType>
    void EntityStorage::registerAttribute(const std::string& attribute)
    {
        FEA_ASSERT(mAttributes.find(attribute) == mAttributes.end(), "Trying to register attribute '" + attribute + "' as a '"  + std::type_index(typeid(DataType)).name() + std::string(" but there is already an attribute registered with that identifier!"));
        mAttributes.emplace(attribute, typeid(DataType));
    }

    template<class DataType>
    void EntityStorage::setData(const uint32_t id, const std::string& attribute, const DataType& inData)
    {
        FEA_ASSERT(mAttributes.find(attribute) != mAttributes.end(), "Trying to set the attribute '" + attribute + "' on an entity but such an attribute has not been registered!");
        FEA_ASSERT(std::type_index(typeid(DataType)) == mAttributes.at(attribute), "Trying to set attibute '" + attribute + "' as a '" + std::type_index(typeid(DataType)).name() + std::string(" but it is of type '") + std::string(mAttributes.at(attribute).name()) + "'");
        mEntities.at(id).setData(attribute, inData);
    }

    template<class DataType>
    DataType EntityStorage::getData(const uint32_t id, const std::string& attribute) const
    {
        FEA_ASSERT(mAttributes.find(attribute) != mAttributes.end(), "Trying to get the attribute '" + attribute + "' on an entity but such an attribute has not been registered!");
        FEA_ASSERT(std::type_index(typeid(DataType)) == mAttributes.at(attribute), "Trying to get attibute '" + attribute + "' as a '" + std::type_index(typeid(DataType)).name() + std::string(" but it is of type '") + std::string(mAttributes.at(attribute).name()) + "'");
        return mEntities.at(id).getData<DataType>(attribute);
    }
}
