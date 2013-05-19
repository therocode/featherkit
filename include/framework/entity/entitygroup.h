#pragma once
#include <framework/entity/entity.h>
#include <set>

namespace windgale
{
    using EntitySet = std::set<WeakEntityPtr, std::owner_less<WeakEntityPtr> >;

    class EntityGroup
    {
        public:
            void add(const WeakEntityPtr entity);
            void add(const EntityGroup& entity);
            void remove(const WeakEntityPtr entity);
            void remove(const EntityGroup& entity);
            void clear();
            EntityGroup operator+(const EntityGroup& other) const;
            EntityGroup operator+(const WeakEntityPtr& entity) const;
            EntityGroup operator-(const EntityGroup& other) const;
            EntityGroup operator-(const WeakEntityPtr& entity) const;
            template<class DataType>
            void setAttribute(const std::string& attribute, const DataType* inData);
            WeakEntityPtr operator[](const int i) const;
            const EntitySet& getSet() const;
            size_t getCount();
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
}
