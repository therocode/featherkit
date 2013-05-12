#include "actiontrigger.h"

namespace windbreeze
{
    bool ActionTrigger::operator>(const ActionTrigger& other) const
    {
        if(type > other.type)
            return true;
        else if(type < other.type)
            return false;
        else
        {
            if(keyCode > other.keyCode)
                return true;
            else if(keyCode < other.keyCode)
                return false;
            else
            {
                if(gamepadId > other.gamepadId)
                    return true;
                else 
                    return false;
            }
        }
    }

    bool ActionTrigger::operator<(const ActionTrigger& other) const
    {
        if(type < other.type)
            return true;
        else if(type > other.type)
            return false;
        else
        {
            if(keyCode < other.keyCode)
                return true;
            else if(keyCode > other.keyCode)
                return false;
            else
            {
                if(gamepadId < other.gamepadId)
                    return true;
                else 
                    return false;
            }
        }
    }
}
