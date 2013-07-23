#include <featherkit/messaging/messagebus.h>

namespace fea
{
    bool MessageBus::subscriptionExists(std::type_index id, MessageReceiverBase* receiver) const
    {
        auto range = subscribers.equal_range(id);
        bool existed = false;

        for(auto iter = range.first; iter != range.second; iter++)
        {
            if(iter->second == receiver)
            {
                existed = true;
                break;
            }
        }
        return existed;
    }
}
