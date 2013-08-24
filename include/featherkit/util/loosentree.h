#include <iostream>

namespace fea
{
    template<int32_t B, int32_t N>
    struct Pow 
    {
        enum { value = B*Pow<B, N-1>::value };
    };

    template< int32_t B >
    struct Pow<B, 0> 
    {
        enum { value = 1 };
    };

    template<uint32_t Depth, uint32_t Dimensions, uint32_t Recursion>
    struct NodeAmount
    {
        enum { value = Pow<2, Dimensions * Recursion>::value + NodeAmount<Depth, Dimensions, Recursion+1>::value };
    };

    template<uint32_t Depth, uint32_t Dimensions>
    struct NodeAmount<Depth, Dimensions, Depth>
    {
        enum { value = 1};
    };

    template<uint32_t Dimensions, uint32_t Depth, bool StaticAllocation>
    class LooseNTree
    {
        public:
            class Vector
            {
                public:
                    Vector()
                    {
                    }
                    Vector(std::initializer_list<float> args)
                    {
                        float* start = coords;
                        for(auto coord : args)
                        {
                            *start = coord;
                            start++;
                        }
                    }

                    float& operator[](const int32_t i)
                    {
                        return coords[i];
                    }

                    float operator[](const int32_t i) const
                    {
                        return coords[i];
                    }

                    bool operator<=(const Vector& other) const
                    {
                        for(uint32_t d = 0; d < Dimensions; d++)
                            if(coords[d] > other.coords[d])
                                return false;

                        return true;
                    }

                    Vector operator/(const Vector& other) const
                    {
                        Vector result;
                        for(uint32_t d = 0; d < Dimensions; d++)
                            result[d] = coords[d] / other.coords[d];

                        return result;
                    }

                    Vector operator/(float divisor) const
                    {
                        Vector result;
                        for(uint32_t d = 0; d < Dimensions; d++)
                            result[d] = coords[d] / divisor;

                        return result;
                    }

                    Vector& operator=(const Vector& other)
                    {
                        for(uint32_t d = 0; d < Dimensions; d++)
                            coords[d] = other.coords[d];
                        return *this;
                    }

                private:

                    float coords[Dimensions];
            };

            struct Node
            {
                Node() : empty(true), parent(0)
                {
                    for(int32_t i = 0; i < Pow<2, Dimensions>::value; i++)
                        children[i] = 0;
                }

                bool empty;
                uint32_t children[Pow<2, Dimensions>::value];
                uint32_t parent;

                void printNode(Node* nodes)
                {
                    std::cout << "HEJ!\n";

                    for(uint32_t child = 0; child < pow(2, Dimensions); child++)
                    {
                        std::cout << "checking kid number " << child << " and it has index " << children[child] << "\n";
                        if(children[child] != 0)
                            nodes[children[child]].printNode(nodes);
                    }
                }
            };

            using Entry = uint32_t;

            LooseNTree(float width, float height) : size({width, height})
            {
                if(StaticAllocation)
                {
                    //allocate all nodes ever and make them all used
                    allocatedNodesCount = NodeAmount<Depth, Dimensions, 0>::value;
                    nodes = new Node[allocatedNodesCount];
                    usedNodesCount = allocatedNodesCount;

                    //setup nodes
                    uint32_t nextFreeIndex = 1;
                    for(uint32_t i = 0; i < NodeAmount<Depth - 1, Dimensions, 0>::value - 1; i++)
                    {
                        for(uint32_t j = 0; j < Pow<2, Dimensions>::value; j++)
                        {
                            std::cout << "i am index " << i << " and i want a child! I claim " << nextFreeIndex << " as mine!\n";
                            nodes[nextFreeIndex].parent = i;
                            nodes[i].children[j] = nextFreeIndex++;
                        }
                    }
                    nodes[0].printNode(nodes);
                }
                else
                {
                    //allocate a basic amount of 8 nodes, of which 1 will be used, the root.
                    allocatedNodesCount = 8;
                    nodes = new Node[allocatedNodesCount];
                    usedNodesCount = 1;
                }
                std::cout << "Allocated: " << allocatedNodesCount << " used: " << usedNodesCount << " root node id is " << 0 << "\n";
            }

