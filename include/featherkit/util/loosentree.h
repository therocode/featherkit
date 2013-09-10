#include <set>
#include <sstream>
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
            class LooseNTreeException : public std::runtime_error
            {
                public:
                    LooseNTreeException(std::string message) : std::runtime_error(message) { }
                    //Entry id;
                    //Vector position;
                    //Vector size;
            };

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

                    bool isPositive() const
                    {
                        for(uint32_t d = 0; d < Dimensions; d++)
                            if(coords[d] <= 0.0f)
                                return false;
                        return true;
                    }

                private:

                    float coords[Dimensions];
            };

            struct Node
            {
                Node() : parent(0)
                {
                    for(int32_t i = 0; i < Pow<2, Dimensions>::value; i++)
                        children[i] = 0;
                }
                uint32_t children[Pow<2, Dimensions>::value];
                uint32_t parent;
            };

            using Entry = uint32_t;

            LooseNTree(const Vector& s) : size(s)
            {
                if(!s.isPositive())
                {
                    throw LooseNTreeException("Error! Cannot create a tree with a negative size");
                }

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
                }
                else
                {
                    //allocate a basic amount of 8 nodes, of which 1 will be used, the root.
                    allocatedNodesCount = 8;
                    nodes = new Node[allocatedNodesCount];
                    usedNodesCount = 1;
                }
                
                for(uint32_t child = 0; child < Pow<2, Dimensions>::value; child++)
                {
                    for(uint32_t dim = 0; dim < Dimensions; dim++)
                    {
                        moveCache[child][dim] = ((float)((uint32_t)(child / pow(2, dim)) % 2) - 0.5f) / 2.0f;
                    }
                }
            }

            void add(uint32_t id, const Vector& pos, const Vector& s)
            {
                if(!s.isPositive())
                {
                    throw LooseNTreeException("Error! Added objects must have a size bigger than zero.");
                }
                
                if(entryLocations.find(id) != entryLocations.end())
                {
                    std::stringstream ss;
                    ss << "Error! Cannot add id " << id << " twice.";
                    throw LooseNTreeException(ss.str());
                }

                for(uint32_t dim = 0; dim < Dimensions; dim++)
                {
                    if(pos[dim] < 0.0f || pos[dim] > size[dim])
                    {
                        std::stringstream ss;
                        ss << "Error! Cannot add id " << id << " out of the tree's bounds.";
                        throw LooseNTreeException(ss.str());
                    }
                }

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
                //std::cout << "added id " << id << " so now i am printing\n";
                //printNode(0);
            }

            void remove(uint32_t id)
            {
                if(entryLocations.find(id) == entryLocations.end())
                {
                    std::stringstream ss;
                    ss << "Error! Cannot remove id " << id << " since it doesn't exist.";
                    throw LooseNTreeException(ss.str());
                }
                
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

                //TODO: removing somehow

            }

            void move(uint32_t id, const Vector& pos)
            {
                if(entryLocations.find(id) == entryLocations.end())
                {
                    std::stringstream ss;
                    ss << "Error! Cannot move id " << id << " since it doesn't exist.";
                    throw LooseNTreeException(ss.str());
                }

                for(uint32_t dim = 0; dim < Dimensions; dim++)
                {
                    if(pos[dim] < 0.0f || pos[dim] > size[dim])
                    {
                        std::stringstream ss;
                        ss << "Error! Cannot move id " << id << " out of the tree's bounds.";
                        throw LooseNTreeException(ss.str());
                    }
                }

                uint32_t depth = 0;

                uint32_t currentNodeId = entryLocations.at(id);

                std::cout << "i want to check the depth of node " << currentNodeId << "\n";
                while(currentNodeId != 0)
                {
                    depth++;
                    currentNodeId = nodes[currentNodeId].parent;
                    std::cout << "now node id is " << currentNodeId << "\n";
                    if(depth > 15)
                    {
                        std::cout << "that's it, depth became fucked... time to die\n";
                       //printNode(0);
                        exit(4);
                    }
                }

                uint32_t previousNode = entryLocations.at(id);
                remove(id);
                if(!checkSane(0))
                {
                    std::cout << "wrong on sixth\n";
                    printNode(0);
                    exit(4);
                } 
                placeEntryInDepth(id, pos, depth);
                if(!checkSane(0))
                {
                    std::cout << "wrong on seventh\n";
                    printNode(0);
                    exit(4);
                } 

                if(!StaticAllocation)
                {
                    checkForRemoval(previousNode);
                if(!checkSane(0))
                {
                    std::cout << "wrong on eigth\n";
                    printNode(0);
                    exit(4);
                } 
                }
            }

            std::vector<Entry> get(const Vector& point) const
            {
                std::vector<Entry> result;

                getFromNode(point / size, 0, result);

                return result;
            }

            std::vector<Entry> get(const Vector& start, const Vector& end) const
            {
                std::vector<Entry> result;

                getFromNode(start / size, end / size, 0, result);

                return result;
            }

            void renderTree()
            {
                glTranslatef(size[0]/2.0f, size[1]/2.0f, 0.0f);
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
                if(!checkSane(0))
                {
                    std::cout << "wrong on fourth\n";
                    printNode(0);
                    exit(4);
                } 
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
                    if(StaticAllocation)
                    {
                        targetNodeIndex = currentNode->children[childIndex];
                        currentNode = &nodes[currentNode->children[childIndex]];
                    }
                    else
                    {
                        if(currentNode->children[childIndex] == 0)
                        {
                            if(usedNodesCount == allocatedNodesCount)
                            {
                                //std::cout << "size is " << usedNodesCount << " and allocated is " << allocatedNodesCount << " therefore we resize\n";
                                uint32_t pointerDistance = currentNode - nodes;
                                //std::cout << "pointer distance is " << pointerDistance << "\n";
                                if(!checkSane(0))
                                {
                                    std::cout << "wrong on ninth\n";
                                    printNode(0);
                                    exit(4);
                                } 
                                increaseSize();
                                if(!checkSane(0))
                                {
                                    std::cout << "wrong on tenth\n";
                                    printNode(0);
                                    exit(4);
                                } 
                                currentNode = nodes + pointerDistance;
                            }
                            
                            if(!checkSane(0))
                            {
                                std::cout << "wrong on twelwth\n";
                                printNode(0);
                                exit(4);
                            } 
                            //std::cout << "will place a kid in " << childIndex << "\n";
                            //här kanskeldas fdlASDFafsdfsdf
                            std::cout << "setting the child of the current node to be " << usedNodesCount << "\n";
                            currentNode->children[childIndex] = usedNodesCount;
                            std::cout << "setting the parent of that node to " << targetNodeIndex << "\n";
                            nodes[usedNodesCount].parent = targetNodeIndex;
                            std::cout << "plussing nodesCount\n";
                            usedNodesCount++;
                            //std::cout << "spawned a kid with ID " << usedNodesCount -1 << " and the child index is " << childIndex << " and the parent of this kid is " << targetNodeIndex << " and now it looks like:\n";
                            //printNode(0);
                            if(!checkSane(0))
                            {
                                std::cout << "wrong on eleventh\n";
                                printNode(0);
                                exit(4);
                            } 
                        }
                        targetNodeIndex = currentNode->children[childIndex];
                        currentNode = &nodes[currentNode->children[childIndex]];
                    }
                }
                entries.emplace(targetNodeIndex, entry);
                entryLocations.emplace(entry, targetNodeIndex);
                if(!checkSane(0))
                {
                    std::cout << "wrong on fifth\n";
                    printNode(0);
                    exit(4);
                } 
            }

            void getFromNode(const Vector& positionPercentage, uint32_t nodeId, std::vector<Entry>& result) const
            {
                auto contained = entries.equal_range(nodeId);
                
                for(auto iter = contained.first; iter != contained.second; iter++)
                {
                    result.push_back(iter->second);
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
                        float moveIt = moveCache[child][dim];
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

            void getFromNode(const Vector& startPercentage, const Vector& endPercentage, uint32_t nodeId, std::vector<Entry>& result) const
            {
                auto contained = entries.equal_range(nodeId);
                
                for(auto iter = contained.first; iter != contained.second; iter++)
                {
                    result.push_back(iter->second);
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
                        float moveIt = moveCache[child][dim];
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

            void increaseSize()
            {
                //std::cout << "resizing!\n";
                //std::cout << "before resize: \n";
                //printNode(0);
                uint32_t newSize = allocatedNodesCount * 2;
                Node* newNodes = new Node[newSize];

                std::copy(nodes, nodes + allocatedNodesCount, newNodes);
                delete [] nodes;
                nodes = newNodes;

                allocatedNodesCount = newSize;

                //std::cout << "after resize: \n";
                //printNode(0);
            }

            void checkForRemoval(uint32_t nodeIndex)
            {
                if(nodeIndex == 0)
                    return;

                if(entries.find(nodeIndex) == entries.end())
                {
                    Node* currentNode = &nodes[nodeIndex];
                    for(uint32_t child = 0; child < Pow<2, Dimensions>::value; child++)
                    {
                        if(currentNode->children[child] != 0)
                            return;
                        
                    }
                //std::cout << "\nshiiiet before removinf from the tree!\n";
                //printNode(0);
                    removeNode(nodeIndex);
                }
            }

            bool checkSane(uint32_t id)
            {
                std::set<uint32_t> passed;
                return checkSane(id, passed);
            }

            bool checkSane(uint32_t id, std::set<uint32_t>& passed)
            {
                bool sane = true;
                passed.insert(id);
                for(uint32_t child = 0; child < Pow<2, Dimensions>::value; child++)
                {
                    if(nodes[id].children[child] != 0)
                    {
                        if(passed.find(nodes[id].children[child]) != passed.end())
                        {
                            std::cout << "bloody hell, something is insane now, shit!\n";
                            sane = false;
                        }
                        sane = checkSane(nodes[id].children[child], passed) && sane;
                    }
                }
                return sane;
            }

            void printNode(uint32_t id)
            {
                std::set<uint32_t> passed;
                printNode(id, passed);
            }

            void printNode(uint32_t id, std::set<uint32_t>& passed)
            {
                passed.insert(id);
                if(id == 0)
                    std::cout << "\n";
                std::cout << "I am node id " << id << " and my kids are:  ";
                for(uint32_t child = 0; child < Pow<2, Dimensions>::value; child++)
                {
                    std::cout << nodes[id].children[child] << "  ";
                }
                std::cout << "\n";
                for(uint32_t child = 0; child < Pow<2, Dimensions>::value; child++)
                {
                    if(nodes[id].children[child] != 0)
                    {
                        std::cout << "diving into child number " << child << " (id " << nodes[id].children[child] << ") of node id " << id << "\n";
                        if(passed.find(nodes[id].children[child]) != passed.end())
                        {
                            std::cout << "bloody hell, something is wrong now, shit!\n";
                            return;
                        }
                        printNode(nodes[id].children[child], passed);
                    }
                }
            }

            void removeNode(uint32_t nodeIndex)
            {
                std::cout << "will erase " << nodeIndex << "\n";
                if(!checkSane(0))
                {
                    std::cout << "wrong on first\n";
                    printNode(0);
                    exit(4);
                } 
                //std::cout << "removing node number " << nodeIndex << "\n";
                uint32_t parentId = nodes[nodeIndex].parent;
                Node* parent = &nodes[parentId];
                for(uint32_t child = 0; child < Pow<2, Dimensions>::value; child++)
                {
                    //std::cout << "checking this child number " << parent->children[child] << " if it is similar to " << nodeIndex << "...\n";
                    if(parent->children[child] == nodeIndex)
                    {
                        //std::cout << "found the right child and is now eradicating it!\n";
                        parent->children[child] = 0;
                        break;
                    }
                }
                //std::cout << "\nshiiiet printing the tree!\n";
                //printNode(0);
                //exit(3);
                //MIGHT BE BAD UNDER THIS LINE HELVETTE!
                uint32_t lastNode = usedNodesCount - 1;
                usedNodesCount--;
                if(lastNode == nodeIndex)
                {
                    if(!checkSane(0))
                    {
                        std::cout << "wrong on third\n";
                        printNode(0);
                        exit(4);
                    } 
                    return;
                }

                Node* parentOfLast = &nodes[nodes[lastNode].parent];
                //BLIX
                bool found = false;
                for(uint32_t child = 0; child < Pow<2, Dimensions>::value; child++)
                {
                    std::cout << "checking this child to change its parent...\n";
                    if(parentOfLast->children[child] == lastNode)
                    {
                        std::cout << "found the right child and is now changing it!\n";
                        parentOfLast->children[child] = nodeIndex;
                        found = true;
                        break;
                    }
                }
                if(!found)
                {
                    std::cout << "wtf! and last node index was " << lastNode << "\n";
                    printNode(0);
                    exit(3);
                }
            
                Node* lastNodeP = &nodes[lastNode];
                for(uint32_t child = 0; child < Pow<2, Dimensions>::value; child++)
                {
                    if(lastNodeP->children[child] != 0)
                        nodes[lastNodeP->children[child]].parent = nodeIndex;
                    lastNodeP->children[child] = 0;
                }
                nodes[nodeIndex].parent = lastNodeP->parent;
                for(uint32_t child = 0; child < Pow<2, Dimensions>::value; child++)
                {
                    nodes[nodeIndex].children[child] = lastNodeP->children[child];
                }
                std::cout << "lowered usedNodesCount and it is now " << usedNodesCount << "\n";
                
                uint32_t ii = 0;
                auto range = entries.equal_range(lastNode);
                std::vector<Entry> entriesToMove;
                for(auto iter = range.first; iter != range.second; iter++)
                {
                    entriesToMove.push_back(iter->second);
                    entryLocations[iter->second] = nodeIndex;
                    ii++;
                }
                entries.erase(lastNode);

                for(auto entry : entriesToMove)
                {
                    entries.emplace(nodeIndex, entry);
                }
                std::cout << "done erasing " << nodeIndex << "\n";
                if(!checkSane(0))
                {
                    std::cout << "wrong on second\n";
                    printNode(0);
                    exit(4);
                } 
                //checkForRemoval(parentId); //note: important and this needs to be done, does the parentID need to be changed?
            }

            Vector size;

            Node* nodes;
            uint32_t allocatedNodesCount;
            uint32_t usedNodesCount;
            std::unordered_map<Entry, uint32_t> entryLocations;
            std::unordered_multimap<uint32_t, Entry> entries;
            float moveCache[Pow<2, Dimensions>::value][Dimensions];
    };
}
