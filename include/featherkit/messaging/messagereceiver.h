#pragma once

namespace fea
{
    class MessageReceiverBase
    {
    };

    template<class MessageType>
        class MessageReceiver : public MessageReceiverBase
    {
        public:
            virtual void handleMessage(const MessageType& mess) = 0;
    };
    /** @addtogroup Messaging
     *@{
     *  @class MessageReceiverBase
     *  @class MessageReceiver
     *@}
     ***
     *  @class MessageReceiverBase
     *  @brief Base class for all MessageReceiver classes.
     *
     *  Serves as a common base for all MessageReceiver inheritors. Used internally in the MessageBus.
     ***
     *  @class MessageReceiver
     *  @brief Class template to inherit from to receive messages.
     *
     *  Any class that wishes to receive a message of type A, needs to inherit from MessageReceiver<A>. Doing this gives the class an ability to subscribe to messages of that type and messages of that type will be handed to the MessageReceiver::handleMessage function which must be implemented. If a class needs to handle various Message types, multiple inheritance should be used.
     *  @tparam MessageType Message type to be able to subscribe for.
     ***
     *  @fn virtual void MessageReceiver::handleMessage(const MessageType& mess) = 0
     *  @brief Receive and process a Message.
     *
     *  This function is used to receive subscribed messages. After a class has subscribed to a Message of a certain type, every time such a message is sent, this function will receive it. The message data is packed in an std::tuple and needs to be accessed using std::tie. This is an example of how to receive and handle a Message.
     *  @code
     *  //ResizedMessage definition. 
     *  //Sent when the window is resized, contains the dimensions of the new window size.
     *  //Data:
     *  //uint32_t - Width of the new size.
     *  //uint32_t - Height of the new size.
     *  struct Resized_tag{};
     *  using ResizedMessage = Message<Resized_tag, uint32_t, uint32_t>;
     *  using ResizedData = std::tuple<uint32_t, uint32_t>;
     *
     *  //...
     *
     *  void Handler::handleMessage(const ResizedMessage& mess)
     *  {
     *      uint32_t width;
     *      uint32_t height;
     *      std::tie(x, y) = mess.data;
     *      std::cout << "Received a resize message. The dimensions sent in the message was: " << width << " and " << height << "\n";
     *  }
     *  @endcode
     *  @param mess Message to handle.
     ***/
}
