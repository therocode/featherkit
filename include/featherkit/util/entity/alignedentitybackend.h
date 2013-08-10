#pragma once
#include <featherkit/entity/entitybackend.h>
#include <featherkit/util/entity/arrayholder.h>
#include <featherkit/util/entity/bimap.h>
#include <vector>
#include <stack>
#include <string>

namespace fea
{
    namespace util
    {
        struct DataContainer
        {
            char* data;
            uint32_t* validity;
            uint32_t dataLength;        
            uint32_t validityStartBit;
        };

        using DataMap = std::map<AttributeHash, DataContainer>;

        class AlignedEntityBackend : public EntityBackend
        {
            public:
                AlignedEntityBackend();
                EntityId addEntity(AttributeList attributeList) override;
                void removeEntity(const EntityId id) override;
                void registerAttribute(const AttributeHash identifier, const ElementSize elementSize) override;
                void setData(const AttributeHash identifier, const EntityId id, const char* inData) override;
                void getData(const AttributeHash identifier, const EntityId id, char* outData) const override;
                bool hasData(const AttributeHash identifier, const EntityId id) const override;
                bool attributeIsValid(AttributeHash identifier) const override;
                void clear() override;
                DataMap getIterableData(std::vector<std::string> stringList) const;
            private:
                std::string concatAttributeList(const std::vector<std::string>& attributeList) const;   
                std::vector<std::string> splitAttributeString(const std::string& attributeString) const;  
                void sortAttributeList(std::vector<std::string>& attributeList) const; 
                void swapDownEntityThroughGroups(const uint32_t startEntityPosition, const uint32_t stopGroupIndex); 
                void swapDownEntityThroughGroups(const uint32_t startEntityPosition, const uint32_t stopGroupIndex, bool newGroup); 
                void swapDownGroups(const uint32_t startIndex, const uint32_t stopIndex); 
                void setSlotsValid(const AttributeList& attributeList, const uint32_t position, const bool state); 
                EntityId assignEntityAtEnd(uint32_t& arrayPos);
                void validateAttributeList(AttributeList attributeList) const;
                uint32_t findSuitableAttributeGroupIndex(AttributeList attributeList) const; 
                uint32_t getSubsetGroupArrayPosition(AttributeList& attributeList) const;
                uint32_t getAttributeGroupIndexFromPosition(uint32_t position) const;
                uint32_t getLastDataOfGroup(uint32_t currentGroup) const;
                void removeAttributeGroup(uint32_t group);
                feai::BiMap<uint32_t, EntityId> posIdMap;
                feai::BiMap<AttributeList, uint32_t> attributeGroupIndex;
                std::vector<uint32_t> attributeGroupLocation;
                ArrayHolder dataArrays;
                std::stack<EntityId> freeEntityIds;
                EntityId  nextEntityId;
                uint32_t nextEmptyArraySlot;
        };
        /** @addtogroup EntitySystem
         *@{
         *  @class AlignedEntityBackend
         *
         *  @struct DataContainer
         *
         *  @typedef DataMap
         *@}
         ***
         *  @typedef DataMap
         *  @brief Map containing iterable Entity data.
         ***
         *  @struct DataContainer
         *  @brief Container for iterable Entity data.
         ***
         *  @var DataContainer::data
         *  @brief Pointer to where the relevant data begins in the attribute array.
         ***
         *  @var DataContainer::validity
         *  @brief Pointer to where the relevant validity data begins in the validity bitfield belonging to the attribute.
         ***
         *  @var DataContainer::dataLength
         *  @brief How many elements should be iterated.
         ***
         *  @var DataContainer::validityStartBit
         *  @brief The bit offset in the bitfield to which the first element belongs.
         ***
         *  @class AlignedEntityBackend
         *  @brief Data oriented implementation of the EntityBackend base class.
         *
         *  This EntityBackend implementation internally stores the Entity data in per-attribute arrays. These arrays are accessable for efficient iteration using the function AlignedEntityBackend::getIterableData. For situations where a lot of intensive processing has to be done for many entities, this may prove much more efficient than for instance the BasicEntityBackend. This implementation however, has a bigger memory footprint.
         ***
         *  @fn int AlignedEntityBackend::addEntity(AttributeList attributeList)
         *  @brief Create a new Entity with the attributes from the given AttributeList.
         *  @param attributeList The attributes the Entity should have.
         ***
         *  @fn void AlignedEntityBackend::removeEntity(const int id)
         *  @brief Remove an Entity stored in the AlignedEntityBackend.
         *
         *  This should throw an EntityException if the given Entity does not exist.
         *  @param id Entity to remove.
         ***
         *  @fn void AlignedEntityBackend::registerAttribute(const AttributeHash identifier, const ElementSize elementSize)
         *  @brief Register an attribute with the given size in bytes.
         *  @param identifier Hash unique to this attribute.
         *  @param elementSize Memory size in bytes.
         ***
         *  @fn void AlignedEntityBackend::setData(const AttributeHash identifier, const int id, const char* inData)
         *  @brief Set attribute data of an Entity.
         *  
         *  Should throw an InvalidAttributeException if the attribute does not exist.
         *  @param identifier Hash representing the attribute to set.
         *  @param id ID of the Entity to set the attribute for.
         *  @param inData Pointer to a variable holding the value to set.
         ***
         *  @fn void AlignedEntityBackend::getData(const AttributeHash identifier, const int id, const char* outData)
         *  @brief Get attribute data of an Entity.
         *
         *  Should throw an InvalidAttributeException if the attribute does not exist.
         *  @param identifier Hash representing the attribute to get.
         *  @param id ID of the Entity to get the attribute for.
         *  @param outData Pointer to a variable holding the value to get.
         ***
         *  @fn bool AlignedEntityBackend::hasData(const AttributeHash identifier, const int id) const
         *  @brief Check if a certain Entity has an attribute.
         *
         *  Should throw an InvalidAttributeException if the attribute does not exist.
         *  @param identifier Hash representing the attribute to check for.
         *  @param id ID of the Entity to check the attribute for.
         *  @return True if the attribute exists, otherwise false.
         ***
        *  @fn bool AlignedEntityBackend::attributeIsValid(AttributeHash identifier) const
            *  @brief Check if a certain attribute is registered.
            *  @param identifier Hash representing the attribute to check.
            *  @return True if the attribute is registered, otherwise false.
            ***
            *  @fn void AlignedEntityBackend::clear()
            *  @brief Removes all Entity instances currently stored in the AlignedEntityBackend.
            ***
            *  @fn DataMap AlignedEntityBackend::getIterableData(std::vector<std::string> stringList) const
            *  @brief Retrieve iterable Entity data.
            *  
            *  This function is unique to this EntityBackend implementation. Through the arguments, a specific set of attributes are requested. The function then returns a structure of pointers to the appropriate places in the Entity data arrays along with bitfield arrays to determine if data at specific array positions are valid or not.
            *
            *  See the tutorial pages for more information on how to use this function properly.
            ***/
    }
}
