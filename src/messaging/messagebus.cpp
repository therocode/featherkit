#include <featherkit/messaging/messagebus.h>

namespace fea
{
    bool MessageBus::subscriptionExists(std::type_index id, MessageReceiverBase* receiver) const
    {
        const auto listIterator = mSubscribers.find(id);

        if(listIterator == mSubscribers.end())
            return false;

        const auto& list = listIterator->second;
        bool existed = false;


        for(const auto subscriber : list)
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
