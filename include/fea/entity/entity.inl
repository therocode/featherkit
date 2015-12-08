template<class DataType>
const DataType& Entity::getAttribute(const std::string& attribute) const
{
    FEA_ASSERT(!mEntityManager.findEntity(mId).expired(), "Trying to set the attribute '" + attribute + "' on entity ID '" + std::to_string(mId) + "' which has previously been deleted!");
    return mEntityManager.getAttribute<DataType>(mId, attribute);
}

template<class DataType>
DataType& Entity::getAttribute(const std::string& attribute)
{
    FEA_ASSERT(!mEntityManager.findEntity(mId).expired(), "Trying to set the attribute '" + attribute + "' on entity ID '" + std::to_string(mId) + "' which has previously been deleted!");
    return mEntityManager.getAttribute<DataType>(mId, attribute);
}

template<class DataType>
void Entity::setAttribute(const std::string& attribute, DataType value) const
{
    mEntityManager.setAttribute<DataType>(mId, attribute, std::move(value));
}
