#pragma once
#include <featherkit/entity/entitymanager.h>

namespace fk
{
    class Entity
    {
        public:
            Entity(EntityId i, EntityManager& m);
            template<class DataType>
            bool getAttributeSafe(const std::string& attribute, DataType* outData) const;
            template<class DataType>
            bool setAttributeSafe(const std::string& attribute, const DataType* inData) const;
            template<class DataType>
            bool modifyAttributeSafe(const std::string& attribute, const DataType* inData) const;
            template<class DataType>
            DataType getAttribute(const std::string& attribute) const;
            template<class DataType>
            void setAttribute(const std::string& attribute, DataType value) const;
            template<class DataType>
            void modifyAttribute(const std::string& attribute, DataType value) const;
            bool hasAttribute(const std::string& attribute) const;
            EntityId getId() const;
        private:
            EntityId id;
            EntityManager& entityManager;
    };

    template<class DataType>
    bool Entity::getAttributeSafe(const std::string& attribute, DataType* outData) const
    {
        if(entityManager.hasAttribute(attribute, id))
        {
            entityManager.getAttribute<DataType>(attribute, id, outData);
            return true;
        }
        return false;
    }

    template<class DataType>
    bool Entity::setAttributeSafe(const std::string& attribute, const DataType* inData) const
    {
        if(entityManager.hasAttribute(attribute, id))
        {
            entityManager.setAttribute<DataType>(attribute, id, inData);
            return true;
        }
        return false;
    }

    template<class DataType>
    bool Entity::modifyAttributeSafe(const std::string& attribute, const DataType* inData) const
    {
        if(entityManager.hasAttribute(attribute, id))
        {
            entityManager.modifyAttribute<DataType>(attribute, id, inData);
            return true;
        }
        return false;
    }

    template<class DataType>
    DataType Entity::getAttribute(const std::string& attribute) const
    {
        DataType result;
        entityManager.getAttribute<DataType>(attribute, id, &result);
        return result;
    }

    template<class DataType>
    void Entity::setAttribute(const std::string& attribute, DataType value) const
    {
        entityManager.setAttribute<DataType>(attribute, id, &value);
    }

    template<class DataType>
    void Entity::modifyAttribute(const std::string& attribute, DataType value) const
    {
        entityManager.modifyAttribute<DataType>(attribute, id, &value);
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
     *  @fn bool Entity::getAttributeSafe(const std::string& attribute, DataType* outData) const
     *  @brief Retrieve the value of an attribute of the Entity in a safe way.
     *
     *  As opposed to Entity::getAttribute, this function will not throw an exception when the requested attribute does not exist. Instead the function returns false and the return value is undefined.
     *
     *  @tparam Type of the attribute to get.
     *  @param attribute Name of the attribute to get.
     *  @param outData Pointer to a variable in which to store the return value.
     *  @return True if the requested attribute existed. Otherwise false.
     ***
     *  @fn bool Entity::setAttributeSafe(const std::string& attribute, DataType* inData)
     *  @brief Set the value of an attribute of the Entity in a safe way.
     *
     *  As opposed to Entity::setAttribute, this function will not throw an exception when the requested attribute does not exist. Instead the function returns false and no attribute is modified.
     *
     *  @tparam Type of the attribute to set.
     *  @param attribute Name of the attribute to set.
     *  @param inData Pointer to a variable containing the new value of the attribute.
     *  @return True if the specified attribute existed. Otherwise false.
     ***
     *  @fn bool Entity::modifyAttributeSafe(const std::string& attribute, DataType* inData)
     *  @brief Modify the value of an attribute of the Entity in a safe way.
     *
     *  The given value will be added to the already existing value. Needs the operator+ function to be implemented for the target type.
     *
     *  As opposed to Entity::modifyAttribute, this function will not throw an exception when the requested attribute does not exist. Instead the function returns false and no attribute is modified.
     *
     *  @tparam Type of the attribute to modify.
     *  @param attribute Name of the attribute to modify.
     *  @param inData Pointer to a variable containing the value to add to the attribute.
     *  @return True if the specified attribute existed. Otherwise false.
     ***
     *  @fn DataType Entity::getAttribute(const std::string& attribute) const
     *  @brief Get the value of an attribute of the entity.
     *
     *  If the given attribute does not exist, this function will cause an InvalidAttributeException to be thrown. For a safe way to get attributes, see Entity::getAttributeSafe.
     *  
     *  @tparam Type of the attribute to get.
     *  @param attribute Name of the attribute to get.
     *  @return Attribute value.
     ***
     *  @fn void Entity::setAttribute(const std::string& attribute, DataType value) const
     *  @brief Set the value of an attribute of the entity.
     *
     *  If the given attribute does not exist, this function will cause an InvalidAttributeException to be thrown. For a safe way to set attributes, see Entity::setAttributeSafe.
     *  
     *  @tparam Type of the attribute to set.
     *  @param attribute Name of the attribute to set.
     *  @param value Value to set the attribute to.
     ***
     *  @fn void Entity::modifyAttribute(const std::string& attribute, DataType value) const
     *  @brief Modify the value of an attribute of the entity.
     *
     *  The given value will be added to the already existing value. Needs the operator+ function to be implemented for the target type.
     *
     *  If the given attribute does not exist, this function will cause an InvalidAttributeException to be thrown. For a safe way to set attributes, see Entity::setAttributeSafe.
     *  
     *  @tparam Type of the attribute to modify.
     *  @param attribute Name of the attribute to modify.
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
