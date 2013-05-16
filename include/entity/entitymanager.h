#pragma once
#include "entitybackend.h"
#include <memory>
#include <map>
#include <vector>
#include "common.h"
#include <stdexcept>

namespace windgale
{
    class EntityException : public std::runtime_error 
    {
        public:
            EntityException(const std::string& message) 
                : std::runtime_error(message) { };
    };
    
    //TODO: check if unsorted_map/set would be better in places
    //TODO: apply rule of three - including move constructor
    //TODO: http://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
    //TODO: make use of std::insert and std::erase
    //TODO: profile! make a dumb entity implementation and compare. 
    //TODO: think: is attributeArrayLocation necessary if std::maps are always sorted and index can be gotten therefrom?
    //TODO: think: should expiration of pointers be checked before the library uses lock?
    //TODO: think: should it be possible to disable attributes?
    //TODO: think; should entity manager really do this much? register attributes etc
    //TODO: clean up, using auto, const etc
    //TODO: nicer type for IDs
    //TODO: consider if components should be a system included, or up to the user
    //TODO: what about temporary variables that needs to be stored in components? how to handle that? example: last frame position, such
    //TODO: mandatory/non-mandatory attributes when getting the data from iterators?
    //TODO: error checking for the attribute loader

    struct EntityTypeData
    {
        AttributeList attributeList;
        std::map<std::string, std::string> defaultStrings;
    };

    class EntityManager
    {
        public:
            EntityManager(EntityBackend& b) : backend(b) {};
            WeakEntityPtr createEntity(const EntityType& type);
            void removeEntity(const EntityId id);
            void removeEntities(const EntityGroup entities);
            template<class DataType>
            void getAttribute(const std::string& attribute, const EntityId id, DataType* outData) const;
            template<class DataType>
            void setAttribute(const std::string& attribute, const EntityId id, const DataType* inData);
            bool hasAttribute(const std::string& attribute, const EntityId id) const;
            void registerAttribute(const std::string& attribute, const int size);
            void registerAttributes(const std::map<std::string, int>& attributes);
            void registerEntityType(const EntityType& type, const std::map<std::string, std::string>& attributes);
            void registerEntityTypes(const std::map<EntityType, std::map<std::string, std::string> > types);
            void setDefaultSetter(std::string attribute, void (*defaultFunc)(std::string, std::vector<std::string>&, WeakEntityPtr));
            EntityGroup getAll();
            void removeAll();
            void reset();
        private:
            EntityBackend& backend;
            std::map<EntityType, EntityTypeData> entityTypes;
            std::map<EntityId, EntityPtr> entities;
            std::map<std::string, void (*)(std::string, std::vector<std::string>&, WeakEntityPtr)> defaultSetters;
    };

    template<class DataType>
    void EntityManager::getAttribute(const std::string& attribute, const EntityId id, DataType* outData) const
    {
        std::hash<std::string> hasher;
        backend.getData(hasher(attribute), id, (char*) outData);
    }
    template<class DataType>
    void EntityManager::setAttribute(const std::string& attribute, const EntityId id, const DataType* inData)
    {
        std::hash<std::string> hasher;
        backend.setData(hasher(attribute), id, (char*) inData);
    }
}
