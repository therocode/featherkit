#pragma once

template<class tag, typename... DataTypes>
struct Message
{
    std::tuple<DataTypes...> data;
};
