#pragma once
#include <featherkit/entity/entitystorage.h>
#include <memory>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <stdint.h>
#include <set>

namespace fea
{
    class Entity;

    using EntityPtr = std::shared_ptr<Entity>;
    using WeakEntityPtr = std::weak_ptr<Entity>;
    using EntityId = uint32_t;
    using EntitySet = std::set<WeakEntityPtr, std::owner_less<WeakEntityPtr>>;

    class EntityManager
    {
        public:
            WeakEntityPtr createEntity(const std::set<std::string>& attributes);
            WeakEntityPtr findEntity(EntityId id) const;
            void removeEntity(const EntityId id);
            template<class DataType>
            DataType getAttribute(const EntityId id, const std::string& attribute) const;
            template<class DataType>
            void setAttribute(const EntityId id, const std::string& attribute, const DataType& attributeData);
            template<class DataType>
            void addToAttribute(const EntityId id, const std::string& attribute, const DataType& attributeData);
            bool hasAttribute(const EntityId id, const std::string& attribute) const;
            template<class DataType>
            void registerAttribute(const std::string& attributeName);
            bool attributeIsValid(const std::string& attributeName) const;
            EntitySet getAll() const;
            void removeAll();
            void clear();
        private:
            std::unordered_map<EntityId, EntityPtr> mEntities;
            EntityStorage mStorage;
    };

    template<class DataType>
    DataType EntityManager::getAttribute(const EntityId id, const std::string& attribute) const
    {
        FEA_ASSERT(mEntities.find(id) != mEntities.end(), "Trying to get the attribute '" + attribute + "' on entity entity ID '" + std::to_string(id) + "' but such an entity doesn't exist!");

        return mStorage.getData<DataType>(id, attribute);
    }

    template<class DataType>
    void EntityManager::setAttribute(const EntityId id, const std::string& attribute, const DataType& attributeData)
    {
        FEA_ASSERT(mEntities.find(id) != mEntities.end(), "Trying to get the attribute '" + attribute + "' on entity entity ID '" + std::to_string(id) + "' but such an entity doesn't exist!");
        mStorage.setData(id, attribute, attributeData);
    }

    template<class DataType>
    void EntityManager::addToAttribute(const EntityId id, const std::string& attribute, const DataType& attributeData)
    {
        FEA_ASSERT(mEntities.find(id) != mEntities.end(), "Trying to add to the attribute '" + attribute + "' on entity entity ID '" + std::to_string(id) + "' but such an entity doesn't exist!");
        mStorage.setData(id, attribute, mStorage.getData<DataType>(id, attribute) + attributeData);
    }

