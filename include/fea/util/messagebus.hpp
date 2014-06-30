#pragma once
#include <fea/config.hpp>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <typeindex>
#include <algorithm>
#include <fea/messaging/messagereceiver.hpp>
#include <fea/assert.hpp>

#define FEA_DECLARE_MESSAGE1(name)                      \
    struct name {};                                 \
using name##Receiver = fea::MessageReceiver< name >;

#define FEA_DECLARE_MESSAGE2(name, args)                      \
    struct name { args };                                 \
using name##Receiver = fea::MessageReceiver< name >;

#define _ARG2(_0, _1, _2, ...) _2
#define NARG2(...) _ARG2(__VA_ARGS__, 2, 1, 0)

#define _ONE_OR_TWO_ARGS_1(a) FEA_DECLARE_MESSAGE1(a)
#define _ONE_OR_TWO_ARGS_2(a, b) FEA_DECLARE_MESSAGE2(a,b)

#define __ONE_OR_TWO_ARGS(N, ...) _ONE_OR_TWO_ARGS_ ## N (__VA_ARGS__)
#define _ONE_OR_TWO_ARGS(N, ...) __ONE_OR_TWO_ARGS(N, __VA_ARGS__)

#define FEA_DECLARE_MESSAGE(...) _ONE_OR_TWO_ARGS(NARG2(__VA_ARGS__), __VA_ARGS__)

namespace fea
{
    class FEA_API MessageBus
    {
        public:
            template<class Message>
            void addSubscriber(const MessageReceiver<Message>& receiver);
            template<class Message>
            void removeSubscriber(const MessageReceiver<Message>& receiver);
            template<class Message>
            void send(const Message& mess);
        private:
            bool subscriptionExists(std::type_index id, MessageReceiverBase* receiver) const;
            std::unordered_map<std::type_index, std::vector<MessageReceiverBase*>> mSubscribers;
    };

#include <fea/messaging/messagebus.inl>
    /** @addtogroup Messaging
     *@{
     *  @class MessageBus
     *@}
     ***
     *  @class MessageBus
     *  @brief Class that manages Message sending.
     *
     *  It offers a way of subscribing to messages. It will keep track of the subscriptions and when messages are send, it will reroute these to the correct receivers.
     *  The type of the message can be anything. Even primitives like int or double can be subscribed to. Most of the time, the message type is a struct carrying the information needed. Due to that being the common case, Feather Kit defines a macro which eases the process of creating a message with a receiver: 
     *  @code
     *  FEA_DECLARE_MESSAGE(ResizedMessage, uint32_t width; uint32_t height;);
     *  @endcode
     *
     *  This line declares a struct called ResizedMessage carrying a width and a height. Furthermore it also declares an alias ResizedMessageReceiver which is equivalent to fea::MessageReceiver<ResizedMessage>.
     ***
     *  @fn void MessageBus::addSubscriber(const MessageReceiver<Message>& receiver)
     *  @brief Create a subscription for a receiver.
     *  
     *  The subscription will be valid until MessageBus::removeMessageSubscriber is called on the same receiver. The Message type subscribed to is the one given in the template argument. The receiver must inherit from the correct MessageReceiver to be able to subscribe to a message. If the subscriber is destroyed before the MessageBus, all of its subscriptions must be removed using MessageBus::removeMessageSubscriber.
     *  
     *  Assert/undefined behavior if an object tries to subscribe to the same Message type more than once.
     *  @tparam Message Type of the message to subscribe to.
     *  @param receiver The instance which will receive the messages.
     ***
     *  @fn void MessageBus::removeSubscriber(const MessageReceiver<Message>& receiver)
     *  @brief Remove a Message subscription.
     *
     *  Mostly used to remove subscriptions of an object that is about to be destroyed. Not doing this results in undefined behavior. The template parameter deterimines which type of Message is unsibscribed from.
     *
     *  Assert/undefined behavior if the subscription to remove doesn't exist.
     *
     *  @tparam Message The Message type to unsubscribe from.
     *  @param receiver Object to remove subscription for.
     ***
     *  @fn void MessageBus::send(const Message& mess)
     *  @brief Send a Message.
     *
     *  Messages sent using this function will be routed to any subscribers which subscribed to that particular message type. If there are no subscribers to a particular Message type, nothing will hapen.
     *  @tparam Message Type of the Message to send.
     *  @param mess Message instance to send.
     **/
}