            void add(uint32_t id, float x, float y, float width, float height)////WTF!
            {
                add(id, Vector({x, y}), Vector({width, height}));
            }

            void add(uint32_t id, const Vector& pos, const Vector& s)
            {
                uint32_t depth;

                Vector nextLooseBounds = size;
                for(depth = 0; depth < Depth; depth++)
                {
                    std::cout << "testing depth " << depth + 1 << " with loose bounds being " << nextLooseBounds[0] << " " << nextLooseBounds[1] << "...\n";
                    if(!(s <= nextLooseBounds))
                    {
                        std::cout << "it doesn't fit so will use depth " << depth << "\n";
                        break;
                    }
                    nextLooseBounds = nextLooseBounds / 2.0f;
                    std::cout << "fits in this depth\n";
                }
                placeEntryInDepth(id, pos, depth);
            }
            
            void remove(uint32_t id)
            {
                auto range = entries.equal_range(entryLocations.at(id));
                bool existed = false;

                for(auto iter = range.first; iter != range.second; iter++)
                {
                    if(iter->second == id)
                    {
                        entries.erase(iter);
                        existed = true;
                        break;
                    }
                }
                entryLocations.erase(id);

                if(!existed)
                {
                    std::cout << "FAILED TO REMOVE\n";
                    //std::stringstream ss; 
                    //ss << "Error! Cannot remove subscription to message " << index.name() << " on receiver " << receiverPtr << " since the subscription does not exist!\n";
                    //throw MessageException(ss.str());
                }

            }

            void move(uint32_t id, float x, float y) //WTF!!!!!!!!!
            {
                move(id, Vector({x, y}));
            }

            void move(uint32_t id, const Vector& pos)
            {
                uint32_t depth = 0;

                uint32_t currentNodeId = entryLocations.at(id);

                while(currentNodeId != 0)
                {
                    depth++;
                    currentNodeId = nodes[currentNodeId].parent;
                }

                remove(id);
                placeEntryInDepth(id, pos, depth);
            }
 
            ~LooseNTree()
            {
                delete [] nodes;
            }
        private:
            void placeEntryInDepth(const Entry& entry, const Vector& pos, uint32_t depth)
            {
                Vector positionPercent = pos / size;
                Node* currentNode = &nodes[0];
                uint32_t targetNodeIndex = 0;

                std::cout << "going to find the right node now. it should be in depth " << depth << "\n";
                for(uint32_t d = 0; d < depth; d++)
                {
                    uint32_t childIndex = 0;
                    std::cout << "on depth " << d << " with percentage being " << positionPercent[0] << " " << positionPercent[1] << "\n";
                    for(uint32_t dim = 0; dim < Dimensions; dim++)
                    {
                        std::cout << "comparing axis " << dim << "\n";
                        if(positionPercent[dim] > 0.5f)
                        {
                            childIndex += pow(2, dim);
                            positionPercent[dim] = (positionPercent[dim] - 0.5f) * 2.0f;
                            std::cout << "it was over the half\n";
                        }
                        else
                        {
                            positionPercent[dim] = positionPercent[dim] * 2.0f;
                            std::cout << "it was under the half\n";
                        }
                    }
                    targetNodeIndex = currentNode->children[childIndex];
                    currentNode = &nodes[currentNode->children[childIndex]];
                }
                entries.emplace(targetNodeIndex, entry);
                entryLocations.emplace(entry, targetNodeIndex);


                std::cout << "the thing ended up in node index " << targetNodeIndex << "\n";
            }

            Vector size;

            Node* nodes;
            uint32_t allocatedNodesCount;
            uint32_t usedNodesCount;
            std::unordered_multimap<uint32_t, Entry> entries;
            std::unordered_map<uint32_t, uint32_t> entryLocations;
    };
}
