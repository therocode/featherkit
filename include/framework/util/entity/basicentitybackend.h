#pragma once
#include <framework/entity/entitybackend.h>
#include <stack>
#include <unordered_map>
#include <memory>

using namespace fk;

namespace fku
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
            private:
                BasicEntityBackend& parent;
                std::unordered_map<AttributeHash, std::shared_ptr<char> > attributeData;
        };

        public:
            BasicEntityBackend();
            EntityId addEntity(AttributeList attributeList) override;
            void removeEntity(const EntityId id) override;
            void registerAttribute(const AttributeHash identifier, const ElementSize elementSize) override;
            void setData(const AttributeHash identifier, const EntityId id, const char* inData) override;
            void getData(const AttributeHash identifier, const EntityId id, char* outData) const override;
            bool hasData(const AttributeHash identifier, const EntityId id) const override;
            bool attributeIsValid(AttributeHash identifier) const override;
            void clear() override;
            ~BasicEntityBackend();
        private:
            std::unordered_map<AttributeHash, ElementSize> attributes;
            std::unordered_map<EntityId, BasicBackendEntity> entities;
            std::stack<EntityId> freeEntityIds;
            uint32_t nextEntityId;
    };
    /** @addtogroup EntitySystem
     *@{
     *  @class BasicEntityBackend
     *@}
     ***
     *  @class BasicEntityBackend
     *  @brief Basic implementation of an EntityBackend.
     *
     *  This basic implementation is appropriate for most situations where there are not any special needs or demands on the entity system. It implements Entity data storage using std::unordered_map instances that get gradually filled as Entity instances are added. It has no functions in addition to the ones overriden from the EntityBackend base class.
     ***
     *  @fn virtual int BasicEntityBackend::addEntity(AttributeList attributeList)
     *  @brief Create a new Entity with the attributes from the given AttributeList.
     *  @param attributeList The attributes the Entity should have.
     ***
     *  @fn virtual void BasicEntityBackend::removeEntity(const int id)
     *  @brief Remove an Entity stored in the BasicEntityBackend.
     *
     *  This should throw an EntityException if the given Entity does not exist.
     *  @param id Entity to remove.
     ***
     *  @fn virtual void BasicEntityBackend::registerAttribute(const AttributeHash identifier, const ElementSize elementSize)
     *  @brief Register an attribute with the given size in bytes.
     *  @param identifier Hash unique to this attribute.
     *  @param elementSize Memory size in bytes.
     ***
     *  @fn virtual void BasicEntityBackend::setData(const AttributeHash identifier, const int id, const char* inData)
     *  @brief Set attribute data of an Entity.
     *  
     *  Should throw an InvalidAttributeException if the attribute does not exist.
     *  @param identifier Hash representing the attribute to set.
     *  @param id ID of the Entity to set the attribute for.
     *  @param inData Pointer to a variable holding the value to set.
     ***
     *  @fn virtual void BasicEntityBackend::getData(const AttributeHash identifier, const int id, const char* outData)
     *  @brief Get attribute data of an Entity.
     *
     *  Should throw an InvalidAttributeException if the attribute does not exist.
     *  @param identifier Hash representing the attribute to get.
     *  @param id ID of the Entity to get the attribute for.
     *  @param outData Pointer to a variable holding the value to get.
     ***
     *  @fn virtual bool BasicEntityBackend::hasData(const AttributeHash identifier, const int id) const
     *  @brief Check if a certain Entity has an attribute.
     *
     *  Should throw an InvalidAttributeException if the attribute does not exist.
     *  @param identifier Hash representing the attribute to check for.
     *  @param id ID of the Entity to check the attribute for.
     *  @return True if the attribute exists, otherwise false.
     ***
     *  @fn virtual bool BasicEntityBackend::attributeIsValid(AttributeHash identifier) const
     *  @brief Check if a certain attribute is registered.
     *  @param identifier Hash representing the attribute to check.
     *  @return True if the attribute is registered, otherwise false.
     ***
     *  @fn virtual void BasicEntityBackend::clear()
     *  @brief Removes all Entity instances currently stored in the BasicEntityBackend.
     ***/
}
