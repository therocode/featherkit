#pragma once
#include <featherkit/entity/attributelist.h>
#include <stdint.h>

namespace fk
{
    using EntityId = uint32_t;
    using ElementSize = uint32_t;
    using AttributeHash = std::size_t;

    class EntityBackend
    {
            public:
                virtual EntityId addEntity(AttributeList attributeList) = 0;
                virtual void removeEntity(const EntityId id) = 0;
                virtual void registerAttribute(const AttributeHash identifier, const ElementSize elementSize) = 0;
                virtual void setData(const AttributeHash identifier, const EntityId id, const char* inData) = 0;
                virtual void getData(const AttributeHash identifier, const EntityId id, char* outData) const = 0;
                virtual bool hasData(const AttributeHash identifier, const EntityId id) const = 0;
                virtual bool attributeIsValid(AttributeHash identifier) const = 0;
                virtual void clear() = 0;
    };
    /** @addtogroup EntitySystem
     *@{
     *  @class EntityBackend
     *@}
     ***
     *  @class EntityBackend
     *  @brief Abstract base class for various EntityBackend implementations.
     *
     *  The EntityBackend serves as a storage unit for the EntityManager which won't function without one. With different implementations, it is possible to specialise how Entity data should be stored which may be needed when tailoring the Entity system for your needs.
     ***
     *  @fn virtual int EntityBackend::addEntity(AttributeList attributeList) = 0
     *  @brief Create a new Entity with the attributes from the given AttributeList.
     *  @param attributeList The attributes the Entity should have.
     ***
     *  @fn virtual void EntityBackend::removeEntity(const int id) = 0
     *  @brief Remove an Entity stored in the EntityBackend.
     *
     *  This should throw an EntityException if the given Entity does not exist.
     *  @param id Entity to remove.
     ***
     *  @fn virtual void EntityBackend::registerAttribute(const AttributeHash identifier, const ElementSize elementSize) = 0
     *  @brief Register an attribute with the given size in bytes.
     *  @param identifier Hash unique to this attribute.
     *  @param elementSize Memory size in bytes.
     ***
     *  @fn virtual void EntityBackend::setData(const AttributeHash identifier, const int id, const char* inData) = 0
     *  @brief Set attribute data of an Entity.
     *  
     *  Should throw an InvalidAttributeException if the attribute does not exist.
     *  @param identifier Hash representing the attribute to set.
     *  @param id ID of the Entity to set the attribute for.
     *  @param inData Pointer to a variable holding the value to set.
     ***
     *  @fn virtual void EntityBackend::getData(const AttributeHash identifier, const int id, const char* outData) = 0
     *  @brief Get attribute data of an Entity.
     *
     *  Should throw an InvalidAttributeException if the attribute does not exist.
     *  @param identifier Hash representing the attribute to get.
     *  @param id ID of the Entity to get the attribute for.
     *  @param outData Pointer to a variable holding the value to get.
     ***
     *  @fn virtual bool EntityBackend::hasData(const AttributeHash identifier, const int id) const = 0
     *  @brief Check if a certain Entity has an attribute.
     *
     *  Should throw an InvalidAttributeException if the attribute does not exist.
     *  @param identifier Hash representing the attribute to check for.
     *  @param id ID of the Entity to check the attribute for.
     *  @return True if the attribute exists, otherwise false.
     ***
     *  @fn virtual bool EntityBackend::attributeIsValid(AttributeHash identifier) const = 0
     *  @brief Check if a certain attribute is registered.
     *  @param identifier Hash representing the attribute to check.
     *  @return True if the attribute is registered, otherwise false.
     ***
     *  @fn virtual void EntityBackend::clear() = 0
     *  @brief Removes all Entity instances currently stored in the EntityBackend.
     ***/
}
