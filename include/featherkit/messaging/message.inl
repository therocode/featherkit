template<class tag, typename... DataTypes>
Message<tag, DataTypes...>::Message()
{
}

template<class tag, typename... DataTypes>
Message<tag, DataTypes...>::Message(DataTypes... data) : mData(std::forward<DataTypes>(data)...)
{
}

template<class tag, typename... DataTypes>
Message<tag, DataTypes...>::Message(const std::tuple<DataTypes...>& data) : mData(std::move(data))
{
}
