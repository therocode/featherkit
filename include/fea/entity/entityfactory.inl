template<typename Function>
void EntityFactory::addDataType(const std::string& dataTypeName, Function parser)
{
    FEA_ASSERT(mRegistrators.find(dataTypeName) == mRegistrators.end(),"Trying to add data type '" + dataTypeName + "' but it already exists!");
    using Type = typename std::result_of<Function(const Parameters&)>::type;
    //Make attribute registrator
    mRegistrators[dataTypeName] = [this, parser](const std::string& attributeName)->Parser
    {
        mManager.registerAttribute<Type>(attributeName);
        //Make parser
        return [this, parser, attributeName](const std::string& params)->Setter
        {
            auto value = parser(splitByDelimeter(params, ','));
            //make setter.
            return [attributeName, value](EntityPtr& entity)
            {
                entity->setAttribute<Type>(attributeName, value);
            };
        };
    };
}

    template<typename Type>
void EntityFactory::addDataType(const std::string& dataTypeName)
{
    FEA_ASSERT(mRegistrators.find(dataTypeName) == mRegistrators.end(),"Trying to add data type '" + dataTypeName + "' but it already exists!");
    //Make attribute registrator
    mRegistrators[dataTypeName] = [this](const std::string& attributeName)->Parser
    {
        mManager.registerAttribute<Type>(attributeName);
        //Make parser
        return [attributeName](const std::string& params)->Setter
        {
            FEA_ASSERT(1 == 0, "Trying to register a template where a default value has been added to the attribute '" + attributeName + "' which doesn't have a parser function!");
            return [](EntityPtr& entity)
            {
            };
        };
    };
}
