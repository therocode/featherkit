#pragma once
#include <unordered_map>
#include <memory>

namespace fea
{
    template<typename Key, typename Value>
    class HashedStorage
    {
        public:
            void add(Key k, Value v)
            {
                storage.emplace(hasher(k), std::make_shared<Value>(v));
            }

            std::weak_ptr<Value> at(Key k)
            {
                return storage.at(hasher(k));
            }

            std::weak_ptr<Value> atId(size_t id)
            {
                return storage.at(id);
            }

            size_t getId(Key k)
            {
                return hasher(k);
            }
        private:
            std::hash<Key> hasher;
            std::unordered_map<size_t, std::shared_ptr<Value> > storage;
    };
}
