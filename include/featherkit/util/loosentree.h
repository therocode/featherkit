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
            class Position
            {
                public:
                    float operator[](const int32_t i)
                    {
                        return coords[i];
                    }
                private:
                    float coords[Dimensions];
            };
            
            class Size
            {
                private:
                    float operator[](const int32_t i)
                    {
                        return widths[i];
                    }

                    bool operator<=(const Size& other)
                    {
                        for(uint32_t d = 0; d < Dimensions; d++)
                            if(widths[d] > other[d])
                                return false;

                        return true;
                    }

                    float widths[Dimensions];
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
            };

            struct Entry
            {

            };

            LooseNTree() 
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
                            std::cout << "i am id " << i << " and i want a child! I claim " << nextFreeIndex << " as mine!\n";
                            nodes[i].children[j] = nextFreeIndex++;
                            nodes[i].parent = i;
                        }
                    }
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

            void Add(uint32_t id, Position pos, Size s)
            {
                uint32_t depth;

                Size nextLooseBounds = size;
                for(depth = 0; depth <= Depth; depth++)
                {
                    if(!(s <= nextLooseBounds))
                    {
                        break;
                    }
                }

                //coords in the current depth grid = pos / nextLooseBounds 
            }

            ~LooseNTree()
            {
                delete [] nodes;
            }
        private:
            float size;

            Node* nodes;
            uint32_t allocatedNodesCount;
            uint32_t usedNodesCount;
    };
}
