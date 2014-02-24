#include <featherkit/messaging/messagebus.h>

namespace fea
{
    bool MessageBus::subscriptionExists(std::type_index id, MessageReceiverBase* receiver) const
    {
        const auto& list = mSubscribers.find(id)->second;
        bool existed = false;

        for(auto subscriber : list)
        {
            if(subscriber == receiver)
            {
                existed = true;
                break;
            }
        }
        return existed;
    }
}
