#include <cstring>
#include <sstream>
#include <featherkit/util/entity/arrayholder.h>

namespace fku
{
    ArrayObject::~ArrayObject()
    {
        if(data != nullptr)
            delete [] data;
        if(bitfield != nullptr)
            delete [] bitfield;
    }

    ArrayHolder::ArrayHolder()
    {
        arrayLength = 256;  //should be divisible with 32 due to the bitfield
        largestElement = 0;
    }

    void ArrayHolder::addArray(const AttributeHash identifier, const ElementSize size)
    {
        if(arrays.find(identifier) != arrays.end())
        {
            std::stringstream ss;
            ss << "Error! Attribute " << identifier << " is already added!\n";
            throw InvalidAttributeException(ss.str(), identifier);
        }
        uint32_t bitfieldLength = arrayLength / 32;
        char* newArray = new char[arrayLength * size];
        uint32_t* newBitfield = new uint32_t[bitfieldLength];
        ArrayObject newObject;

        newObject.data = newArray;
        newObject.bitfield = newBitfield;
        newObject.elementSize = size;

        for(uint32_t i = 0; i < bitfieldLength; i++)
            newBitfield[i] = 0;

        if(size > largestElement)
            largestElement = size;

        arrays.insert(std::pair<AttributeHash, ArrayObject>(identifier, newObject));
    }

    void ArrayHolder::swapData(const ArrayPosition position1, const ArrayPosition position2)
    {
        if(position1 == position2)
            return;

        char* tempBuffer = new char[largestElement];
        ElementSize size = 0;
        for(auto iter = arrays.begin(); iter != arrays.end(); iter++)
        {
            size = iter->second.elementSize;
            memcpy(tempBuffer, iter->second.data + (position1 * size), size);
            memcpy(iter->second.data + (position1 * size), iter->second.data + (position2 * size), size);
            memcpy(iter->second.data + (position2 * size), tempBuffer, size);
            
            bool position1Valid = getEntryValid(iter->first, position1);
            bool position2Valid = getEntryValid(iter->first, position2);


            setEntryValid(iter->first, position1, position2Valid);
            setEntryValid(iter->first, position2, position1Valid);
        }
        delete [] tempBuffer;
    }
    
    void ArrayHolder::setData(const AttributeHash identifier, const ArrayPosition position, const char* inData)
    {
        memcpy(arrays.at(identifier).data + (position * arrays.at(identifier).elementSize), inData, arrays.at(identifier).elementSize);
    }

    void ArrayHolder::getData(const AttributeHash identifier, const ArrayPosition position, char* outData) const
    {
        memcpy(outData, arrays.at(identifier).data + (position * arrays.at(identifier).elementSize), arrays.at(identifier).elementSize);
    }
    
    bool ArrayHolder::attributeIsValid(const AttributeHash identifier) const
    {
        return !(arrays.find(identifier) == arrays.end());
    }
    
    void ArrayHolder::setMinimumArrayLength(const uint32_t length)
    {
        if(length > arrayLength)
        {
            uint32_t newSize = arrayLength;
            while(length > newSize)
                newSize *= 2;
            extendArrays(newSize);
        }
    }

    void ArrayHolder::extendArrays(uint32_t newLength)
    {
        char* tempBuffer = new char[largestElement * arrayLength];

        for(auto iter = arrays.begin(); iter != arrays.end(); iter++)
        {
            ElementSize size = iter->second.elementSize;
            char* newArray = new char[size * newLength];
            memcpy(tempBuffer, iter->second.data, size * arrayLength);
            delete [] iter->second.data;
            iter->second.data = newArray;
            memcpy(iter->second.data, tempBuffer, size * arrayLength);

            uint32_t* newBitfield = new uint32_t[newLength / 32];
            memcpy(tempBuffer, iter->second.bitfield, (arrayLength / 32) * 4);
            delete [] iter->second.bitfield;
            iter->second.bitfield = newBitfield;
            memcpy(iter->second.bitfield, tempBuffer, (arrayLength / 32) * 4);

            for(uint32_t i = arrayLength / 32; i < newLength / 32; i++)
            {
                iter->second.bitfield[i] = 0;
            }
        }

        arrayLength = newLength;
        delete [] tempBuffer;
    }
    
    void ArrayHolder::setEntryValid(const AttributeHash identifier, const ArrayPosition position, const bool state) //ADD ERROR CHECKS?
    {
        ArrayPosition bitArrayIndex = position / 32;
        uint32_t bitIndex = position % 32;
        
        if(state)
        {
            arrays[identifier].bitfield[bitArrayIndex] |= (1 << (bitIndex));
        }
        else
        {
            arrays[identifier].bitfield[bitArrayIndex] &= ~(1 << (bitIndex));
        }
    }
    
    bool ArrayHolder::getEntryValid(const AttributeHash identifier, const ArrayPosition position) const //ADD ERROR CHECKS?
    {
        ArrayPosition bitArrayIndex = position / 32;
        uint32_t bitIndex = position % 32;

        try
        {
            return (bool)(arrays.at(identifier).bitfield[bitArrayIndex] & (1 << (bitIndex)));
        }
        catch(std::out_of_range e)
        {
            return false;
        }
    }

    char* ArrayHolder::getDataPointer(const AttributeHash identifier, const ArrayPosition position) const
    {
        return arrays.at(identifier).data + (position * arrays.at(identifier).elementSize);
    }

    uint32_t* ArrayHolder::getValidityPointer(const AttributeHash identifier, const ArrayPosition position) const
    {
        return arrays.at(identifier).bitfield + (position / 32);
    }
    
    void ArrayHolder::clear()
    {
        for(auto iter = arrays.begin(); iter != arrays.end(); iter++) 
        {
            delete [] iter->second.data;
            delete [] iter->second.bitfield;
        }
        arrays.clear();
        arrayLength = 256;
        largestElement = 0;
    }
}
