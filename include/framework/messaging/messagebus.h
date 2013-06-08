#pragma once
#include <unordered_map>
#include <sstream>
#include <framework/messaging/messagereceiver.h>
#include <framework/messaging/messageidentifier.h>
#include <framework/messaging/messageexception.h>

namespace windbreeze
{
    class MessageBus
    {
        public:
            template<class Message>
            void addMessageSubscriber(const MessageReceiver<Message>& receiver);
            template<class Message>
            void removeMessageSubscriber(const MessageReceiver<Message>& receiver);
            template<class Message>
            void sendMessage(const Message& mess);
        private:
            bool subscriptionExists(uint32_t id, MessageReceiverBase* receiver) const;
            std::unordered_multimap<uint32_t, MessageReceiverBase*> subscribers;
    };

    template<class Message>
    void MessageBus::addMessageSubscriber(const MessageReceiver<Message>& receiver)
    {
        MessageIdentifier<Message> identifier;
        uint32_t messageId = identifier.id;
        MessageReceiverBase* receiverPtr = (MessageReceiverBase*) &receiver;

        bool existed = subscriptionExists(messageId, receiverPtr);

        if(!existed)
        {
            subscribers.emplace(messageId, receiverPtr);
        }
        else
        {
            std::stringstream ss;
            ss << "Error! Message receiver " << receiverPtr << " already subscribes to message " << messageId << "!\n";
            throw MessageException(ss.str());
        }
    }

    template<class Message>
    void MessageBus::removeMessageSubscriber(const MessageReceiver<Message>& receiver)
    {
        MessageIdentifier<Message> identifier;
        uint32_t messageId = identifier.id;
        MessageReceiverBase* receiverPtr = (MessageReceiverBase*) &receiver;

        auto range = subscribers.equal_range(messageId);
        bool existed = false;

        for(auto iter = range.first; iter != range.second; iter++)
        {
            if(iter->second == receiverPtr)
            {
                subscribers.erase(iter);
                existed = true;
                break;
            }
        }

        if(!existed)
        {
            std::stringstream ss;
            ss << "Error! Cannot remove subscription to message id " << messageId << " on receiver " << receiverPtr << " since the subscription does not exist!\n";
            throw MessageException(ss.str());
        }
    }

    template<class Message>
    void MessageBus::sendMessage(const Message& mess)
    {
        MessageIdentifier<Message> identifier;
        uint32_t messageId = identifier.id;

        auto range = subscribers.equal_range(messageId);
        if(range.first != subscribers.end() || range.second != subscribers.end())
        {
            for_each (range.first, range.second, [&](std::unordered_multimap<uint32_t, MessageReceiverBase*>::value_type& subscription){ ((MessageReceiver<Message>*)subscription.second)->handleMessage(mess);});
        }
    }
}
