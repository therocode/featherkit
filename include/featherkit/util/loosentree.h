#include <set>
#include <sstream>
#include <unordered_map>
#include <featherkit/assert.h>

namespace fea
{
    constexpr int32_t Pow(int32_t base, int32_t exponent)
    {
        return(expo != 0 )? base * Pow(base, exponent -1) : 1;
    }

    constexpr int32_t NodeAmount(int32_t depth, int32_t dimensions, int32_t recursion)
    {
        return(recursion != 0)? (Pow(2, dimensions * recursion) + NodeAmount(depth, dimensions, recursion+1)) : 1;
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
                        float* start = mCoords;
                        for(auto coord : args)
                        {
                            *start = coord;
                            start++;
                        }
                    }

                    float& operator[](const int32_t i)
                    {
                        return mCoords[i];
                    }

                    float operator[](const int32_t i) const
                    {
                        return mCoords[i];
                    }

                    bool operator<=(const Vector& other) const
                    {
                        for(uint32_t d = 0; d < Dimensions; d++)
                            if(mCoords[d] > other.mCoords[d])
                                return false;

                        return true;
                    }

                    Vector operator*(const Vector& other) const
                    {
                        Vector result;
                        for(uint32_t d = 0; d < Dimensions; d++)
                            result[d] = mCoords[d] * other.mCoords[d];

                        return result;
                    }

                    Vector operator*(float multiplier) const
                    {
                        Vector result;
                        for(uint32_t d = 0; d < Dimensions; d++)
                            result[d] = mCoords[d] * multiplier;

                        return result;
                    }

                    Vector operator/(const Vector& other) const
                    {
                        Vector result;
                        for(uint32_t d = 0; d < Dimensions; d++)
                            result[d] = mCoords[d] / other.mCoords[d];

                        return result;
                    }

                    Vector operator/(float divisor) const
                    {
                        Vector result;
                        for(uint32_t d = 0; d < Dimensions; d++)
                            result[d] = mCoords[d] / divisor;

                        return result;
                    }

                    Vector& operator=(const Vector& other)
                    {
                        for(uint32_t d = 0; d < Dimensions; d++)
                            mCoords[d] = other.mCoords[d];
                        return *this;
                    }

                    bool isPositive() const
                    {
                        for(uint32_t d = 0; d < Dimensions; d++)
                            if(mCoords[d] <= 0.0f)
                                return false;
                        return true;
                    }

                private:

