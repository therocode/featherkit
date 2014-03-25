#pragma once
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <set>
#include <typeindex>
#include <featherkit/assert.hpp>

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
                std::unordered_set<std::string> getAttributes() const;
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
        std::unordered_set<std::string> getAttributes(uint32_t id) const;

        std::unordered_map<std::string, std::type_index> mAttributes;
        std::unordered_map<uint32_t, StorageEntity> mEntities;
        std::stack<uint32_t> mFreeIds;
        uint32_t mNextId;
    };
#include <featherkit/entity/entitystorage.inl>
}
