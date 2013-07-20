#pragma once
#include <featherkit/entity/entity.h>
#include <set>

namespace fk
{
    using EntitySet = std::set<WeakEntityPtr, std::owner_less<WeakEntityPtr> >;

    class EntityGroup
    {
        public:
            void add(const WeakEntityPtr entity);
            void add(const EntityGroup& group);
            void remove(const WeakEntityPtr entity);
            void remove(const EntityGroup& group);
            void clear();
            EntityGroup operator+(const EntityGroup& other) const;
            EntityGroup operator+(const WeakEntityPtr& entity) const;
            EntityGroup operator-(const EntityGroup& other) const;
            EntityGroup operator-(const WeakEntityPtr& entity) const;
            template<class DataType>
            void setAttribute(const std::string& attribute, const DataType* inData);
            const EntitySet& getSet() const;
            size_t size();
            EntityGroup applyFilter(std::function<bool(WeakEntityPtr)> filterFunc);
            void removeInvalid();
        private:
            EntitySet entities;
    };
    template<class DataType>
    void EntityGroup::setAttribute(const std::string& attribute, const DataType* inData)
    {
        for(auto& entity : entities)
        {
            entity.lock()->setAttribute<DataType>(attribute, inData);
        }
    }
    /** @addtogroup EntitySystem
     *@{
     *  @class EntityGroup
     *@}
     ***
     *  @class EntityGroup
     *  @brief Utility class representing a group of Entity instances.
     *
     *  It is often useful to refer to a group of Entity instances. This is when this class comes in handy. An EntityGroup can contain zero or more Entity pointers. Is has functions to easily add and remove one or several Entity instances. It is also possible to filter them out based on an arbitrary criteria (see EntityGroup::ApplyFilter), and to set attributes for the whole group. The EntityGroup guarantees that the same Entity will never exist two times in a single EntityGroup instance.
     *
     *  Entities are represended using WeakEntityPtr instances.
     ***
     *  @fn void EntityGroup::add(const WeakEntityPtr entity)
     *  @brief Add an Entity to the group.
     *  @param entity Entity pointer to add.
     ***
     *  @fn void EntityGroup::add(const EntityGroup& group)
     *  @brief Add an EntityGroup to the group.
     *  @param group EntityGroup to add.
     ***
     *  @fn void EntityGroup::remove(const WeakEntityPtr entity)
     *  @brief Remove an Entity from the group.
     *  @param entity Entity pointer to remove.
     ***
     *  @fn void EntityGroup::remove(const EntityGroup& group)
     *  @brief Remove an EntityGroup from the group.
     *  @param group EntityGroup to remove.
     ***
     *  @fn void EntityGroup::clear()
     *  @brief Empty the group of all entities.
     ***
     *  @fn EntityGroup EntityGroup::operator+(const EntityGroup& other) const
     *  @brief Add up two EntityGroup instances to produce a third group consisting of the two original groups.
     *  @param other Group to combine with.
     *  @return Combined group.
     ***
     *  @fn EntityGroup EntityGroup::operator+(const WeakEntityPtr& other) const
     *  @brief Add up this EntityGroup with an Entity pointer to produce a group containing both the EntityGroup and the Entity.
     *  @param other Entity pointer to combine with.
     *  @return Combined group.
     ***
     *  @fn EntityGroup EntityGroup::operator-(const EntityGroup& other) const
     *  @brief Subtract an EntityGroup from this group to produce a third group consisting of the Entity instances found in this group, but not the ones found in the second group.
     *  @param other EntityGroup to subtract from this group.
     *  @return Subtracted group.
     ***
     *  @fn EntityGroup EntityGroup::operator-(const WeakEntityPtr& other) const
     *  @brief Subtract an Entity from this group to produce a group consisting of the Entity instances found in this group, minus the entity provided. If the entity does not exist, nothing will happen.
     *  @param other Entity to subtract.
     *  @return Subtracted group.
     ***
     *  @fn void EntityGroup::setAttribute(const std::string& attribute, const DataType* inData)
     *  @brief Set an attribute for all Entity instances currently in the group.
     *  @tparam Type of the attribute to set.
     *  @param attribute Name of the attribute to set.
     *  @param inData Pointer to a variable containing the value to set.
     ***
     *  @fn const EntitySet& EntityGroup::getSet() const
     *  @brief Access the internal set containing the Entity instances. Useful for looping through the enties.
     *  @return Set of the entities.
     ***
     *  @fn size_t EntityGroup::size()
     *  @brief Get the amount of Entity instances currently in the group.
     *  @return Amount of entities.
     ***
     *  @fn EntityGroup EntityGroup::applyFilter(std::function<bool(WeakEntityPtr)> filterFunc)
     *  @brief Filter out Entity instances based on a criterium.
     *
     *  The new filtered group will contain a subset of the Entity instances in this group. The subset is determined by a criterum given in the form of an std::function which could be for example a functor class or a lambda expression. They must however, take a WeakEntityPtr as an argument and return a bool.
     *
     *  The given std::function will be called for every entity in the group. If the function returns true for a given entity, it will be included in the returned subset group, otherwise it will not be included. By providing the logic for the std::function, it is possible to filter in many ways.
     *
     *  Example on how to keep the Entity instances that have a higher ID than 50:
     *  @code
     *  EntityGroup greaterThan50 = originalGroup.applyFilter([] (WeakEntityPtr e) {return e.lock()->getId() > 50;};
     *  @endcode
     *
     *  Example on how to filter out approximately 50% of the Entity instances randomly:
     *  @code
     *  EntityGroup randomised = originalGroup.applyFilter([] (WeakEntityPtr e) {return rand() % 2 == 0;};
     *  @endcode
     *
     *  @param filterFunc Function object containing the logic for the criterium. Should take a WeakEntityPtr as an argument and return a bool. Should return true for the entities to keep.
     *  @return The new subset group.
     ***
     *  @fn void EntityGroup::removeInvalid()
     *  @brief Searches through the EntityGroup and removes any Entity pointers that have become invalid due to the target Entity being deleted.
     ***/

}
