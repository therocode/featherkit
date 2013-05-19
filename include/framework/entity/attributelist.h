#pragma once
#include <framework/entity/common.h>
#include <set>

namespace windgale
{
    class AttributeList
    {
        public:
            void addAttribute(AttributeHash attribute);
            size_t getSize();
            const std::set<AttributeHash>& getSet() const;
            bool hasAttributes(AttributeList& attributes);
            bool operator==(const AttributeList& other) const;
            bool operator!=(const AttributeList& other) const;
            bool operator<(const AttributeList& other) const;
            bool operator>(const AttributeList& other) const;
            bool operator<=(const AttributeList& other) const;
            bool operator>=(const AttributeList& other) const;
            std::string debug();
        private:
            std::set<AttributeHash> attributeSet;
    };
}