                    float mCoords[Dimensions];
            };

            struct Node
            {
                Node() : mParent(0)
                {
                    for(int32_t i = 0; i < Pow(2, Dimensions); i++)
                        mChildren[i] = 0;
                }
                uint32_t mChildren[Pow(2, Dimensions)];
                uint32_t mParent;
            };

        public:
            using TreeEntry = size_t;

            LooseNTree(const Vector& size) : mSize(size)
            {
                FEA_ASSERT(size.isPositive(), "Tree size must be bigger than zero in all dimensions!");

                if(StaticAllocation)
                {
                    //allocate all nodes ever and make them all used
                    mAllocatedNodesCount = NodeAmount(Depth, Dimensions, 0);
                    mNodes = new Node[mAllocatedNodesCount];
                    mUsedNodesCount = mAllocatedNodesCount;

                    //setup nodes
                    uint32_t nextFreeIndex = 1;
                    for(uint32_t i = 0; i < NodeAmount(Depth - 1, Dimensions, 0) - 1; i++)
                    {
                        for(uint32_t j = 0; j < Pow(2, Dimensions); j++)
                        {
                            mNodes[nextFreeIndex].mParent = i;
                            mNodes[i].mChildren[j] = nextFreeIndex++;
                        }
                    }
                }
                else
                {
                    //allocate a basic amount of 8 nodes, of which 1 will be used, the root.
                    mAllocatedNodesCount = 8;
                    mNodes = new Node[mAllocatedNodesCount];
                    mUsedNodesCount = 1;
                }
                
                for(uint32_t child = 0; child < Pow(2, Dimensions); child++)
                {
                    for(uint32_t dim = 0; dim < Dimensions; dim++)
                    {
                        mMoveCache[child][dim] = ((float)((uint32_t)(child / pow(2, dim)) % 2) - 0.5f) / 2.0f;
                    }
                }
            }

            void add(uint32_t id, const Vector& position, const Vector& size)
            {
                FEA_ASSERT(size.isPositive(), "Error! Added objects must have a size bigger than zero.");
                FEA_ASSERT(mEntryLocations.find(id) == mEntryLocations.end(), "Trying to add an object with ID '" + std::to_string(id) + " but that ID is already added!");
                
                for(uint32_t dim = 0; dim < Dimensions; dim++)
                {
                    FEA_ASSERT(position[dim]  >= 0.0f && position[dim] <= mSize[dim], "Trying to add object outside of the bounds of the tree!");
                }

                uint32_t depth;

                Vector nextLooseBounds = mSize;
                for(depth = 0; depth < Depth; depth++)
                {
                    if(!(size <= nextLooseBounds))
                    {
                        depth++; //one too much
                        break;
                    }
                    nextLooseBounds = nextLooseBounds / 2.0f;
                }
                placeTreeEntryInDepth(id, position, depth - 1); //correct it
            }

            void remove(uint32_t id)
            {
                FEA_ASSERT(mEntryLocations.find(id) != mEntryLocations.end(), "Trying to remove object ID '" + std::to_string(id) + "' which does not exist!");
                uint32_t previousNode = mEntryLocations.at(id);
                removeTreeEntry(id);

                if(!StaticAllocation)
                {
                    std::vector<uint32_t> nodesToCheck;
                    uint32_t currentNode = previousNode;
                    while(currentNode)
                    {
                        nodesToCheck.push_back(currentNode);
                        currentNode = mNodes[currentNode].mParent;
                    }
                    for(int32_t i = 0; i < nodesToCheck.size(); i++)
                    {
                        checkForRemoval(nodesToCheck[i], nodesToCheck);
                    }
                }
            }

            void move(uint32_t id, const Vector& position)
            {
                FEA_ASSERT(mEntryLocations.find(id) != mEntryLocations.end(), "Trying to remove object ID '" + std::to_string(id) + "' which does not exist!");

                for(uint32_t dim = 0; dim < Dimensions; dim++)
                {
                    FEA_ASSERT(position[dim]  >= 0.0f && position[dim] <= mSize[dim], "Trying to move object outside of the bounds of the tree!");
                }

                uint32_t depth = 0;

                uint32_t currentNodeId = mEntryLocations.at(id);

                while(currentNodeId != 0)
                {
                    depth++;
                    currentNodeId = mNodes[currentNodeId].mParent;
                }

                uint32_t previousNode = mEntryLocations.at(id);
                removeTreeEntry(id);
                placeTreeEntryInDepth(id, position, depth);

                if(!StaticAllocation)
                {
                    std::vector<uint32_t> nodesToCheck;
                    uint32_t currentNode = previousNode;
                    while(currentNode)
                    {
                        nodesToCheck.push_back(currentNode);
                        currentNode = mNodes[currentNode].mParent;
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

                getFromNode(point / mSize, 0, result);

                return result;
            }

            std::vector<TreeEntry> get(const Vector& start, const Vector& end) const
            {
                std::vector<TreeEntry> result;

                getFromNode(start / mSize, end / mSize, 0, result);

                return result;
            }

            void clear()
            {
                mEntries.clear();
                mEntryLocations.clear();
            }
 
            ~LooseNTree()
            {
                delete [] mNodes;
            }

        private:
            void placeTreeEntryInDepth(const TreeEntry& entry, const Vector& position, uint32_t depth)
            {
                Vector positionPercent = position / mSize;
                Node* currentNode = &mNodes[0];
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
                        targetNodeIndex = currentNode->mChildren[childIndex];
                        currentNode = &mNodes[currentNode->mChildren[childIndex]];
                    }
                    else
                    {
                        if(currentNode->mChildren[childIndex] == 0)
                        {
                            if(mUsedNodesCount == mAllocatedNodesCount)
                            {
                                uint32_t pointerDistance = currentNode - mNodes;
                                increaseSize();
                                currentNode = mNodes + pointerDistance;
                            }
                            
                            currentNode->mChildren[childIndex] = mUsedNodesCount;
                            mNodes[mUsedNodesCount].mParent = targetNodeIndex;
                            mUsedNodesCount++;
                        }
                        targetNodeIndex = currentNode->mChildren[childIndex];
                        currentNode = &mNodes[currentNode->mChildren[childIndex]];
                    }
                }
                mEntries.emplace(targetNodeIndex, entry);
                mEntryLocations.emplace(entry, targetNodeIndex);
            }

            void removeTreeEntry(uint32_t id)
            {
                auto range = mEntries.equal_range(mEntryLocations.at(id));
                bool existed = false;

                for(auto iter = range.first; iter != range.second; iter++)
                {
                    if(iter->second == id)
                    {
                        mEntries.erase(iter);
                        existed = true;
                        break;
                    }
                }
                mEntryLocations.erase(id);
            }

            void getFromNode(const Vector& positionPercentage, uint32_t nodeId, std::vector<TreeEntry>& result) const
            {
                auto contained = mEntries.equal_range(nodeId);
                
                for(auto iter = contained.first; iter != contained.second; iter++)
                {
                    result.push_back(iter->second);
                }

                bool overHalf[Dimensions];

                for(uint32_t child = 0; child < Pow(2, Dimensions); child++)
                {
                    if(mNodes[nodeId].mChildren[child] == 0)
                    {
                        continue;
                    }

                    bool wasInside = true;
                    for(uint32_t dim = 0; dim < Dimensions; dim++)
                    {
                        float moveIt = mMoveCache[child][dim];
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

                        getFromNode(percentAdapted, mNodes[nodeId].mChildren[child], result);
                    }
                }
            }

            void getFromNode(const Vector& startPercentage, const Vector& endPercentage, uint32_t nodeId, std::vector<TreeEntry>& result) const
            {
                auto contained = mEntries.equal_range(nodeId);
                
                for(auto iter = contained.first; iter != contained.second; iter++)
                {
                    result.push_back(iter->second);
                }

                bool overHalf[Dimensions];

                for(uint32_t child = 0; child < Pow(2, Dimensions); child++)
                {
                    if(mNodes[nodeId].mChildren[child] == 0)
                    {
                        continue;
                    }

                    bool wasInside = true;
                    for(uint32_t dim = 0; dim < Dimensions; dim++)
                    {
                        float moveIt = mMoveCache[child][dim];
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

                        getFromNode(startPercentAdapted, endPercentAdapted, mNodes[nodeId].mChildren[child], result);
                    }
                }
            }

            void setSize(const Vector& size)
            {
                mSize = size;
            }

            void increaseSize()
            {
                uint32_t newSize = mAllocatedNodesCount * 2;
                Node* newNodes = new Node[newSize];

                std::copy(mNodes, mNodes + mAllocatedNodesCount, newNodes);
                delete [] mNodes;
                mNodes = newNodes;

                mAllocatedNodesCount = newSize;
            }

            void decreaseSize()
            {
                uint32_t newSize = mAllocatedNodesCount / 4;
                Node* newNodes = new Node[newSize];

                std::copy(mNodes, mNodes + newSize, newNodes);
                delete [] mNodes;
                mNodes = newNodes;

                mAllocatedNodesCount = newSize;
            }

            void checkForRemoval(uint32_t nodeIndex, std::vector<uint32_t>& toCheck)
            {
                if(nodeIndex == 0)
                {
                    return;
                }

                if(mEntries.find(nodeIndex) == mEntries.end())
                {
                    Node* currentNode = &mNodes[nodeIndex];
                    for(uint32_t child = 0; child < Pow(2, Dimensions); child++)
                    {
                        if(currentNode->mChildren[child] != 0)
                        {
                            return;
                        }
                        
                    }
                    removeNode(nodeIndex, toCheck);
                }
            }

            void removeNode(uint32_t nodeIndex, std::vector<uint32_t>& toCheck)
            {
                uint32_t parentId = mNodes[nodeIndex].mParent;
                Node* parent = &mNodes[parentId];
                for(uint32_t child = 0; child < Pow(2, Dimensions); child++)
                {
                    if(parent->mChildren[child] == nodeIndex)
                    {
                        parent->mChildren[child] = 0;
                        break;
                    }
                }
                uint32_t lastNode = mUsedNodesCount - 1;
                mUsedNodesCount--;
                if(lastNode == nodeIndex)
                {
                    return;
                }

                for(auto& node : toCheck)
                {
                    if(node == lastNode)
                        node = nodeIndex;
                }

                Node* parentOfLast = &mNodes[mNodes[lastNode].mParent];
                for(uint32_t child = 0; child < Pow(2, Dimensions); child++)
                {
                    if(parentOfLast->mChildren[child] == lastNode)
                    {
                        parentOfLast->mChildren[child] = nodeIndex;
                        break;
                    }
                }
            
                Node* lastNodeP = &mNodes[lastNode];
                for(uint32_t child = 0; child < Pow(2, Dimensions); child++)
                {
                    if(lastNodeP->mChildren[child] != 0)
                        mNodes[lastNodeP->mChildren[child]].mParent = nodeIndex;
                }
                mNodes[nodeIndex].mParent = lastNodeP->mParent;
                lastNodeP->mParent = 0;
                for(uint32_t child = 0; child < Pow(2, Dimensions); child++)
                {
                    mNodes[nodeIndex].mChildren[child] = lastNodeP->mChildren[child];
                    lastNodeP->mChildren[child] = 0;
                }
                
                auto range = mEntries.equal_range(lastNode);
                std::vector<TreeEntry> entriesToMove;
                for(auto iter = range.first; iter != range.second; iter++)
                {
                    entriesToMove.push_back(iter->second);
                    mEntryLocations[iter->second] = nodeIndex;
                }
                mEntries.erase(lastNode);

                for(auto entry : entriesToMove)
                {
                    mEntries.emplace(nodeIndex, entry);
                }

                if(mUsedNodesCount <= mAllocatedNodesCount / 4 && mAllocatedNodesCount > 16)
                    decreaseSize();
            }

            Vector mSize;

            Node* mNodes;
            uint32_t mAllocatedNodesCount;
            uint32_t mUsedNodesCount;
            std::unordered_map<TreeEntry, uint32_t> mEntryLocations;
            std::unordered_multimap<uint32_t, TreeEntry> mEntries;
            float mMoveCache[Pow(2, Dimensions)][Dimensions];
    };

    /** @addtogroup Structure
     *@{
     *  @typedef LooseNTree::TreeEntry
     *  @class LooseNTree
     *@}
     ***
     *  @typedef LooseNTree::TreeEntry
     *  @brief An entry in the tree.
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
     *  @fn LooseNTree::LooseNTree(const Vector& size)
     *  @brief Construct a tree with the given size.
     *
     *  Assert/undefined behaviour if the size is zero or less in any of the dimensions.
     *  @param size Size.
     ***
     *  @fn void LooseNTree::add(uint32_t id, const Vector& position, const Vector& size)
     *  @brief Add an object to track.
     *  
     *  The added object must have a unique ID. If the object moves, the position must be updated using the LooseNTree::move function.
     *  Assert/undefined behaviour if the size is zero or less in any of the dimensions, if the given ID already exists in the tree, or if the position is outside of the bounds of the tree.
     *  @param id ID of the object to track.
     *  @param position Position of the object.
     *  @param size Size of the object. Given as an Axis aligned bounding box.
     ***
     *  @fn void LooseNTree::remove(uint32_t id)
     *  @brief Stop tracking an object.
     *  
     *  Assert/undefined behaviour if the object does not exist.
     *  @param id ID of the object to stop tracking.
     ***
     *  @fn void LooseNTree::move(uint32_t id, const Vector& position)
     *  @brief Move a tracked object.
     *
     *  This must be called to keep tracked objects up to date.
     *  Assert/undefined behaviour if the object does not exist or if target position is outside of the bounds of the tree.
     *  @param id ID of the object to move.
     *  @param position New position of the object.
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
