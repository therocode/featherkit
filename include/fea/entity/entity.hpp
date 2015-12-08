#pragma once
#include <fea/config.hpp>
#include <fea/entity/entitymanager.hpp>

namespace fea
{
    class FEA_API Entity
    {
        public:
            Entity(EntityId id, EntityManager& entityManager);
            template<class DataType>
            const DataType& getAttribute(const std::string& attribute) const;
            template<class DataType>
            DataType& getAttribute(const std::string& attribute);
            template<class DataType>
            void setAttribute(const std::string& attribute, DataType value) const;
            bool hasAttribute(const std::string& attribute) const;
            EntityId getId() const;
            std::unordered_set<std::string> getAttributes() const;
        private:
            EntityId mId;
            EntityManager& mEntityManager;
    };
#include <fea/entity/entity.inl>
    /** @addtogroup EntitySystem
     *@{
     *  @class Entity
     *@}
     ***
     *  @class Entity
     *  @brief Represents a single game entity.
     *
     *  A game entity is no more than a collection of attributes, associated with the same entity ID. An attribute is a named value of any type. An example of an attribute would be an int named "health points" storing the value 23. An entity may have an arbitrary amount of attributes and every entity has a unique entity ID. 
     *
     *  Although usage may vary and is not restricted, the entities are meant to be used for ingame objects that need to store data. These could include the player, enemies, pickups, bullets, and so on.
     ***
     *  @fn Entity::Entity(EntityId i, EntityManager& m)
     *  @brief Construct an Entity. 
     *
     *  This sets the EntityId to the supplied ID. The entity stores the EntityManager reference internally for using when getting and setting attributes.
     *
     *  Observe that entities aren't mean to be created manually, but using the EntityManager::CreateEntity function.
     *  @param i ID of the new entity.
     *  @param m EntityManager that the entity will use.
     ***
     *  @fn const DataType& Entity::getAttribute(const std::string& attribute) const
     *  @brief Get the value of an attribute of the entity.
     *
     *  Assert/undefined behavior when the attribute does not exist or the wrong template argument is provided.
     *  @tparam Type of the attribute to get.
     *  @param attribute Name of the attribute to get.
     *  @return Attribute value.
     ***
     *  @fn DataType& Entity::getAttribute(const std::string& attribute)
     *  @brief Get the value of an attribute of the entity.
     *
     *  Assert/undefined behavior when the attribute does not exist or the wrong template argument is provided.
     *  @tparam Type of the attribute to get.
     *  @param attribute Name of the attribute to get.
     *  @return Attribute value.
     ***
     *  @fn void Entity::setAttribute(const std::string& attribute, DataType value) const
     *  @brief Set the value of an attribute of the entity.
     *
     *  Assert/undefined behavior when the attribute does not exist or the wrong template argument is provided.
     *  @tparam Type of the attribute to set.
     *  @param attribute Name of the attribute to set.
     *  @param value Value to set the attribute to.
     ***
     *  @fn bool Entity::hasAttribute(const std::string& attribute) const
     *  @brief Check if the entity has an attribute.
     *
     *  @param attribute Name of the attribute to check.
     *  @return True if the attribute exists.
     ***
     *  @fn EntityId Entity::getId() const
     *  @brief Get the ID of an entity.
     *  @return The ID.
     ***
     *  @fn std::unordered_set<std::string> Entity::getAttributes() const
     *  @brief Get a set containing all the attributes of the entity.
     *
     *  Assert/undefined behavior if the entity does not exist.
     *  @return Set with attributes.
     ***/
}
