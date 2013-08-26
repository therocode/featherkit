#include <iostream>
#include <set>
#include <unordered_map>

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

                    Vector operator*(const Vector& other) const
                    {
                        Vector result;
                        for(uint32_t d = 0; d < Dimensions; d++)
                            result[d] = coords[d] * other.coords[d];

                        return result;
                    }

                    Vector operator*(float multiplier) const
                    {
                        Vector result;
                        for(uint32_t d = 0; d < Dimensions; d++)
                            result[d] = coords[d] * multiplier;

                        return result;
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
                    for(uint32_t child = 0; child < pow(2, Dimensions); child++)
                    {
                        if(children[child] != 0)
                            nodes[children[child]].printNode(nodes);
                    }
                }

                void renderNode(Node* nodes, const Vector& pos, const Vector& size, uint32_t depth, uint32_t nodeId, std::unordered_multimap<uint32_t, uint32_t>& entries)
                {
                    uint32_t contentAmount = entries.count(nodeId);
                    glPointSize(20 - depth * 4.00);

                    if(contentAmount == 0)
                    {
                        glColor3f(0.0f, 1.0f, 1.0f);
                    }
                    else if(contentAmount == 1)
                    {
                        glColor3f(0.0f, 1.0f, 0.0f);
                    }
                    else
                    {
                        glColor3f(1.0f, 1.0f, 0.0f);
                    }

                    glBegin(GL_POINTS); // render with points
                    glVertex2f(pos[0], pos[1]); //display a point
                    glEnd();

                    const Vector newSize = size / 2.0f;


                    if(children[0])
                    {
                        nodes[children[0]].renderNode(nodes, Vector({pos[0] -newSize[0] / 2.0f, pos[1] -newSize[1] / 2.0f}),newSize, depth + 1, children[0], entries);
                    }
                    if(children[1])
                    {
                        nodes[children[1]].renderNode(nodes, Vector({pos[0] +newSize[0] / 2.0f, pos[1] -newSize[1] / 2.0f}),newSize, depth + 1, children[1], entries);
                    }
                    if(children[2])
                    {
                        nodes[children[2]].renderNode(nodes, Vector({pos[0] -newSize[0] / 2.0f, pos[1] +newSize[1] / 2.0f}),newSize, depth + 1, children[2], entries);
                    }
                    if(children[3])
                    {
                        nodes[children[3]].renderNode(nodes, Vector({pos[0] +newSize[0] / 2.0f, pos[1] +newSize[1] / 2.0f}),newSize, depth + 1, children[3], entries);
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
            }

            void add(uint32_t id, const Vector& pos, const Vector& s)
            {
                uint32_t depth;

                Vector nextLooseBounds = size;
                for(depth = 0; depth < Depth; depth++)
                {
                    if(!(s <= nextLooseBounds))
                    {
                        depth++; //one too much
                        break;
                    }
                    nextLooseBounds = nextLooseBounds / 2.0f;
                }
                placeEntryInDepth(id, pos, depth - 1); //correct it
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
                    //std::stringstream ss; 
                    //ss << "Error! Cannot remove subscription to message " << index.name() << " on receiver " << receiverPtr << " since the subscription does not exist!\n";
                    //throw MessageException(ss.str());
                }

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

            std::set<Entry> get(const Vector& point) const
            {
                std::set<Entry> result;

                getFromNode(point / size, 0, result);

                return result;
            }

            std::set<Entry> get(const Vector& start, const Vector& end) const
            {
                std::set<Entry> result;

                getFromNode(start / size, end / size, 0, result);

                return result;
            }

            void renderTree()
            {
                glTranslatef(size[0]/2.0f, size[1]/2.0f, 0.0f);
                nodes[0].renderNode(nodes, size / 2.0f, size, 0, 0, entries);
                glLoadIdentity();
            }

            void clear()
            {
                entries.clear();
                entryLocations.clear();
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

                for(uint32_t d = 0; d < depth; d++)
                {
                    uint32_t childIndex = 0;
                    for(uint32_t dim = 0; dim < Dimensions; dim++)
                    {
                        if(positionPercent[dim] > 0.5f)
                        {
                            childIndex += pow(2, dim);
                            positionPercent[dim] = (positionPercent[dim] - 0.5f) * 2.0f;
                        }
                        else
                        {
                            positionPercent[dim] = positionPercent[dim] * 2.0f;
                        }
                    }
                    targetNodeIndex = currentNode->children[childIndex];
                    currentNode = &nodes[currentNode->children[childIndex]];
                }
                entries.emplace(targetNodeIndex, entry);
                entryLocations.emplace(entry, targetNodeIndex);
            }

            void getFromNode(const Vector& positionPercentage, uint32_t nodeId, std::set<Entry>& result) const
            {
                auto contained = entries.equal_range(nodeId);
                
                for(auto iter = contained.first; iter != contained.second; iter++)
                {
                    result.insert(iter->second);
                }

                bool overHalf[Dimensions];

                for(uint32_t child = 0; child < Pow<2, Dimensions>::value; child++)
                {
                    if(nodes[nodeId].children[child] == 0)
                    {
                        continue;
                    }

                    bool wasInside = true;
                    for(uint32_t dim = 0; dim < Dimensions; dim++)
                    {
                        float moveIt = ((float)((uint32_t)(child / pow(2, dim)) % 2) - 0.5f) / 2.0f;
                        overHalf[dim] = moveIt > 0.0f;

                        if(positionPercentage[dim] < moveIt || positionPercentage[dim] > 1.0f + moveIt)
                        {
                            wasInside = false;
                            break;
                        }
                    }

                    if(wasInside)
                    {
                        Vector percentAdapted = positionPercentage;
                        for(uint32_t dim = 0; dim < Dimensions; dim++)
                        {
                            if(overHalf[dim])
                            {
                                percentAdapted[dim] = (percentAdapted[dim] - 0.5f) * 2.0f;
                            }
                            else
                            {
                                percentAdapted[dim] = percentAdapted[dim] * 2.0f;
                            }
                        }

                        getFromNode(percentAdapted, nodes[nodeId].children[child], result);
                    }
                }
            }

            void getFromNode(const Vector& startPercentage, const Vector& endPercentage, uint32_t nodeId, std::set<Entry>& result) const
            {
                auto contained = entries.equal_range(nodeId);
                
                for(auto iter = contained.first; iter != contained.second; iter++)
                {
                    result.insert(iter->second);
                }

                bool overHalf[Dimensions];

                for(uint32_t child = 0; child < Pow<2, Dimensions>::value; child++)
                {
                    if(nodes[nodeId].children[child] == 0)
                    {
                        continue;
                    }

                    bool wasInside = true;
                    for(uint32_t dim = 0; dim < Dimensions; dim++)
                    {
                        float moveIt = ((float)((uint32_t)(child / pow(2, dim)) % 2) - 0.5f) / 2.0f;
                        overHalf[dim] = moveIt > 0.0f;

                        if(endPercentage[dim] < moveIt || startPercentage[dim] > 1.0f + moveIt)
                        {
                            wasInside = false;
                            break;
                        }
                    }

                    if(wasInside)
                    {
                        Vector startPercentAdapted = startPercentage;
                        Vector endPercentAdapted = endPercentage;
                        for(uint32_t dim = 0; dim < Dimensions; dim++)
                        {
                            if(overHalf[dim])
                            {
                                startPercentAdapted[dim] = (startPercentAdapted[dim] - 0.5f) * 2.0f;
                                endPercentAdapted[dim] = (endPercentAdapted[dim] - 0.5f) * 2.0f;
                            }
                            else
                            {
                                startPercentAdapted[dim] = startPercentAdapted[dim] * 2.0f;
                                endPercentAdapted[dim] = endPercentAdapted[dim] * 2.0f;
                            }
                        }

                        getFromNode(startPercentAdapted, endPercentAdapted, nodes[nodeId].children[child], result);
                    }
                }
            }

            void setSize(const Vector& s)
            {
                size = s;
            }

            Vector size;

            Node* nodes;
            uint32_t allocatedNodesCount;
            uint32_t usedNodesCount;
            std::unordered_multimap<uint32_t, Entry> entries;
            std::unordered_map<uint32_t, uint32_t> entryLocations;
    };
}
