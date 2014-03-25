template<uint32_t Dimensions, uint32_t Depth, bool StaticAllocation>
LooseNTree<Dimensions, Depth, StaticAllocation>::Vector::Vector()
{
}

template<uint32_t Dimensions, uint32_t Depth, bool StaticAllocation>
LooseNTree<Dimensions, Depth, StaticAllocation>::Vector::Vector(std::initializer_list<float> args)
{
    float* start = mCoords;
    for(auto coord : args)
    {
        *start = coord;
        start++;
    }
}

template<uint32_t Dimensions, uint32_t Depth, bool StaticAllocation>
float& LooseNTree<Dimensions, Depth, StaticAllocation>::Vector::operator[](const int32_t i)
{
    return mCoords[i];
}

template<uint32_t Dimensions, uint32_t Depth, bool StaticAllocation>
float LooseNTree<Dimensions, Depth, StaticAllocation>::Vector::operator[](const int32_t i) const
{
    return mCoords[i];
}

template<uint32_t Dimensions, uint32_t Depth, bool StaticAllocation>
bool LooseNTree<Dimensions, Depth, StaticAllocation>::Vector::operator<=(const Vector& other) const
{
    for(uint32_t d = 0; d < Dimensions; d++)
        if(mCoords[d] > other.mCoords[d])
            return false;

    return true;
}

template<uint32_t Dimensions, uint32_t Depth, bool StaticAllocation>
typename LooseNTree<Dimensions, Depth, StaticAllocation>::Vector LooseNTree<Dimensions, Depth, StaticAllocation>::Vector::operator*(const Vector& other) const
{
    Vector result;
    for(uint32_t d = 0; d < Dimensions; d++)
        result[d] = mCoords[d] * other.mCoords[d];

    return result;
}

template<uint32_t Dimensions, uint32_t Depth, bool StaticAllocation>
typename LooseNTree<Dimensions, Depth, StaticAllocation>::Vector LooseNTree<Dimensions, Depth, StaticAllocation>::Vector::operator*(float multiplier) const
{
    Vector result;
    for(uint32_t d = 0; d < Dimensions; d++)
        result[d] = mCoords[d] * multiplier;

    return result;
}

template<uint32_t Dimensions, uint32_t Depth, bool StaticAllocation>
typename LooseNTree<Dimensions, Depth, StaticAllocation>::Vector LooseNTree<Dimensions, Depth, StaticAllocation>::Vector::operator/(const Vector& other) const
{
    Vector result;
    for(uint32_t d = 0; d < Dimensions; d++)
        result[d] = mCoords[d] / other.mCoords[d];

    return result;
}

template<uint32_t Dimensions, uint32_t Depth, bool StaticAllocation>
typename LooseNTree<Dimensions, Depth, StaticAllocation>::Vector LooseNTree<Dimensions, Depth, StaticAllocation>::Vector::operator/(float divisor) const
{
    Vector result;
    for(uint32_t d = 0; d < Dimensions; d++)
        result[d] = mCoords[d] / divisor;

    return result;
}

template<uint32_t Dimensions, uint32_t Depth, bool StaticAllocation>
typename LooseNTree<Dimensions, Depth, StaticAllocation>::Vector& LooseNTree<Dimensions, Depth, StaticAllocation>::Vector::operator=(const Vector& other)
{
    for(uint32_t d = 0; d < Dimensions; d++)
        mCoords[d] = other.mCoords[d];
    return *this;
}

template<uint32_t Dimensions, uint32_t Depth, bool StaticAllocation>
bool LooseNTree<Dimensions, Depth, StaticAllocation>::Vector::isPositive() const
{
    for(uint32_t d = 0; d < Dimensions; d++)
        if(mCoords[d] <= 0.0f)
            return false;
    return true;
}

template<uint32_t Dimensions, uint32_t Depth, bool StaticAllocation>
LooseNTree<Dimensions, Depth, StaticAllocation>::Node::Node() : mParent(0)
{
    for(int32_t i = 0; i < Pow(2, Dimensions); i++)
        mChildren[i] = 0;
}

template<uint32_t Dimensions, uint32_t Depth, bool StaticAllocation>
LooseNTree<Dimensions, Depth, StaticAllocation>::LooseNTree(const Vector& size) : mSize(size)
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

template<uint32_t Dimensions, uint32_t Depth, bool StaticAllocation>
void LooseNTree<Dimensions, Depth, StaticAllocation>::add(uint32_t id, const Vector& position, const Vector& size)
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

