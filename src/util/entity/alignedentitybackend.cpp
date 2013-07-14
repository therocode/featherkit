#include <framework/util/entity/alignedentitybackend.h>
#include <algorithm>
#include <sstream>
#include <framework/entity/entityexceptions.h>

    namespace windgale
    {

        AlignedEntityBackend::AlignedEntityBackend()
        {
            nextEntityId = 0;
            nextEmptyArraySlot = 0;
        }

        EntityId AlignedEntityBackend::addEntity(AttributeList attributeList)
        {
            validateAttributeList(attributeList);

            EntityId createdEntityId = 0;
            if(attributeGroupIndex.keyExists(attributeList))
            {
                int attributeIndex = attributeGroupIndex.getValueAtKey(attributeList);
                int entityArrayLocation;
                createdEntityId = assignEntityAtEnd(entityArrayLocation);
                setSlotsValid(attributeList, entityArrayLocation, true);
                swapDownEntityThroughGroups(entityArrayLocation, attributeIndex, false);

                for(int i = attributeGroupLocation.size() - 1; i > attributeIndex; i--)
                    attributeGroupLocation[i]++;
            }
            else
            {
                int newAttributeTargetIndex = findSuitableAttributeGroupIndex(attributeList);
            int newAttributeCreatedIndex = attributeGroupLocation.size();

            attributeGroupIndex.addKeyValuePair(attributeList, newAttributeCreatedIndex);
            swapDownGroups(newAttributeCreatedIndex, newAttributeTargetIndex);

            int attribGroupLocationSize = attributeGroupLocation.size();


            if(attribGroupLocationSize > 0 && newAttributeTargetIndex < attributeGroupIndex.size() - 1)
            {
                attributeGroupLocation.insert(attributeGroupLocation.begin() + newAttributeTargetIndex, attributeGroupLocation[newAttributeTargetIndex]);
                for(unsigned int i = newAttributeTargetIndex + 1; i < attributeGroupLocation.size(); i++)
                    attributeGroupLocation[i]++;
            }
            else if (attribGroupLocationSize > 0)
            {
                attributeGroupLocation.push_back(nextEmptyArraySlot);
            }
            else
            {
                attributeGroupLocation.push_back(0);
            }

            int entityArrayLocation;
            createdEntityId = assignEntityAtEnd(entityArrayLocation);
            setSlotsValid(attributeList, entityArrayLocation, true);

            swapDownEntityThroughGroups(entityArrayLocation, newAttributeTargetIndex, true);
        }
        return createdEntityId;
    }

    void AlignedEntityBackend::removeEntity(const EntityId id)
    {

        if(!posIdMap.valueExists(id))
        {
            std::stringstream ss;
            ss << "Error! Cannot remove entity number " << id << "! It is not a valid entity!\n";
            throw InvalidIdException(ss.str());
        }
        int position = posIdMap.getKeyAtValue(id);
        int startGroup = getAttributeGroupIndexFromPosition(position);

        setSlotsValid(attributeGroupIndex.getKeyAtValue(startGroup), position, false);

        int currentGroup = getAttributeGroupIndexFromPosition(position + 1);

        if(currentGroup == -1)
        {
            posIdMap.removeAtValue(id);
            return;
        }

        int prevIndex = position;
        
        while(currentGroup < attributeGroupIndex.size())
        {
            int lastOfGroup = getLastDataOfGroup(currentGroup);

            posIdMap.swapValuesAtKeys(prevIndex, lastOfGroup);
            dataArrays.swapData(prevIndex, lastOfGroup);

            prevIndex = lastOfGroup;
            currentGroup++;
        }
        
        posIdMap.removeAtValue(id);
        nextEmptyArraySlot--;

        freeEntityIds.push(id);

        if(attributeGroupIndex.size() == 1)
        {
            if(nextEmptyArraySlot == 0)
            {
                removeAttributeGroup(startGroup);
            }
            return;
        }

        if(startGroup == attributeGroupIndex.size() -1)
        {
            if(attributeGroupLocation[startGroup] == nextEmptyArraySlot)
            {
                removeAttributeGroup(startGroup);
            }
            return;
        }

        int currentBorderChangedGroup = startGroup + 1;
        while(currentBorderChangedGroup < attributeGroupIndex.size())
        {
            attributeGroupLocation[currentBorderChangedGroup]--;
            currentBorderChangedGroup++;
        }



        if(attributeGroupLocation[startGroup] == attributeGroupLocation[startGroup + 1])
        {
            return removeAttributeGroup(startGroup);
        }
    }
    
    void AlignedEntityBackend::registerAttribute(const AttributeHash identifier, const ElementSize elementSize)
    {
        dataArrays.addArray(identifier, elementSize);
    }

    void AlignedEntityBackend::setData(const AttributeHash identifier, const EntityId id, const char* inData)
    {
        if(!posIdMap.valueExists(id))
        {
            std::stringstream ss;
            ss << "Error! Entity number " << id << " does not exist!\n";
            throw InvalidIdException(ss.str());
        }
        int position = posIdMap.getKeyAtValue(id);

        if(!dataArrays.attributeIsValid(identifier))
        {
            std::stringstream ss;
            ss << "Error! The given attribute '" << identifier << "' does not exist!\n";
            throw InvalidAttributeException(ss.str(), identifier);
        }
            
        if(dataArrays.getEntryValid(identifier, position))
        {
            dataArrays.setData(identifier, position, inData);
        }
        else
        {
            std::stringstream ss;
            ss << "Error! The given attribute '" << identifier << "' does not exist for entity number " << id << " which resides at position " << position << " in the array!\n";
            throw InvalidAttributeException(ss.str(), identifier);
        }
    }

    void AlignedEntityBackend::getData(const AttributeHash identifier, const EntityId id, char* outData) const
    {
        if(!posIdMap.valueExists(id))
        {
            std::stringstream ss;
            ss << "Error! Entity number " << id << " does not exist!\n";
            throw InvalidIdException(ss.str());
        }
        int position = posIdMap.getKeyAtValue(id);

        if(!dataArrays.attributeIsValid(identifier))
        {
            std::stringstream ss;
            ss << "Error! The given attribute '" << identifier << "' does not exist!\n";
            throw InvalidAttributeException(ss.str(), identifier);
        }

        if(dataArrays.getEntryValid(identifier, position))
        {
            dataArrays.getData(identifier, position, outData);
        }
        else
        {
            std::stringstream ss;
            ss << "Error! The given attribute '" << identifier << "' does not exist for entity number " << id << "!\n";
            throw InvalidAttributeException(ss.str(), identifier);
        }
    }
    
    bool AlignedEntityBackend::hasData(const AttributeHash identifier, const EntityId id) const
    {
        return dataArrays.getEntryValid(identifier, posIdMap.getKeyAtValue(id));
    }

    bool AlignedEntityBackend::attributeIsValid(AttributeHash identifier) const
    {
        return dataArrays.attributeIsValid(identifier);
    }

    std::string AlignedEntityBackend::concatAttributeList(const std::vector<std::string>& attributeList) const
    {
        if(attributeList.size() == 0)
            return "";

        std::stringstream ss;

        for(unsigned int i = 0; i < attributeList.size() - 1; i++)
        {
            ss << attributeList[i] << ";";
        }
        ss << attributeList[attributeList.size() - 1];
        return ss.str();
    }

    std::vector<std::string> AlignedEntityBackend::splitAttributeString(const std::string& attributeString) const
    {
        std::vector<std::string> attributeList;
        std::string attribute;
        std::stringstream ss(attributeString);
        while(getline(ss, attribute, ';'))
        {
            attributeList.push_back(attribute);
        }
        return attributeList;
    }

    void AlignedEntityBackend::sortAttributeList(std::vector<std::string>& attributeList) const
    {
        sort(attributeList.begin(), attributeList.end());
    }

    int AlignedEntityBackend::findSuitableAttributeGroupIndex(AttributeList attributeList) const
    {
        int groupAmount = attributeGroupIndex.size();
        int indexToChoose = groupAmount;

        for(int i = 0; i < groupAmount; i++)
        {
            if(attributeList.size() <= attributeGroupIndex.getKeyAtValue(i).size())
            {
                indexToChoose = i;
                break;
            }
        }
        return indexToChoose;
    }
    
    int AlignedEntityBackend::getSubsetGroupArrayPosition(AttributeList& attributeList) const
    {
        int result = -1;
        for(unsigned int i = 0; i < attributeGroupLocation.size(); i++)
        {
            bool found = true;

            AttributeList tempAttributeList = attributeGroupIndex.getKeyAtValue(i);
            for(unsigned int j = 0; j < attributeList.size(); j++)
            {
                if(!tempAttributeList.hasAttributes(attributeList))
                    found = false;
            }

            if(found)
            {
                result = attributeGroupLocation[i];
                break;
            }
        }
        return result;
    }

    void AlignedEntityBackend::swapDownEntityThroughGroups(const int startEntityPosition, const int stopGroupIndex, bool newGroup)
    {
        int swapFromIndex = startEntityPosition;
        for(int i = attributeGroupLocation.size() - 1; i > stopGroupIndex; i--)
        {
            int swapToIndex = attributeGroupLocation[i];
            posIdMap.swapValuesAtKeys(swapToIndex, swapFromIndex);
            dataArrays.swapData(swapToIndex, swapFromIndex);
            swapFromIndex = swapToIndex;
        }
        if(newGroup)
        {
            int swapToIndex = attributeGroupLocation[stopGroupIndex];
            posIdMap.swapValuesAtKeys(swapToIndex, swapFromIndex);
            dataArrays.swapData(swapToIndex, swapFromIndex);
        }
    }
    
    void AlignedEntityBackend::swapDownGroups(const int startIndex, const int stopIndex) 
    {
        for(int i = startIndex; i > stopIndex; i--)
        {
            attributeGroupIndex.swapKeysAtValues(i, i-1);
        }
    }

    void AlignedEntityBackend::setSlotsValid(const AttributeList& attributeList, const int position, const bool state)
    {
        for(auto attribute : attributeList.getSet())
        {
            dataArrays.setEntryValid(attribute, position, state);
        }
    }

    int AlignedEntityBackend::assignEntityAtEnd(int& arrayPos)
    {
        int createdId;

        if(freeEntityIds.size() > 0)
        {
            createdId = freeEntityIds.top();
            freeEntityIds.pop();
        }
        else
        {
            if(nextEntityId == std::numeric_limits<uint32_t>::max())
            {
                std::stringstream ss;
                ss << "Error! Cannot have more than uint32_t (" << std::numeric_limits<uint32_t>::max() << ") entities!\n";
                throw InvalidIdException(ss.str());
            }
            createdId = nextEntityId;
            nextEntityId++;
        }
        int newEntityArrayPosition = nextEmptyArraySlot;
        nextEmptyArraySlot++;
        dataArrays.setMinimumArrayLength(newEntityArrayPosition + 1);

        posIdMap.addKeyValuePair(newEntityArrayPosition, createdId);
        arrayPos = newEntityArrayPosition;
        return createdId;
    }
    
    void AlignedEntityBackend::validateAttributeList(AttributeList attributeList) const
    {
        if(attributeList.size() == 0)
        {
            throw InvalidAttributeException("Error! Zero attributes given", 0);
        }

        for(auto& attribute : attributeList.getSet())
        {
            if(!dataArrays.attributeIsValid(attribute))
            {
                throw InvalidAttributeException("Error! Invalid attribute given: ", attribute);
            }
        }
    }

    int AlignedEntityBackend::getAttributeGroupIndexFromPosition(int position) const
    {
        int groupAmount = attributeGroupIndex.size();

        int index = -1;
        for(int i = 0; i < groupAmount; i++)
        {
            index = i;
            
            if(attributeGroupLocation[i] > position)
            {
                index--;
                break;
            }
        }

        return index;
    }

    int AlignedEntityBackend::getLastDataOfGroup(unsigned int currentGroup) const
    {
        if(currentGroup == attributeGroupLocation.size() - 1)
            return nextEmptyArraySlot - 1;
        else
            return attributeGroupLocation[currentGroup + 1] - 1;
    }
    
    void AlignedEntityBackend::removeAttributeGroup(unsigned int group)
    {
        attributeGroupLocation.erase(attributeGroupLocation.begin() + group);

        int currentGroup = group;
        while(currentGroup < attributeGroupIndex.size() - 1)
        {
            attributeGroupIndex.swapKeysAtValues(currentGroup, currentGroup + 1);
            currentGroup++;
        }
        attributeGroupIndex.removeAtValue(currentGroup);
    }

    void AlignedEntityBackend::clear()
    {
        posIdMap.clear();
        attributeGroupIndex.clear();
        attributeGroupLocation.clear();
        dataArrays.clear();
        freeEntityIds = std::stack<EntityId>();
        nextEntityId = 0;
        nextEmptyArraySlot = 0;
    }

    DataMap AlignedEntityBackend::getIterableData(std::vector<std::string> stringList) const
    {
        DataMap result;
        if(attributeGroupLocation.size() == 0)
            return result;

        std::hash<std::string> hasher;
        AttributeList attributeList;
        for(auto& attributeString : stringList)
        {
            attributeList.addAttribute(hasher(attributeString));
        }

        int arrayPosition = getSubsetGroupArrayPosition(attributeList);

        if(arrayPosition == -1)
        {
            return result;
        }

        for(auto& attribute : attributeList.getSet())
        {
            DataContainer tempCont;
            tempCont.data = dataArrays.getDataPointer(attribute, arrayPosition);
            tempCont.dataLength = nextEmptyArraySlot - arrayPosition;
            tempCont.validity = dataArrays.getValidityPointer(attribute, arrayPosition);
            tempCont.validityStartBit = arrayPosition % 32;
            result.insert(std::pair<AttributeHash, DataContainer>(attribute,tempCont));
        }
        return result;
    }
    
}
