#include <featherkit/entity/attributelist.h>
#include <sstream>

namespace fk
{
    void AttributeList::addAttribute(AttributeHash attribute)
    {
        attributeSet.insert(attribute);
    }

    size_t AttributeList::size() const
    {
        return attributeSet.size();
    }

    const std::set<AttributeHash>& AttributeList::getSet() const
    {
        return attributeSet;
    }
    
    bool AttributeList::hasAttributes(const AttributeList& attributes) const
    {
        for(auto attribute : attributes.attributeSet)
        {
            if(attributeSet.find(attribute) == attributeSet.end())
                return false;
        }
        return true;
    }

    bool AttributeList::operator==(const AttributeList& other) const
    {
        if(attributeSet.size() != other.attributeSet.size())
            return false;
        else
        {
            auto iter1 = attributeSet.begin();
            auto iter2 = other.attributeSet.begin();
            while(iter1 != attributeSet.end())
            {
                AttributeHash thisHash = *iter1;
                AttributeHash otherHash = *iter2;
                if(thisHash != otherHash)
                    return false;

                iter1++;
                iter2++;
            }
        }
        return true;
    }
    
    bool AttributeList::operator!=(const AttributeList& other) const
    {
        return !(*this == other);
    }

    bool AttributeList::operator<(const AttributeList& other) const
    {
        if(attributeSet.size() < other.attributeSet.size())
            return true;
        else if(attributeSet.size() > other.attributeSet.size())
            return false;
        else
        {
            auto iter1 = attributeSet.begin();
            auto iter2 = other.attributeSet.begin();
            while(iter1 != attributeSet.end())
            {
                AttributeHash thisHash = *iter1;
                AttributeHash otherHash = *iter2;
                if(thisHash < otherHash)
                    return true;
                else if(thisHash > otherHash)
                    return false;

                iter1++;
                iter2++;
            }
        }
        return false;
    }

    bool AttributeList::operator>(const AttributeList& other) const
    {
        if(attributeSet.size() > other.attributeSet.size())
            return true;
        else if(attributeSet.size() < other.attributeSet.size())
            return false;
        else
        {
            auto iter1 = attributeSet.begin();
            auto iter2 = other.attributeSet.begin();
            while(iter1 != attributeSet.end())
            {
                AttributeHash thisHash = *iter1;
                AttributeHash otherHash = *iter2;
                if(thisHash > otherHash)
                    return true;
                else if(thisHash < otherHash)
                    return false;

                iter1++;
                iter2++;
            }
        }
        return false;
    }

    bool AttributeList::operator<=(const AttributeList& other) const
    {
        return attributeSet.size() <= other.attributeSet.size();
    }

    bool AttributeList::operator>=(const AttributeList& other) const
    {
        return attributeSet.size() >= other.attributeSet.size();
    }
}
