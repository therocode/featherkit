#pragma once
#include <map>
#include <string>
#include <featherkit/entity/entityexceptions.h>

using namespace fk;

namespace fku
{
    using ArrayPosition = uint32_t;
    using ElementSize = uint32_t;

    struct ArrayObject
    {
        char* data = nullptr;
        uint32_t* bitfield = nullptr;
        ElementSize elementSize = 0;
        ~ArrayObject();
    };

    using ArrayMap = std::map<fk::AttributeHash, ArrayObject>;

    class ArrayHolder
    {
        public:
            ArrayHolder();
            void addArray(const AttributeHash identifier, const ElementSize size);
            void swapData(const ArrayPosition position1, const ArrayPosition position2);
            void setData(const AttributeHash identifier, const ArrayPosition position, const char* inData);
            void getData(const AttributeHash identifier, const ArrayPosition position, char* outData) const;
            bool attributeIsValid(const AttributeHash identifier) const;
            void setMinimumArrayLength(const uint32_t length);
            void setEntryValid(const AttributeHash identifier, const ArrayPosition position, const bool state);
            bool getEntryValid(const AttributeHash identifier, const ArrayPosition position) const;
            char* getDataPointer(const AttributeHash identifier, const ArrayPosition position) const;
            uint32_t* getValidityPointer(const AttributeHash identifier, const ArrayPosition position) const;
            void clear();
        private:
            void extendArrays(uint32_t newLength);
            ArrayMap arrays;
            uint32_t arrayLength;
            uint32_t largestElement;
    };
}
