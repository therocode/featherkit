#include <set>
#include <sstream>
#include <unordered_map>

namespace fea
{
    constexpr int32_t Pow(int32_t base, int32_t expo)
    {
        return(expo != 0 )? base * Pow(base, expo -1) : 1;
    }

    constexpr int32_t NodeAmount(int32_t depth, int32_t dimensions, int32_t recursion)
    {
        return(recursion != 0)? (Pow(2, dimensions * recursion) + NodeAmount(depth, dimensions, recursion+1)) : 1;
    };

    class LooseNTreeException : public std::runtime_error
    {
        public:
            LooseNTreeException(std::string message) : std::runtime_error(message) { }
    };

    template<uint32_t Dimensions, uint32_t Depth, bool StaticAllocation>
    class LooseNTree
    {
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
                    for(int32_t i = 0; i < Pow(2, Dimensions); i++)
                        children[i] = 0;
                }
                uint32_t children[Pow(2, Dimensions)];
                uint32_t parent;
            };

        public:
            using TreeEntry = size_t;

            LooseNTree(const Vector& s) : size(s)
            {
                if(!s.isPositive())
                {
                    throw LooseNTreeException("Error! Tree size must be bigger than zero in all dimensions!");
                }

                if(StaticAllocation)
                {
                    //allocate all nodes ever and make them all used
                    allocatedNodesCount = NodeAmount(Depth, Dimensions, 0);
                    nodes = new Node[allocatedNodesCount];
                    usedNodesCount = allocatedNodesCount;

                    //setup nodes
                    uint32_t nextFreeIndex = 1;
                    for(uint32_t i = 0; i < NodeAmount(Depth - 1, Dimensions, 0) - 1; i++)
                    {
                        for(uint32_t j = 0; j < Pow(2, Dimensions); j++)
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
                
                for(uint32_t child = 0; child < Pow(2, Dimensions); child++)
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
                placeTreeEntryInDepth(id, pos, depth - 1); //correct it
            }

            void remove(uint32_t id)
            {
                if(entryLocations.find(id) == entryLocations.end())
                {
                    std::stringstream ss;
                    ss << "Error! Cannot remove id " << id << " since it doesn't exist.";
                    throw LooseNTreeException(ss.str());
                }
                uint32_t previousNode = entryLocations.at(id);
                removeTreeEntry(id);

                if(!StaticAllocation)
                {
                    std::vector<uint32_t> nodesToCheck;
                    uint32_t currentNode = previousNode;
                    while(currentNode)
                    {
                        nodesToCheck.push_back(currentNode);
                        currentNode = nodes[currentNode].parent;
                    }
                    for(int32_t i = 0; i < nodesToCheck.size(); i++)
                    {
                        checkForRemoval(nodesToCheck[i], nodesToCheck);
                    }
                }
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

                while(currentNodeId != 0)
                {
                    depth++;
                    currentNodeId = nodes[currentNodeId].parent;
                }

                uint32_t previousNode = entryLocations.at(id);
                removeTreeEntry(id);
                placeTreeEntryInDepth(id, pos, depth);

                if(!StaticAllocation)
                {
                    std::vector<uint32_t> nodesToCheck;
                    uint32_t currentNode = previousNode;
                    while(currentNode)
                    {
                        nodesToCheck.push_back(currentNode);
                        currentNode = nodes[currentNode].parent;
                    }
                    for(int32_t i = 0; i < nodesToCheck.size(); i++)
                    {
                        checkForRemoval(nodesToCheck[i], nodesToCheck);
                    }
                }
            }

            std::vector<TreeEntry> get(const Vector& point) const
            {
                std::vector<TreeEntry> result;

                getFromNode(point / size, 0, result);

                return result;
            }

            std::vector<TreeEntry> get(const Vector& start, const Vector& end) const
            {
                std::vector<TreeEntry> result;

                getFromNode(start / size, end / size, 0, result);

                return result;
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
            void placeTreeEntryInDepth(const TreeEntry& entry, const Vector& pos, uint32_t depth)
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
                                uint32_t pointerDistance = currentNode - nodes;
                                increaseSize();
                                currentNode = nodes + pointerDistance;
                            }
                            
                            currentNode->children[childIndex] = usedNodesCount;
                            nodes[usedNodesCount].parent = targetNodeIndex;
                            usedNodesCount++;
                        }
                        targetNodeIndex = currentNode->children[childIndex];
                        currentNode = &nodes[currentNode->children[childIndex]];
                    }
                }
                entries.emplace(targetNodeIndex, entry);
                entryLocations.emplace(entry, targetNodeIndex);
            }

            void removeTreeEntry(uint32_t id)
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
            }

            void getFromNode(const Vector& positionPercentage, uint32_t nodeId, std::vector<TreeEntry>& result) const
            {
                auto contained = entries.equal_range(nodeId);
                
                for(auto iter = contained.first; iter != contained.second; iter++)
                {
                    result.push_back(iter->second);
                }

                bool overHalf[Dimensions];

                for(uint32_t child = 0; child < Pow(2, Dimensions); child++)
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

            void getFromNode(const Vector& startPercentage, const Vector& endPercentage, uint32_t nodeId, std::vector<TreeEntry>& result) const
            {
                auto contained = entries.equal_range(nodeId);
                
                for(auto iter = contained.first; iter != contained.second; iter++)
                {
                    result.push_back(iter->second);
                }

                bool overHalf[Dimensions];

                for(uint32_t child = 0; child < Pow(2, Dimensions); child++)
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
                uint32_t newSize = allocatedNodesCount * 2;
                Node* newNodes = new Node[newSize];

                std::copy(nodes, nodes + allocatedNodesCount, newNodes);
                delete [] nodes;
                nodes = newNodes;

                allocatedNodesCount = newSize;
            }

            void decreaseSize()
            {
                uint32_t newSize = allocatedNodesCount / 4;
                Node* newNodes = new Node[newSize];

                std::copy(nodes, nodes + newSize, newNodes);
                delete [] nodes;
                nodes = newNodes;

                allocatedNodesCount = newSize;
            }

            void checkForRemoval(uint32_t nodeIndex, std::vector<uint32_t>& toCheck)
            {
                if(nodeIndex == 0)
                {
                    return;
                }

                if(entries.find(nodeIndex) == entries.end())
                {
                    Node* currentNode = &nodes[nodeIndex];
                    for(uint32_t child = 0; child < Pow(2, Dimensions); child++)
                    {
                        if(currentNode->children[child] != 0)
                        {
                            return;
                        }
                        
                    }
                    removeNode(nodeIndex, toCheck);
                }
            }

            void removeNode(uint32_t nodeIndex, std::vector<uint32_t>& toCheck)
            {
                uint32_t parentId = nodes[nodeIndex].parent;
                Node* parent = &nodes[parentId];
                for(uint32_t child = 0; child < Pow(2, Dimensions); child++)
                {
                    if(parent->children[child] == nodeIndex)
                    {
                        parent->children[child] = 0;
                        break;
                    }
                }
                uint32_t lastNode = usedNodesCount - 1;
                usedNodesCount--;
                if(lastNode == nodeIndex)
                {
                    return;
                }

                for(auto& node : toCheck)
                {
                    if(node == lastNode)
                        node = nodeIndex;
                }

                Node* parentOfLast = &nodes[nodes[lastNode].parent];
                for(uint32_t child = 0; child < Pow(2, Dimensions); child++)
                {
                    if(parentOfLast->children[child] == lastNode)
                    {
                        parentOfLast->children[child] = nodeIndex;
                        break;
                    }
                }
            
                Node* lastNodeP = &nodes[lastNode];
                for(uint32_t child = 0; child < Pow(2, Dimensions); child++)
                {
                    if(lastNodeP->children[child] != 0)
                        nodes[lastNodeP->children[child]].parent = nodeIndex;
                }
                nodes[nodeIndex].parent = lastNodeP->parent;
                lastNodeP->parent = 0;
                for(uint32_t child = 0; child < Pow(2, Dimensions); child++)
                {
                    nodes[nodeIndex].children[child] = lastNodeP->children[child];
                    lastNodeP->children[child] = 0;
                }
                
                auto range = entries.equal_range(lastNode);
                std::vector<TreeEntry> entriesToMove;
                for(auto iter = range.first; iter != range.second; iter++)
                {
                    entriesToMove.push_back(iter->second);
                    entryLocations[iter->second] = nodeIndex;
                }
                entries.erase(lastNode);

                for(auto entry : entriesToMove)
                {
                    entries.emplace(nodeIndex, entry);
                }

                if(usedNodesCount <= allocatedNodesCount / 4 && allocatedNodesCount > 16)
                    decreaseSize();
            }

            Vector size;

            Node* nodes;
            uint32_t allocatedNodesCount;
            uint32_t usedNodesCount;
            std::unordered_map<TreeEntry, uint32_t> entryLocations;
            std::unordered_multimap<uint32_t, TreeEntry> entries;
            float moveCache[Pow(2, Dimensions)][Dimensions];
    };

    /** @addtogroup Structure
     *@{
     *  @typedef LooseNTree::TreeEntry
     *  @class LooseNTreeException
     *  @class LooseNTree
     *@}
     ***
     *  @typedef LooseNTree::TreeEntry
     *  @brief An entry in the tree.
     ***
     *  @class LooseNTreeException
     *  @brief Exception used by the LooseNTree when something goes wrong.
     ***
     *  @fn LooseNTreeException::LooseNTreeException(std::string message)
     *  @brief Construct an exception to throw containing a message.
     *  @param message Message further describing the error.
     ***
     *  @class LooseNTree
     *  @brief Tree structure for keeping track of possibly overlapping objects.
     *
     *  This class generalises the concept of a loose quadtree/octree to make it work in any dimension. The amount of dimensions are passed as template parameters. The tree can be used to track objects with a position and size, to return possible overlaps. The node depth of the tree is also configured with a template parameter as well as if the tree should allocate all memory possibly needed at once, or if it should dynamically grow depending on need.
     *
     *  @tparam Dimensions Amount of dimensions. 2 makes a quadtree and 3 makes an octree.
     *  @tparam Depth Node depth. The deeper the tree, the bigger memory footprint, but might reduce false positives when returning possible overlaps.
     *  @tparam StaticAllocation If this is set to true, the tree allocates all nodes at once. This increases performance of the tree, but with bigger depth and dimensions, the memory usage quickly goes out of hand.
     ***
     *  @fn LooseNTree::LooseNTree(const Vector& s)
     *  @brief Construct a tree with the given size.
     *  @param s Size.
     ***
     *  @fn void LooseNTree::add(uint32_t id, const Vector& pos, const Vector& s)
     *  @brief Add an object to track.
     *  
     *  The added object must have a unique ID. If the object moves, the position must be updated using the LooseNTree::move function.
     *  @param id ID of the object to track.
     *  @param pos Position of the object.
     *  @param s Size of the object. Given as an Axis aligned bounding box.
     ***
     *  @fn void LooseNTree::remove(uint32_t id)
     *  @brief Stop tracking an object.
     *  
     *  @param id ID of the object to stop tracking.
     ***
     *  @fn void LooseNTree::move(uint32_t id, const Vector& pos)
     *  @brief Move a tracked object.
     *
     *  This must be called to keep tracked objects up to date.
     *  @param id ID of the object to move.
     *  @param pos New position of the object.
     ***
     *  @fn std::vector<TreeEntry> LooseNTree::get(const Vector& point) const
     *  @brief Return all tracked objects which possibly overlaps a certain point.
     *  @param point Point to check at.
     *  @return Objects that might overlap the point.
     ***
     *  @fn std::vector<TreeEntry> LooseNTree::get(const Vector& start, const Vector& end) const
     *  @brief Return all tracked objects which possible overlaps a certain box.
     *  @param start Starting corner of the box to check against.
     *  @param end Ending corner of the box to check against.
     *  @return Objects that might overlap the box.
     ***
     *  @fn void LooseNTree::clear()
     *  @brief Stop tracking all objects.
     ***
     *  @fn LooseNTree::~LooseNTree()
     *  @brief Destroy the tree.
     ***/
}
