#pragma once
#include <stack>
#include <unordered_map>
#include <memory>
#include <vector>
#include <typeindex>

namespace fea
{
    class EntityStorage
    {
        class StorageEntity
        {
            public:
                StorageEntity(const std::vector<std::string>& attributeList, EntityStorage& p);
                template<class DataType>
                void setData(const std::string& identifier, const DataType& inData);
                template<class DataType>
                DataType getData(const std::string& identifier) const;
                bool hasData(const std::string& identifier) const;
            private:
                EntityStorage& parent;
                std::unordered_map<std::string, std::shared_ptr<char> > attributeData;
        };

        public:
        EntityStorage();
        uint32_t addEntity(const std::vector<std::string>& attributeList);
        template<class DataType>
        void registerAttribute(const std::string& identifier);
        template<class DataType>
        void setData(const uint32_t id, const std::string& identifier, const DataType& inData);
        template<class DataType>
        DataType getData(const uint32_t id, const std::string& identifier) const;
        bool hasData(const uint32_t id, const std::string& identifier) const;
        bool attributeIsValid(const std::string& identifier) const;
        void clear();

        std::unordered_map<std::string, std::type_index> attributes;
        std::unordered_map<uint32_t, StorageEntity> entities;
        std::stack<uint32_t> freeIds;
        uint32_t nextId;
    };
}
