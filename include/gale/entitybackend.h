#pragma once
#include "common.h"
#include "attributelist.h"

namespace windgale
{
    class EntityBackend
    {
            public:
                virtual int addEntity(AttributeList attributeList) = 0;
                virtual void removeEntity(const int id) = 0;
                virtual void registerAttribute(const AttributeHash identifier, const ElementSize elementSize) = 0;
                virtual void setData(const AttributeHash identifier, const int id, const char* inData) = 0;
                virtual void getData(const AttributeHash identifier, const int id, char* outData) const = 0;
                virtual bool hasData(const AttributeHash identifier, const int id) const = 0;
                virtual bool attributeIsValid(AttributeHash identifier) = 0;
                virtual void clear() = 0;
    };
}
