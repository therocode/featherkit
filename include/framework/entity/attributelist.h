#pragma once
#include <framework/entity/common.h>
#include <set>

namespace windgale
{
    using AttributeHash = std::size_t;

    class AttributeList
    {
        public:
            void addAttribute(AttributeHash attribute);
            size_t getSize() const;
            const std::set<AttributeHash>& getSet() const;
            bool hasAttributes(AttributeList& attributes) const;
            bool operator==(const AttributeList& other) const;
            bool operator!=(const AttributeList& other) const;
            bool operator<(const AttributeList& other) const;
            bool operator>(const AttributeList& other) const;
            bool operator<=(const AttributeList& other) const;
            bool operator>=(const AttributeList& other) const;
        private:
            std::set<AttributeHash> attributeSet;
    };
}