template<uint32_t Dimensions, uint32_t Depth, bool StaticAllocation>
void LooseNTree<Dimensions, Depth, StaticAllocation>::remove(uint32_t id)
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

template<uint32_t Dimensions, uint32_t Depth, bool StaticAllocation>
void LooseNTree<Dimensions, Depth, StaticAllocation>::move(uint32_t id, const Vector& position)
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

template<uint32_t Dimensions, uint32_t Depth, bool StaticAllocation>
std::vector<typename LooseNTree<Dimensions, Depth, StaticAllocation>::TreeEntry> LooseNTree<Dimensions, Depth, StaticAllocation>::get(const Vector& point) const
{
    std::vector<TreeEntry> result;

    getFromNode(point / mSize, 0, result);

    return result;
}

template<uint32_t Dimensions, uint32_t Depth, bool StaticAllocation>
std::vector<typename LooseNTree<Dimensions, Depth, StaticAllocation>::TreeEntry> LooseNTree<Dimensions, Depth, StaticAllocation>::get(const Vector& start, const Vector& end) const
{
    std::vector<TreeEntry> result;

    getFromNode(start / mSize, end / mSize, 0, result);

    return result;
}

template<uint32_t Dimensions, uint32_t Depth, bool StaticAllocation>
void LooseNTree<Dimensions, Depth, StaticAllocation>::clear()
{
    mEntries.clear();
    mEntryLocations.clear();
}

template<uint32_t Dimensions, uint32_t Depth, bool StaticAllocation>
LooseNTree<Dimensions, Depth, StaticAllocation>::~LooseNTree()
{
    delete [] mNodes;
}

template<uint32_t Dimensions, uint32_t Depth, bool StaticAllocation>
void LooseNTree<Dimensions, Depth, StaticAllocation>::placeTreeEntryInDepth(const TreeEntry& entry, const Vector& position, uint32_t depth)
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

template<uint32_t Dimensions, uint32_t Depth, bool StaticAllocation>
void LooseNTree<Dimensions, Depth, StaticAllocation>::removeTreeEntry(uint32_t id)
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

template<uint32_t Dimensions, uint32_t Depth, bool StaticAllocation>
void LooseNTree<Dimensions, Depth, StaticAllocation>::getFromNode(const Vector& positionPercentage, uint32_t nodeId, std::vector<TreeEntry>& result) const
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

template<uint32_t Dimensions, uint32_t Depth, bool StaticAllocation>
void LooseNTree<Dimensions, Depth, StaticAllocation>::getFromNode(const Vector& startPercentage, const Vector& endPercentage, uint32_t nodeId, std::vector<TreeEntry>& result) const
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

template<uint32_t Dimensions, uint32_t Depth, bool StaticAllocation>
void LooseNTree<Dimensions, Depth, StaticAllocation>::setSize(const Vector& size)
{
    mSize = size;
}

template<uint32_t Dimensions, uint32_t Depth, bool StaticAllocation>
void LooseNTree<Dimensions, Depth, StaticAllocation>::increaseSize()
{
    uint32_t newSize = mAllocatedNodesCount * 2;
    Node* newNodes = new Node[newSize];

    std::copy(mNodes, mNodes + mAllocatedNodesCount, newNodes);
    delete [] mNodes;
    mNodes = newNodes;

    mAllocatedNodesCount = newSize;
}

template<uint32_t Dimensions, uint32_t Depth, bool StaticAllocation>
void LooseNTree<Dimensions, Depth, StaticAllocation>::decreaseSize()
{
    uint32_t newSize = mAllocatedNodesCount / 4;
    Node* newNodes = new Node[newSize];

    std::copy(mNodes, mNodes + newSize, newNodes);
    delete [] mNodes;
    mNodes = newNodes;

    mAllocatedNodesCount = newSize;
}

template<uint32_t Dimensions, uint32_t Depth, bool StaticAllocation>
void LooseNTree<Dimensions, Depth, StaticAllocation>::checkForRemoval(uint32_t nodeIndex, std::vector<uint32_t>& toCheck)
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

template<uint32_t Dimensions, uint32_t Depth, bool StaticAllocation>
void LooseNTree<Dimensions, Depth, StaticAllocation>::removeNode(uint32_t nodeIndex, std::vector<uint32_t>& toCheck)
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
