#pragma once
#include <fea/config.hpp>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <typeindex>
#include <algorithm>
#include <fea/assert.hpp>
#include <fea/util/messagereceiver.hpp>

namespace fea
{
    class FEA_API MessageBus
    {
        public:
            template<class Message>
            void addSubscriber(const MessageReceiverSingle<Message>& receiver);
            template<class Message>
            void removeSubscriber(const MessageReceiverSingle<Message>& receiver);
            template<class Message>
            void send(const Message& mess);
        private:
            bool subscriptionExists(std::type_index id, MessageReceiverBase* receiver) const;
            std::unordered_map<std::type_index, std::vector<MessageReceiverBase*>> mSubscribers;
    };

    template <class MessageType>
    void subscribeToType(MessageBus& bus, MessageReceiverSingle<MessageType>& receiver, std::vector<std::function<void()>>& desubscribers, bool unsubscribe)
    {
        bus.addSubscriber<MessageType>(receiver);

        if(unsubscribe)
            desubscribers.push_back([&] () { bus.removeSubscriber<MessageType>(receiver);});
    }

    template<class... MessageTypes>
    void subscribe(MessageBus& bus, MessageReceiver<MessageTypes...>& receiver, bool unsubscribe)
    {
        std::vector<std::function<void()>> desubscribers;
        int _[] = {0, (subscribeToType<MessageTypes>(bus, receiver, desubscribers, unsubscribe), 0)...};
        (void)_;
        receiver.mDesubscribers = desubscribers;
    }

#include <fea/util/messagebus.inl>
    /** @addtogroup Util
     *@{
     *  @class MessageBus
     *  @fn void subscribe(MessageBus& bus, MessageReceiver<MessageTypes...>& receiver, bool unsubscribe = true)
     *@}
     ***
     *  @class MessageBus
     *  @brief Class that manages Message sending.
     *
     *  It offers a way of subscribing to messages. It will keep track of the subscriptions and when messages are send, it will reroute these to the correct receivers.
     *  The type of the message can be anything. Even primitives like int or double can be subscribed to. Most of the time, the message type is a struct carrying the information needed.
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
     ***
     *  @fn void subscribe(MessageBus& bus, MessageReceiver<MessageTypes...>& receiver, bool unsubscribe = true)
     *  @brief Subscribe to all messages for a receiver in a RAII manner.
     *
     *  When this function is called on a receiver, the receiver will be subscribed to all messages it is able to receive. Futhermore, upon destruction, all subscriptions will be cancelled unless automatic unsubscription is switched off.
     *
     *  @param bus Message bus which messages to subscribe to.
     *  @param receiver Instance to receive messages.
     *  @param unsubscribe Set this to false to disable automatic unsubscription
     *  @tparam Message types to subscribe to.
     **/
}
