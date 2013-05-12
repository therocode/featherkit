#pragma once
#include "entitybackend.h"
#include "../util/bimap.h"
#include "arrayholder.h"
#include <vector>
#include <stack>
#include <string>

namespace windgale
{
    using DataMap = std::map<AttributeHash, DataContainer>;

    struct DataContainer
    {
        char* data;
        uint32_t* validity;
        int dataLength;        
        int validityStartBit;
    };

    class AlignedEntityBackend : public EntityBackend
    {
        public:
            AlignedEntityBackend();
            int addEntity(AttributeList attributeList) override;
            void removeEntity(const int id) override;
            void registerAttribute(const AttributeHash identifier, const ElementSize elementSize) override;
            void setData(const AttributeHash identifier, const int id, const char* inData) override;
            void getData(const AttributeHash identifier, const int id, char* outData) const override;
            bool hasData(const AttributeHash identifier, const int id) const override;
            bool attributeIsValid(AttributeHash identifier) override;
            void clear() override;
            DataMap getIterableData(std::vector<std::string> stringList);
            void debug(std::string mes);
        private:
            std::string concatAttributeList(const std::vector<std::string>& attributeList) const;   
            std::vector<std::string> splitAttributeString(const std::string& attributeString) const;  
            void sortAttributeList(std::vector<std::string>& attributeList) const; 
            void swapDownEntityThroughGroups(const int startEntityPosition, const int stopGroupIndex); 
            void swapDownEntityThroughGroups(const int startEntityPosition, const int stopGroupIndex, bool newGroup); 
            void swapDownGroups(const int startIndex, const int stopIndex); 
            void setSlotsValid(const AttributeList& attributeList, const int position, const bool state); 
            int assignEntityAtEnd(int& arrayPos);
            void validateAttributeList(AttributeList attributeList) const;
            int findSuitableAttributeGroupIndex(AttributeList attributeList) const; 
            int getSubsetGroupArrayPosition(AttributeList& attributeList) const;
            int getAttributeGroupIndexFromPosition(int position);
            int getLastDataOfGroup(unsigned int currentGroup);
            void removeAttributeGroup(unsigned int group);
            BiMap<int, int> posIdMap;
            BiMap<AttributeList, int> attributeGroupIndex;
            std::vector<int> attributeGroupLocation;
            ArrayHolder dataArrays;
            std::stack<int> freeEntityIds;
            uint32_t  nextEntityId;
            int nextEmptyArraySlot;
    };
}
