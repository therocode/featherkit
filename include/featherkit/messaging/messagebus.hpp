#pragma once
#include <vector>
#include <unordered_map>
#include <sstream>
#include <typeindex>
#include <algorithm>
#include <featherkit/messaging/messagereceiver.hpp>
#include <featherkit/assert.hpp>

namespace fea
{
    class MessageBus
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

    template<class Message>
    void MessageBus::addSubscriber(const MessageReceiver<Message>& receiver)
    {
        MessageReceiverBase* receiverPtr = (MessageReceiverBase*) &receiver;
        std::type_index index = std::type_index(typeid(Message));

        FEA_ASSERT(!subscriptionExists(index, receiverPtr), "Message receiver already subscribes to message " + std::string(index.name()) + "!");
        mSubscribers[index].push_back(receiverPtr);
    }

    template<class Message>
    void MessageBus::removeSubscriber(const MessageReceiver<Message>& receiver)
    {
        MessageReceiverBase* receiverPtr = (MessageReceiverBase*) &receiver;
        std::type_index index = std::type_index(typeid(Message));

        FEA_ASSERT(mSubscribers.find(index) != mSubscribers.end(), "Cannot remove subscription to message " + std::string(index.name()) + " since the subscription does not exist!");

        auto& list = mSubscribers.at(index);
        bool existed = false;

        for(auto iter = list.begin(); iter != list.end(); iter++)
        {
            if(*iter == receiverPtr)
            {
                list.erase(iter);
                existed = true;
                if(list.size() == 0)
                    mSubscribers.erase(index);
                break;
            }
        }

        FEA_ASSERT(existed, "Cannot remove subscription to message " + std::string(index.name()) + " since the subscription does not exist!");
    }

    template<class Message>
    void MessageBus::send(const Message& mess)
    {
        const auto listIterator = mSubscribers.find(std::type_index(typeid(Message)));
        if(listIterator != mSubscribers.end())
        {
            const auto& list = listIterator->second;
            if(list.size() > 0)
            {
                for(auto subscriber : list)
                    static_cast<MessageReceiver<Message>*>(subscriber)->handleMessage(mess);
            }
        }
    }
    /** @addtogroup Messaging
     *@{
     *  @class MessageBus
     *@}
     ***
     *  @class MessageBus
     *  @brief Class that manages Message sending.
     *
     *  It offers a way of subscribing to messages. It will keep track of the subscriptions and when messages are send, it will reroute these to the correct receivers.
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
