#pragma once

namespace windbreeze
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
}
