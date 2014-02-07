#pragma once
#include <stack>
#include <unordered_map>
#include <memory>
#include <vector>
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
                StorageEntity(const std::vector<std::string>& attributeList);
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
        uint32_t addEntity(const std::vector<std::string>& attributeList);
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
        try
        {
            auto& valuePointer = attributeData.at(attribute);

            if(!valuePointer)
                valuePointer = std::make_shared<DataType>(inData);
            else
                *std::static_pointer_cast<DataType>(valuePointer) = inData;
        }
        catch(std::out_of_range)
        {
            throw InvalidAttributeException("","");
        }
    }

    template<class DataType>
    DataType EntityStorage::StorageEntity::getData(const std::string& attribute) const
    {
        try
        {
            auto& valuePointer = attributeData.at(attribute);

            FEA_ASSERT(valuePointer, "Calling getData on attribute '" + attribute + "' which is not initialised!");
            return *std::static_pointer_cast<DataType>(valuePointer);
        }
        catch(std::out_of_range)
        {
            throw InvalidAttributeException("","");
        }
    }

    template<class DataType>
    void EntityStorage::registerAttribute(const std::string& attribute)
    {
        if(mAttributes.find(attribute) == mAttributes.end())
        {
            mAttributes.emplace(attribute, typeid(DataType));
        }
        else
        {
            throw EntityException("");
        }
    }

    template<class DataType>
    void EntityStorage::setData(const uint32_t id, const std::string& attribute, const DataType& inData)
    {
        try
        {
            FEA_ASSERT(std::type_index(typeid(DataType)) == mAttributes.at(attribute), "Trying to set attibute '" + attribute + "' as a '" + std::type_index(typeid(DataType)).name() + std::string(" but it is of type '") + std::string(mAttributes.at(attribute).name()) + "'");
            mEntities.at(id).setData(attribute, inData);
        }
        catch(std::out_of_range)
        {
            throw EntityException("");
        }
    }

    template<class DataType>
    DataType EntityStorage::getData(const uint32_t id, const std::string& attribute) const
    {
        try
        {
            FEA_ASSERT(std::type_index(typeid(DataType)) == mAttributes.at(attribute), "Trying to get attibute '" + attribute + "' as a '" + std::type_index(typeid(DataType)).name() + std::string(" but it is of type '") + std::string(mAttributes.at(attribute).name()) + "'");
            return mEntities.at(id).getData<DataType>(attribute);
        }
        catch(std::out_of_range)
        {
            throw EntityException("");
        }
    }
}