    template<class DataType>
    void EntityManager::registerAttribute(const std::string& attribute)
    {
        mStorage.registerAttribute<DataType>(attribute);
    }
    /** @addtogroup EntitySystem
     *@{
     *  @class EntityManager
     *
     *  @typedef EntityPtr
     *  
     *  @typedef WeakEntityPtr
     *
     *  @typedef EntityId
     *
     *  @typedef EntitySet
     *@}
     ***
     *  @typedef EntityPtr
     *  @brief A shared pointer to an Entity instance.
     *
     *  @typedef WeakEntityPtr
     *  @brief A weak pointer to an Entity instance.
     *
     *  @typedef EntityId
     *  @brief The ID of an Entity instance. This is a normal 32 bit unsigned integer.
     *
     *  @typedef EntitySet
     *  @brief An std::set containing a number of entities represented with WeakEntityPtr instances.
     *
     *  @class EntityManager
     *  @brief Takes care of managing multiple Entity instances. 
     *
     *  This class is needed to create Entity instances. All entities will be owned by the EntityManager. It provides ways of accessing and deleting Entity instances of a given entity ID.
     *
     *  The only way to access Entity instances created by the EntityManager is through WeakEntityPtr instances. WeakEntityPtr is simply an alias to std::weak_ptr<Entity>. Entity pointers received from the EntityManager should never be manually freed, since that is the EntityManager's responsibility. If an entity is meant to be deleted, use the EntityManager::removeEntity function.
     *
     *  Prior to creating any Entity instances, attributes must be registered. Attributes are values belonging to entities. Some examples of attributes includes "health", "weight", "position" and "velocity". The type for the attribute is remembered by the entity manager.  Registration is done using EntityManager::registerAttribute.
     *
     *  After attributes have been registered, entities can be created. Entities have zero or more of registered attributes and they can be set for individual entities.
     ***
     *  @fn WeakEntityPtr EntityManager::createEntity(const std::set<std::string>& attributes)
     *  @brief Create an Entity with the given attributes.
     *  
     *  The attributes must have been registered prior to creating the Entity. If the function succeeds in creating the Entity, it will be assigned a unique ID and a WeakEntityPtr pointing to the Entity will be returned. The returned pointer is not meant to be stored in a locked state since that entity would still become invalid if the entity is deleted using the EntityManager::removeEntity method.
     *  @param attributes The names of the attributes the entity should have.
     *  @return A pointer to the created Entity.
     ***
     *  @fn WeakEntityPtr EntityManager::findEntity(EntityId id) const
     *  @brief Search for an entity with a given ID.
     *  @param id ID of the entity to find.
     *  @return Pointer to the entity. Will be null if no such entity exists.
     ***
     *  @fn void EntityManager::removeEntity(const EntityId id)
     *  @brief Remove an Entity. 
     *
     *  The removed Entity will become invalid instantly after the deletion. This means that if there are any WeakEntityPtr pointing to this Entity elsewhere in the application, those pointers must not be dereferenced. In the case there is a risk for pointing at an invalid Entity, the sanity of the pointer should always be checked before dereferencing it.
     *  Assert/undefined behavior when the entity does not exist.
     *
     *  @param id ID of the Entity to remove.
     ***
     *  @fn DataType EntityManager::getAttribute(const EntityId id, const std::string& attribute) const
     *  @brief Retrieve the value of an attribute of a selected Entity. 
     *  
     *  Assert/undefined behavior when the attribute does not exist or the wrong template argument is provided or the entity does not exist.
     *  @tparam DataType of the attribute to get.
     *  @param attribute Name of the attribute to get.
     *  @param id ID of the Entity to get the attribute from.
     ***
     *  @fn void EntityManager::setAttribute(const EntityId id, const std::string& attribute, const DataType& attributeData)
     *  @brief Set the value of an attribute of a selected Entity. 
     *  
     *  Assert/undefined behavior when the attribute does not exist or the wrong template argument is provide or the entity does not exist..
     *  @tparam DataType of the attribute to set.
     *  @param id ID of the Entity to set the attribute of.
     *  @param attribute Name of the attribute to set.
     *  @param attributeData Value to set the attribute to.
     ***
     *  @fn void EntityManager::addToAttribute(const EntityId id, const std::string& attribute, const DataType& attributeData)
     *  @brief Add the given value to an attribute of a selected Entity. 
     *
     *  Needs the operator+ function to be implemented for the target type.
     *  
     *  Assert/undefined behavior when the attribute does not exist or the wrong template argument is provide or the entity does not exist..
     *  In most cases, it is better to use the setting functions of a specific WeakEntityPtr than using this function.
     *  @tparam DataType of the attribute to add to.
     *  @param id ID of the Entity to add the attribute to.
     *  @param attribute Name of the attribute to add to.
     *  @param attributeData Value to add to the attribute.
     ***
     *  @fn bool EntityManager::hasAttribute(const EntityId id, const std::string& attribute) const
     *  @brief Check if an attribute exists for a specific Entity.
     *
     *  Assert/undefined behavior when the entity does not exist.
     *  @param id Entity to check an attribute for.
     *  @param attribute Name of the attribute to check for.
     *  @return True if the attribute exists, otherwise false.
     ***
     *  @fn void EntityManager::registerAttribute(const std::string& attribute)
     *  @brief Register an attribute.
     *  
     *  For an Entity to be able to have a certain attribute, the attribute needs to be registered, otherwise it can't be stored by the EntityManager. This only needs to be done once for every attribute. 
     *
     *  For example, this is how you would register an attribute called "Health points" as a 4 byte integer:
     *  @code
     *  entityManager.registerAttribute<int32_t>("Health points");
     *  @endcode
     *  Assert/undefined behavior when the attribute is already registered.
     *  @tparam DataType Type of the attribute.
     *  @param attribute Name of the attribute to register.
     ***
     *  @fn bool EntityManager::attributeIsValid(const std::string& attributeName) const
     *  @brief Check if an attribute has been registered.
     *  @param attributeName Name of the attribute.
     *  @return True if valid.
     ***
     *  @fn EntitySet EntityManager::getAll() const
     *  @brief Retrieve an EntitySet filled with all entities currently managed by the EntityManager.
     *  @return All entities in a set.
     ***
     *  @fn void EntityManager::removeAll()
     *  @brief Remove all Entity instances managed by the EntityManager, leaving all pointers to them invalid.
     ***
     *  @fn void EntityManager::clear()
     *  @brief Reset the whole state of the EntityManager to the original state. Effectively removing all Entity instances, leaving all pointers to them invalid, as well as clearing out any registered attributes. Not to be confused with EntityManager::removeAll which only removes all entities.
     ***/
}
