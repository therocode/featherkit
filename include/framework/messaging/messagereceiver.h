#pragma once

class MessageReceiverBase
{
};

class MessageBus;

template<class MessageType>
class MessageReceiver : public MessageReceiverBase
{
    public:
        virtual void handleMessage(const MessageType& mess) = 0;
};
