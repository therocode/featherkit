#include <framework/messaging/messagebus.h>

bool MessageBus::subscriptionExists(uint32_t id, MessageReceiverBase* receiver) const
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
