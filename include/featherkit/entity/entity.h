#pragma once
#include <featherkit/entity/entitymanager.h>

namespace fea
{
    class Entity
    {
        public:
            Entity(EntityId id, EntityManager& entityManager);
            template<class DataType>
            DataType getAttribute(const std::string& attribute) const;
            template<class DataType>
            void setAttribute(const std::string& attribute, const DataType& value) const;
            template<class DataType>
            void addToAttribute(const std::string& attribute, const DataType& value) const;
            bool hasAttribute(const std::string& attribute) const;
            EntityId getId() const;
        private:
            EntityId mId;
            EntityManager& mEntityManager;
    };

    template<class DataType>
    DataType Entity::getAttribute(const std::string& attribute) const
    {
        FEA_ASSERT(!mEntityManager.findEntity(mId).expired(), "Trying to set the attribute '" + attribute + "' on entity ID '" + std::to_string(mId) + "' which has previously been deleted!");
        return mEntityManager.getAttribute<DataType>(mId, attribute);
    }

    template<class DataType>
    void Entity::setAttribute(const std::string& attribute, const DataType& value) const
    {
        mEntityManager.setAttribute<DataType>(mId, attribute, value);
    }

    template<class DataType>
    void Entity::addToAttribute(const std::string& attribute, const DataType& value) const
    {
        mEntityManager.addToAttribute<DataType>(mId, attribute, value);
    }

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
     *  @fn DataType Entity::getAttribute(const std::string& attribute) const
     *  @brief Get the value of an attribute of the entity.
     *
     *  Assert/undefined behaviour when the attribute does not exist or the wrong template argument is provided.
     *  @tparam Type of the attribute to get.
     *  @param attribute Name of the attribute to get.
     *  @return Attribute value.
     ***
     *  @fn void Entity::setAttribute(const std::string& attribute, DataType value) const
     *  @brief Set the value of an attribute of the entity.
     *
     *  Assert/undefined behaviour when the attribute does not exist or the wrong template argument is provided.
     *  @tparam Type of the attribute to set.
     *  @param attribute Name of the attribute to set.
     *  @param value Value to set the attribute to.
     ***
     *  @fn void Entity::addToAttribute(const std::string& attribute, DataType value) const
     *  @brief Add the given value to an attribute of the entity.
     *
     *  The given value will be added to the already existing value. Needs the operator+ function to be implemented for the target type.
     *  Assert/undefined behaviour when the attribute does not exist or the wrong template argument is provided.
     *
     *  @tparam Type of the attribute to add to.
     *  @param attribute Name of the attribute to add to.
     *  @param value Value to add to the attribute.
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
     ***/
}
