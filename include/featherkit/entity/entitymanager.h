#pragma once
#include <featherkit/entity/entitybackend.h>
#include <featherkit/entity/entityexceptions.h>
#include <memory>
#include <map>
#include <vector>
#include <stdexcept>
#include <sstream>

namespace fea
{
    class Entity;
    class EntityGroup;

    using EntityPtr = std::shared_ptr<Entity>;
    using WeakEntityPtr = std::weak_ptr<Entity>;
    using EntityType = std::string;
    using EntityId = uint32_t;
    
    struct EntityTypeData
    {
        AttributeList attributeList;
        std::map<std::string, std::string> defaultStrings;
    };

    class EntityManager
    {
        public:
            EntityManager(EntityBackend* b);
            WeakEntityPtr createEntity(const EntityType& type);
            WeakEntityPtr getEntity(EntityId id) const;
            void removeEntity(const EntityId id);
            void removeEntities(const EntityGroup entities);
            template<class DataType>
            void getAttribute(const std::string& attribute, const EntityId id, DataType* outData) const;
            template<class DataType>
            void setAttribute(const std::string& attribute, const EntityId id, const DataType* inData);
            template<class DataType>
            void modifyAttribute(const std::string& attribute, const EntityId id, const DataType* inData);
            bool hasAttribute(const std::string& attribute, const EntityId id) const;
            void registerAttribute(const std::string& attribute, const int size);
            void registerAttributes(const std::map<std::string, int>& attributes);
            void registerEntityType(const EntityType& type, const std::map<std::string, std::string>& attributes);
            void registerEntityTypes(const std::map<EntityType, std::map<std::string, std::string> > types);
            void registerDefaultSetter(std::string attribute, std::function<void(std::string, std::vector<std::string>&, WeakEntityPtr)> defaultFunc);
            EntityGroup getAll() const;
            void removeAll();
            void reset();
        private:
            std::unique_ptr<EntityBackend> backend;
            std::map<EntityType, EntityTypeData> entityTypes;
            std::map<EntityId, EntityPtr> entities;
            std::map<std::string, std::function<void(std::string, std::vector<std::string>&, WeakEntityPtr)> > defaultSetters;
    };

    template<class DataType>
    void EntityManager::getAttribute(const std::string& attribute, const EntityId id, DataType* outData) const
    {
        std::hash<std::string> hasher;
        try
        {
            backend->getData(hasher(attribute), id, (char*) outData);
        }
        catch(InvalidAttributeException)
        {
            std::stringstream ss;
            ss << "Error! The given attribute '" << attribute << "' does not exist!\n";
            throw InvalidAttributeException(ss.str(), hasher(attribute));
        }
    }

    template<class DataType>
    void EntityManager::setAttribute(const std::string& attribute, const EntityId id, const DataType* inData)
    {
        std::hash<std::string> hasher;
        try
        {
            backend->setData(hasher(attribute), id, (char*) inData);
        }
        catch(InvalidAttributeException)
        {
            std::stringstream ss;
            ss << "Error! The given attribute '" << attribute << "' does not exist!\n";
            throw InvalidAttributeException(ss.str(), hasher(attribute));
        }
    }

