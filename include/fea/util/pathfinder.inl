template<typename NodeProvider>
typename Pathfinder<NodeProvider>::Path Pathfinder<NodeProvider>::findPath(NodeProvider& nodes, const Node& start, const Node& target, uint32_t costLimit)
{   
    auto comparator = [this] (uint32_t a, uint32_t b)
    {
        if(fCosts[a] == fCosts[b])
            return gCosts[a] < gCosts[b];

        return fCosts[a] > fCosts[b];
    };

    fCosts.clear();
    gCosts.clear();
    parents.clear();
    open.clear();
    nodeInfo.clear();
    nodeList.clear();

    uint32_t startId = fCosts.size();
    fCosts.push_back(0);
    gCosts.push_back(0);
    parents.push_back(0);
    open.push_back(startId);
    nodeInfo[start] = {startId, OPEN};
    nodeList.push_back(start);

    bool noMoreNodes = false;
    bool targetFound = false;

    while(!noMoreNodes && !targetFound)
    {
        std::pop_heap(open.begin(), open.end(), comparator);
        uint32_t currentNodeIndex = open.back();
        Node currentNode = nodeList[currentNodeIndex];

        open.pop_back();
        closed.push_back(currentNodeIndex);
        nodeInfo[start].state = CLOSED;

        if(currentNode == target)
        {
            targetFound = true;
            continue;
        }

        uint32_t neighborAmount = nodes.getNeighborAmount(currentNode);
        for(uint32_t i = 0; i < neighborAmount; i++)
        {
            Node neighbor = nodes.getNeighbor(currentNode, i);
            const auto& iter = nodeInfo.find(neighbor);

            if(iter == nodeInfo.end())
            {
                uint32_t id = fCosts.size();
                int32_t g = gCosts[currentNodeIndex] + nodes.getStepCost(currentNode, neighbor);

                if(g <= costLimit)
                {
                    parents.push_back(currentNodeIndex);
                    gCosts.push_back(g);
                    fCosts.push_back(g + nodes.estimateDistance(neighbor, target));

                    open.push_back(id);
                    std::push_heap(open.begin(), open.end(), comparator);
                    nodeInfo[neighbor] = {id, OPEN};
                    nodeList.push_back(neighbor);
                }
            }
            else if(iter->second.state == OPEN)
            {
                uint32_t neighborIndex = iter->second.id;
                int32_t newG = gCosts[currentNodeIndex] + nodes.getStepCost(currentNode, neighbor);

                if(newG < gCosts[neighborIndex])
                {
                    parents[neighborIndex] = currentNodeIndex;
                    gCosts[neighborIndex] = newG;
                    fCosts[neighborIndex] = newG + nodes.estimateDistance(neighbor, target);

                    std::make_heap(open.begin(), open.end(), comparator);
                }
            }
        }

        if(open.size() == 0)
        {
            noMoreNodes = true;
            continue;
        }
    }

    if(targetFound)
    {
        std::vector<Node> result;

        if(closed.back() == startId)
        {
            result.push_back(nodeList[startId]);
            return result;
        }

        result.push_back(nodeList[closed.back()]);
        uint32_t nextParent = parents[closed.back()];
        while(nextParent != startId)
        {
            result.push_back(nodeList[nextParent]);
            nextParent = parents[nextParent];
        }
        result.push_back(nodeList[startId]);

        std::reverse(result.begin(), result.end());

        return result;
    }
    else
    {
        return std::vector<Node>();
    }
}
