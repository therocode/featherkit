#pragma once
#include <set>
#include <stdlib.h>

namespace windgale
{
    using AttributeHash = std::size_t;

    class AttributeList
    {
        public:
            void addAttribute(AttributeHash attribute);
            size_t size() const;
            const std::set<AttributeHash>& getSet() const;
            bool hasAttributes(const AttributeList& attributes) const;
            bool operator==(const AttributeList& other) const;
            bool operator!=(const AttributeList& other) const;
            bool operator<(const AttributeList& other) const;
            bool operator>(const AttributeList& other) const;
            bool operator<=(const AttributeList& other) const;
            bool operator>=(const AttributeList& other) const;
        private:
            std::set<AttributeHash> attributeSet;
    };
    /** @addtogroup EntitySystem
     *@{
     *  @class AttributeList
     *
     *  @typedef AttributeHash
     *@}
     ***
     *  @typedef AttributeHash
     *  @brief Hashed representation of an Entity attribute. This is of the standard type size_t.
     ***
     *  @class AttributeList
     *  @brief Container class that can hold several AttributeHash instances. Used for the EntityBackend implementations.
     ***
     *  @fn void AttributeList::addAttribute(const AttributeHash attribute)
     *  @brief Add an AttributeHash to this AttributeList.
     *  @param attribute AttributeHash to add.
     ***
     *  @fn size_t AttributeList::size() const
     *  @brief Retrieve the current amount of AttributeHash instances currently in the AttributeList.
     *  @return The amount.
     ***
     *  @fn const std::set<AttributeHash>& AttributeList::getSet() const
     *  @brief Access the internal set containing the AttributeHash instances. Useful for looping through them for instance.
     *  @return Reference to the internal set.
     ***
     *  @fn bool AttributeList::hasAttributes(AttributeList& attributes) const
     *  @brief Check if this AttributeList contains all attributes of another AttributeList instance.
     *  @param attributes AttributeList to check for.
     *  @return True if the attributes existed.
     ***
     *  @fn bool AttributeList::operator==(const AttributeList& other) const
     *  @brief Test equality between two AttributeList instances.
     *  @param other Other instance to test against.
     *  @return True if the instances were equal, otherwise false.
     ***
     *  @fn bool AttributeList::operator!=(const AttributeList& other) const
     *  @brief Test inequality between two AttributeList instances.
     *  @param other Other instance to test against.
     *  @return True if the instances were not equal, otherwise false.
     ***
     *  @fn bool AttributeList::operator<(const AttributeList& other) const
     *  @brief Compare two AttributeList instances.
     *  @param other Other instance to compare to.
     *  @return True if the left side instance is less than the right side instance, otherwise false.
     ***
     *  @fn bool AttributeList::operator>(const AttributeList& other) const
     *  @brief Compare two AttributeList instances.
     *  @param other Other instance to compare to.
     *  @return True if the left side instance is greater than the right side instance, otherwise false.
     ***
     *  @fn bool AttributeList::operator<=(const AttributeList& other) const
     *  @brief Compare two AttributeList instances.
     *  @param other Other instance to compare to.
     *  @return True if the left side instance is less than or equal than the right side instance, otherwise false.
     ***
     *  @fn bool AttributeList::operator>=(const AttributeList& other) const
     *  @brief Compare two AttributeList instances.
     *  @param other Other instance to compare to.
     *  @return True if the left side instance is greater than or equal to the right side instance, otherwise false.
     ***/
}