    template<class DataType>
    void EntityManager::modifyAttribute(const std::string& attribute, const EntityId id, const DataType* inData)
    {
        std::hash<std::string> hasher;
        size_t hashed = hasher(attribute);

        DataType temp;
        backend->getData(hashed, id, (char*) &temp);
        temp = temp + *inData;

        backend->setData(hashed, id, (char*) &temp);
    }
    /** @addtogroup EntitySystem
     *@{
     *  @class EntityManager
     *
     *  @typedef EntityPtr
     *  
     *  @typedef WeakEntityPtr
     *
     *  @typedef EntityType
     *
     *  @typedef EntityId
     *@}
     ***
     *  @typedef EntityPtr
     *  @brief A shared pointer to an Entity instance.
     *
     *  @typedef WeakEntityPtr
     *  @brief A weak pointer to an Entity instance.
     *
     *  @typedef EntityType
     *  @brief The type of an Entity instance. This is a normal std::string.
     *
     *  @typedef EntityId
     *  @brief The ID of an Entity instance. This is a normal 32 bit unsigned integer.
     *
     *  @class EntityManager
     *  @brief Takes care of managing multiple Entity instances. 
     *
     *  This class is needed to create Entity instances. All entities will be owned by the EntityManager. It provides ways of accessing and deleting Entity instances of a given entity ID.
     *
     *  The only way to access Entity instances created by the EntityManager is through WeakEntityPtr instances. WeakEntityPtr is simply an alias to std::weak_ptr<Entity>. Entity pointers received from the EntityManager should never be manually freed, since that is the job of the EntityManager. If an entity is meant to be deleted, use the EntityManager::removeEntity function.
     *
     *  Prior to creating any Entity instances, attributes and enty types must be registered. If an entity type which is either not registered, or has unregistered attributes, an appropriate exception will be thrown. Registration is done using EntityManager::registerAttribute and EntityManager::registerEntityType.
     *
     *  The EntityManager relies on an EntityBackend which is responsible of providing a data structure for the EntityManager to store its data in. The underlying implementation of these may vary and have different pros and cons. 
     ***
     *  @fn EntityManager::EntityManager(EntityBackend* b)
     *  @brief Construct an EntityManager that will use the provided EntityBackend.
     *  @param b Backend to be used. The backend is stored internally as an std::unique_ptr and the memory of it will therefore be managed.
     ***
     *  @fn WeakEntityPtr EntityManager::createEntity(const EntityType& type)
     *  @brief Create an Entity of the given EntityType.
     *  
     *  The EntityType given along with its attributes must have been registered prior to creating the Entity. Otherwise, an EntityException will be thrown. If the function succeeds in creating the Entity, it will be assigned a unique ID and a WeakEntityPtr pointing to the Entity will be returned.
     *  @param type The name of the type of Entity to be created.
     *  @return A pointer to the created Entity.
     ***
     *  @fn WeakEntityPtr EntityManager::getEntity(EntityId id) const
     *  @brief Get a specific entity.
     *  @param id ID of the entity to get.
     *  @return Pointer to the entity.
     ***
     *  @fn void EntityManager::removeEntity(const EntityId id)
     *  @brief Remove an Entity. 
     *
     *  The removed Entity will become invalid instantly after the deletion. This means that if there are any WeakEntityPtr pointing to this Entity elsewhere in the application, those pointers must not be dereferenced. In the case there is a risk for pointing at an invalid Entity, the sanity of the pointer should always be checked before dereferencing it.
     *
     *  If a non-existing Entity is given, it will throw an EntityException.
     *  @param id ID of the Entity to remove.
     ***
     *  @fn void EntityManager::removeEntities(const EntityGroup entities)
     *  @brief Remove a whole EntityGroup at once.
     *  
     *  See EntityManager::removeEntity for more information.
     *  @param entities Group to remove.
     ***
     *  @fn void EntityManager::getAttribute(const std::string& attribute, const EntityId id, DataType* outData) const
     *  @brief Retrieve the value of an attribute of a selected Entity. 
     *  
     *  If the given attribute does not exist for the selected Entity, an InvalidAttributeException will be thrown. If the selected Entity does not exist, an EntityException will be thrown. In most cases, it is better to use the access functions of a specific WeakEntityPtr than using this function.
     *  @tparam Type of the attribute to get.
     *  @param attribute Name of the attribute to get.
     *  @param id ID of the Entity to get the attribute from.
     *  @param outData Pointer to a variable where the value will be stored.
     ***
     *  @fn void EntityManager::setAttribute(const std::string& attribute, const EntityId id, DataType* inData) const
     *  @brief Set the value of an attribute of a selected Entity. 
     *  
     *  If the given attribute does not exist for the selected Entity, an InvalidAttributeException will be thrown. If the selected Entity does not exist, an EntityException will be thrown. In most cases, it is better to use the setting functions of a specific WeakEntityPtr than using this function.
     *  @tparam Type of the attribute to set.
     *  @param attribute Name of the attribute to set.
     *  @param id ID of the Entity to set the attribute of.
     *  @param inData Pointer to a variable containing the new value.
     ***
     *  @fn void EntityManager::modifyAttribute(const std::string& attribute, const EntityId id, DataType* inData) const
     *  @brief Modify the value of an attribute of a selected Entity. 
     *
     *  The given value will be added to the already existing value. Needs the operator+ function to be implemented for the target type.
     *  
     *  If the given attribute does not exist for the selected Entity, an InvalidAttributeException will be thrown. If the selected Entity does not exist, an EntityException will be thrown. In most cases, it is better to use the setting functions of a specific WeakEntityPtr than using this function.
     *  @tparam Type of the attribute to modify.
     *  @param attribute Name of the attribute to modify.
     *  @param id ID of the Entity to modify the attribute of.
     *  @param inData Pointer to a variable containing the value to add.
     ***
     *  @fn bool EntityManager::hasAttribute(const std::string& attribute, const EntityId id) const
     *  @brief Check if an attribute exists for a specific Entity.
     *  @param attribute Name of the attribute to check for.
     *  @param id Entity to check an attribute for.
     *  @return True if the attribute exists, otherwise false.
     ***
     *  @fn void EntityManager::registerAttribute(const std::string& attribute, const int size)
     *  @brief Register an attribute and sets it memory size.
     *  
     *  For an Entity to be able to have a certain attribute, the attribute needs to be registered and given a memory size. Otherwise it can't be stored by the EntityManager. This only needs to be done once for every attribute. Throws an InvalidAttributeException if the attribute already exists.
     *
     *  For example, this is how you would register an attribute called "Health points" as a 4 byte integer:
     *  @code
     *  entityManager.registerAttribute("Health points", 4);
     *  @endcode
     *  @param attribute Name of the attribute to register.
     *  @param size Memory size in bytes.
     ***
     *  @fn void EntityManager::registerAttributes(const std::map<std::string, int>& attributes)
     *  @brief Register multiple attributes at once.
     *  Works the same as EntityManager::registerAttribute except it registers a whole map full of attributes at once. Useful for loading attribute configurations that have been read from file.
     *  @param attributes Map containing attribute names and memory sizes.
     ***
     *  @fn void EntityManager::registerEntityType(const EntityType& type, const std::map<std::string, std::string>& attributes)
     *  @brief Register an EntityType. 
     *
     *  The entity type is a name mapped to a map of attributes and their default values. The registered entity type will have all the attributes provided in the map. For example, an Entity type called "Apple" might be registered with the attributes "weight", "brand" and "ripeness". Keep in mind that these attributes must have been registered using EntityManager::registerAttribute.
     *
     *  Default values are given as strings. They may be empty in which case the attribute does not have a default value. These strings have to be hadled by a default setter function. These functions must be registered separately using EntityManager::registerDefaultSetter. See that function for more information on default values.
     *  @param type Name of the new Entity type.
     *  @param attributes Map containing attribute names and default values.
     ***
     *  @fn void EntityManager::registerEntityTypes(const std::map<EntityType, std::map<std::string, std::string> > types)
     *  @brief Register multiple Entity types at once.
     *  
     *  Works the same as EntityManager::registerEntityType except it registers a whole map full of Entity types at once. Useful for loading Entity type configurations that have been read from file.
     *  @param types Map containing Entity type names and maps with attribute information.
     ***
     *  @fn void EntityManager::registerDefaultSetter(std::string attribute, void (*defaultFunc)(std::string, std::vector<std::string>&, WeakEntityPtr))
     *  @brief Register a default setter function for a given attribute.
     *
     *  When registering entity types, default values are registered with their attributes. These default values are always just plain strings, and to make these actually being set to the attribute which might be of any given type in a correct way, a default setter function is needed.
     *
     *  This function should take a string for the attribute name, and an std::vector<std::string> which contains the default value string cut into pieces delimited by ",", and finally a pointer to the entity for which the attribute should be set. This function is responsible for setting the default value for the WeakEntityPtr instance.
     *
     *  For example, if the attribute "Colour has been registered and the data type that will be used for this attribute is this struct...
     *  @code
     *  struct Colour
     *  {
     *    float r;
     *    float g;
     *    float b;
     *   };
     *  @endcode
     *  ...and you have registered an entity type with that attribute, and the default value "1.0f,0.0f,0.0f" for it, then an appropriate default setting function would be:
     *  @code
     *  void colourSetter(std::string attribute, std::vector<std::string>& arguments, fea::WeakEntityPtr entity)
     *  {
     *    Colour col;
     *    col.r = std::stof(arguments[0]);
     *    col.g = std::stof(arguments[1]);
     *    col.b = std::stof(arguments[2]);
     *
     *    entity.lock()->setAttribute<Colour>(attribute, col);
     *  }
     *  @endcode
     *  This works since the default string "1.0f,0.0f,0.0f" will be given to the default setter function as "1.0f", "0.0f" and "0.0f" in the std::vector. Of course it needs to be registered using this function:
     *  @code
     *  entityManager.registerDefaultSetter("Colour", &colourSetter);
     *  @endcode
     *
     *  After this, whenever an entity of that type (or any other type using the "Colour" attribute) is created, the default value will be set according to the default string.
     *  
     *  If an entity type is registered with default values for an attribute, that attribute must have a default setter function registered or an InvalidAttributeException will be thrown.
     *  @param attribute Name of the attribute.
     *  @param defaultFunc Pointer to the default setter function.
     ***
     *  @fn EntityGroup EntityManager::getAll() const
     *  @brief Retrieve an EntityGroup filled with all entities currently managed by the EntityManager.
     *  @return All entities in a group.
     ***
     *  @fn void EntityManager::removeAll()
     *  @brief Remove all Entity instances managed by the EntityManager, leaving all pointers to them invalid.
     ***
     *  @fn void EntityManager::reset()
     *  @brief Reset the whole state of the EntityManager to the original state. Effectively removing all Entity instances, leaving all pointers to them invalid, as well as clearing out any registered attributes, Entity types and default setter functions. Not to be confused with EntityManager::removeAll which only removes all entities.
     ***
     *  using EntityPtr std::shared_ptr<Entity>
     *  brief Entity pointer typedef
     ***
     *  using WeakEntityPtr std::weak_ptr<Entity>
     *  brief HEJHEJ
    using WeakEntityPtr = std::weak_ptr<Entity>;
    using EntityType = std::string;
    using EntityId = uint32_t;
     ***/
}
