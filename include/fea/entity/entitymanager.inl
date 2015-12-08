template<class DataType>
const DataType& EntityManager::getAttribute(const EntityId id, const std::string& attribute) const
{
    FEA_ASSERT(mEntities.find(id) != mEntities.end(), "Trying to get the attribute '" + attribute + "' on entity entity ID '" + std::to_string(id) + "' but such an entity doesn't exist!");

    return mStorage.getData<DataType>(id, attribute);
}

template<class DataType>
DataType& EntityManager::getAttribute(const EntityId id, const std::string& attribute)
{
    FEA_ASSERT(mEntities.find(id) != mEntities.end(), "Trying to get the attribute '" + attribute + "' on entity entity ID '" + std::to_string(id) + "' but such an entity doesn't exist!");

    return mStorage.getData<DataType>(id, attribute);
}

    template<class DataType>
void EntityManager::setAttribute(const EntityId id, const std::string& attribute, DataType attributeData)
{
    FEA_ASSERT(mEntities.find(id) != mEntities.end(), "Trying to get the attribute '" + attribute + "' on entity entity ID '" + std::to_string(id) + "' but such an entity doesn't exist!");
    mStorage.setData(id, attribute, std::move(attributeData));
}

    template<class DataType>
void EntityManager::registerAttribute(const std::string& attribute)
{
    mStorage.registerAttribute<DataType>(attribute);
}
