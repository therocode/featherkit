    template<class DataType>
    void EntityStorage::StorageEntity::setData(const std::string& attribute, const DataType& inData)
    {
        FEA_ASSERT(attributeData.find(attribute) != attributeData.end(), "Trying to set the attribute '" + attribute + "' on an entity which does not have said attribute!");
        auto& valuePointer = attributeData.at(attribute);

        if(!valuePointer)
            valuePointer = std::make_shared<DataType>(inData);
        else
            *std::static_pointer_cast<DataType>(valuePointer) = inData;
    }

    template<class DataType>
    const DataType& EntityStorage::StorageEntity::getData(const std::string& attribute) const
    {
        FEA_ASSERT(attributeData.find(attribute) != attributeData.end(), "Trying to get the attribute '" + attribute + "' on an entity which does not have said attribute!");
        auto& valuePointer = attributeData.at(attribute);

        FEA_ASSERT(valuePointer, "Calling getData on attribute '" + attribute + "' which is not initialized!");
        return *std::static_pointer_cast<DataType>(valuePointer);
    }

    template<class DataType>
    void EntityStorage::registerAttribute(const std::string& attribute)
    {
        FEA_ASSERT(mAttributes.find(attribute) == mAttributes.end(), "Trying to register attribute '" + attribute + "' as a '"  + std::type_index(typeid(DataType)).name() + std::string(" but there is already an attribute registered with that identifier!"));
        mAttributes.emplace(attribute, typeid(DataType));
    }

    template<class DataType>
    void EntityStorage::setData(const uint32_t id, const std::string& attribute, const DataType& inData)
    {
        FEA_ASSERT(mAttributes.find(attribute) != mAttributes.end(), "Trying to set the attribute '" + attribute + "' on an entity but such an attribute has not been registered!");
        FEA_ASSERT(std::type_index(typeid(DataType)) == mAttributes.at(attribute), "Trying to set attibute '" + attribute + "' as a '" + std::type_index(typeid(DataType)).name() + std::string(" but it is of type '") + std::string(mAttributes.at(attribute).name()) + "'");
        mEntities.at(id).setData(attribute, inData);
    }

    template<class DataType>
    const DataType& EntityStorage::getData(const uint32_t id, const std::string& attribute) const
    {
        FEA_ASSERT(mAttributes.find(attribute) != mAttributes.end(), "Trying to get the attribute '" + attribute + "' on an entity but such an attribute has not been registered!");
        FEA_ASSERT(std::type_index(typeid(DataType)) == mAttributes.at(attribute), "Trying to get attibute '" + attribute + "' as a '" + std::type_index(typeid(DataType)).name() + std::string(" but it is of type '") + std::string(mAttributes.at(attribute).name()) + "'");
        return mEntities.at(id).getData<DataType>(attribute);
    }
