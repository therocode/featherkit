#pragma once
#include "entitymanager.h"

namespace windgale
{
    class Entity
    {
        public:
            Entity(EntityId i, EntityManager& m) : id(i), entityManager(m) {}
            template<class DataType>
            bool getAttributeSafe(const std::string& attribute, DataType* outData) const;
            template<class DataType>
            bool setAttributeSafe(const std::string& attribute, const DataType* inData) const;
            template<class DataType>
            DataType getAttribute(const std::string& attribute) const;
            template<class DataType>
            void setAttribute(const std::string& attribute, DataType value) const;
            bool hasAttribute(const std::string& attribute);
            EntityId getId();
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
}
