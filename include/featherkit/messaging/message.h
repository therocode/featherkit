#pragma once
#include <tuple>


namespace fea
{
    template<class tag, typename... DataTypes>
    struct Message
    {
        Message();
        Message(DataTypes... d);
        std::tuple<DataTypes...> data;
    };

    template<class tag, typename... DataTypes>
    Message<tag, DataTypes...>::Message()
    {
    }

    template<class tag, typename... DataTypes>
    Message<tag, DataTypes...>::Message(DataTypes... d) : data(d...)
    {
    }
    /** @addtogroup Messaging
     *@{
     *  @struct Message
     *@}
     ***
     *  @struct Message
     *  @brief Message holding data.
     *
     *  Data container class to be used with the messaging system. Can hold any type of data. The types of the data it stores is defined using variadic template arguments. In other words, any amount of template arguments can be used. Here is an example of how a window resized message could be defined.
     *  @code
     *  //ResizedMessage definition. 
     *  //Sent when the window is resized, contains the dimensions of the new window size.
     *  //Data:
     *  //uint32_t - Width of the new size.
     *  //uint32_t - Height of the new size.
     *  struct Resized_tag{};
     *  using ResizedMessage = Message<Resized_tag, uint32_t, uint32_t>;
     *  using ResizedData = std::tuple<uint32_t, uint32_t>;
     *  @endcode
     *  The empty struct Resized_tag serves as a way of making this Message type unique. The using statements are useful for creating aliases that are easy to work with.
     ***
     *  @fn Message::Message()
     *  @brief Construct a message.
     ***
     *  @fn Message::Message(DataTypes... d)
     *  @brief Construct a message containing the given data.
     *  @param d Data.
     ***
     *  @var Message::data 
     *  @brief Packed tuple of all data the Message is carrying.
     **/
}
