#pragma once
#include "framework/entity/entitybackend.h"
#include <stack>
#include <unordered_map>

namespace windgale
{
    class BasicEntityBackend : public EntityBackend
    {
        class BasicBackendEntity
        {
            public:
                BasicBackendEntity(AttributeList attributeList, BasicEntityBackend& p);
                void setData(const AttributeHash identifier, const char* inData);
                void getData(const AttributeHash identifier, char* outData) const;
                bool hasData(const AttributeHash identifier) const;
                void kill();
            private:
                BasicEntityBackend& parent;
                std::unordered_map<AttributeHash, char*> attributeData;
        };

        public:
            BasicEntityBackend();
            int addEntity(AttributeList attributeList) override;
            void removeEntity(const int id) override;
            void registerAttribute(const AttributeHash identifier, const ElementSize elementSize) override;
            void setData(const AttributeHash identifier, const int id, const char* inData) override;
            void getData(const AttributeHash identifier, const int id, char* outData) const override;
            bool hasData(const AttributeHash identifier, const int id) const override;
            bool attributeIsValid(AttributeHash identifier) override;
            void clear() override;
            ~BasicEntityBackend();
        private:
            std::unordered_map<AttributeHash, ElementSize> attributes;
            std::unordered_map<EntityId, BasicBackendEntity> entities;
            std::stack<int> freeEntityIds;
            uint32_t nextEntityId;
    };
}
