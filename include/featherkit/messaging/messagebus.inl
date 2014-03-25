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
