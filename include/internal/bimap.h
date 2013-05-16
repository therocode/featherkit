#pragma once
#include <map>
namespace windgale
{
    ////////
    //Class: BiMap
    //
    //This class template serves as a way to get bidirectional maps. The normal std::maps are one-way. By maintaining two identical maps where the second one is reversed (values are keys and keys are values), a two-way structure is achieved!

    template <class TypeA, class TypeB>

        class BiMap
        {
            public:
                void addKeyValuePair(const TypeA key, const TypeB value)
                {
                    forwardMap.insert(std::pair<TypeA, TypeB>(key, value));
                    backwardMap.insert(std::pair<TypeB, TypeA>(value, key));
                }
                void removeAtKey(const TypeA key)
                {
                    backwardMap.erase(forwardMap.at(key));
                    forwardMap.erase(key);
                }
                void removeAtValue(const TypeB value)
                {
                    forwardMap.erase(backwardMap.at(value));
                    backwardMap.erase(value);
                }
                //Takes two keys, then swaps the values associated with these keys around.
                void swapValuesAtKeys(const TypeA key1, const TypeA key2)
                {
                    TypeB forwardValue1 = forwardMap.at(key1);
                    TypeB forwardValue2 = forwardMap.at(key2);

                    forwardMap.at(key2) = forwardValue1;
                    forwardMap.at(key1) = forwardValue2;

                    TypeA backwardValue1 = backwardMap.at(forwardValue1);
                    TypeA backwardValue2 = backwardMap.at(forwardValue2);

                    backwardMap.at(forwardValue2) = backwardValue1;
                    backwardMap.at(forwardValue1) = backwardValue2;
                }
                //See previous function
                void swapKeysAtValues(const TypeB value1, const TypeB value2)
                {
                    TypeA backwardValue1 = backwardMap.at(value1);
                    TypeA backwardValue2 = backwardMap.at(value2);

                    backwardMap.at(value2) = backwardValue1;
                    backwardMap.at(value1) = backwardValue2;

                    TypeB forwardValue1 = forwardMap.at(backwardValue1);
                    TypeB forwardValue2 = forwardMap.at(backwardValue2);

                    forwardMap.at(backwardValue2) = forwardValue1;
                    forwardMap.at(backwardValue1) = forwardValue2;
                }
                TypeB getValueAtKey(const TypeA key) const
                {
                    return forwardMap.at(key);
                }
                TypeA getKeyAtValue(const TypeB value) const
                {
                    return backwardMap.at(value);
                }
                int getItemCount() const
                {
                    return forwardMap.size();
                }
                bool keyExists(TypeA key) const
                {
                    return (forwardMap.find(key) != forwardMap.end());
                }
                bool valueExists(TypeB value) const
                {
                    return (backwardMap.find(value) != backwardMap.end());
                }
                void clear()
                {
                    forwardMap.clear();
                    backwardMap.clear();
                }
            private:
                std::map<TypeA, TypeB> forwardMap;
                std::map<TypeB, TypeA> backwardMap;
        };
}
