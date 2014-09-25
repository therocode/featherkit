#pragma once
#include <fea/config.hpp>
#include <functional>
#include <vector>

namespace fea
{
    class MessageBus;
    template<class... MessageTypes>
    class MessageReceiver;
    template <class... MessageTypes>
    void subscribe(MessageBus&, MessageReceiver<MessageTypes...>&, bool = true);
    class FEA_API MessageReceiverBase
    {
    };

    template<class MessageType>
    class FEA_API MessageReceiverSingle : public MessageReceiverBase
    {
        public:
            virtual void handleMessage(const MessageType& message) = 0;
    };

    template<class... MessageTypes>
    class FEA_API MessageReceiver : public MessageReceiverSingle<MessageTypes>...
    {
        public:
            virtual ~MessageReceiver()
            {
                for(auto desubscriber : mDesubscribers)
                    desubscriber();
            }
        private:
            std::vector<std::function<void()>> mDesubscribers;
        template <class... Types>
        friend void subscribe(MessageBus& bus, MessageReceiver<Types...>&, bool);
    };
    /** @addtogroup Util
     *@{
     *  @class MessageReceiver
     *@}
     ***
     *  @class MessageReceiver
     *  @brief Class template to inherit from to receive messages.
     *
     *  Any class that wishes to receive a message of type A, needs to inherit from MessageReceiver<A>. Doing this gives the class an ability to subscribe to messages of that type and messages of that type will be handed to the MessageReceiver::handleMessage function which must be implemented. If a class needs to handle more than one message type, multiple parameters can be given, like so: MessageReceiver<A, B, C>
     *  @tparam MessageTypes Message types to be able to subscribe for.
     ***
     *  @fn virtual void MessageReceiver::handleMessage(const MessageType& message) = 0
     *  @brief Receive and process a Message.
     *
     *  This function is used to receive subscribed messages. After a class has subscribed to a Message of a certain type, every time such a message is sent, this function will receive it. This is an example of how to receive and handle a Message.
     *  @code
     *  //ResizedMessage definition. 
     *  //Sent when the window is resized, contains the dimensions of the new window size.
     *  struct ResizedMessage
     *  {
     *      uint32_t width;  //Width of the new size.
     *      uint32_t height; //Height of the new size.
     *  };
     *
     *  void Handler::handleMessage(const ResizedMessage& message)
     *  {
     *      std::cout << "Received a resize message. The dimensions sent in the message was: " << message.width << " and " << message.height << "\n";
     *  }
     *  @endcode
     *  @param message Message to handle.
     ***/
}
