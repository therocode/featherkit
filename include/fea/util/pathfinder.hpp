#pragma once
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <type_traits>

namespace fea
{
    template<typename NodeProvider>
        class Pathfinder
        {
            public:
            using Node = typename std::remove_const<typename std::remove_reference<decltype((std::declval<NodeProvider>()).getNeighbor({}, 0))>::type>::type;
            using Path = std::vector<Node>;

            private:
            enum State { OPEN, CLOSED };

            struct NodeInfo
            {   
                uint32_t id; 
                State state;
            };  

            public:
            Path findPath(NodeProvider& nodes, const Node& start, const Node& target, uint32_t costLimit = (uint32_t)-1);
            private:
            std::vector<int32_t> fCosts;
            std::vector<int32_t> gCosts;
            std::vector<uint32_t> parents;
            std::vector<uint32_t> open;
            std::vector<uint32_t> closed;
            std::vector<Node> nodeList;
            std::unordered_map<Node, NodeInfo> nodeInfo;
        };

#include <fea/util/pathfinder.inl>

    /** @addtogroup Util
     *@{
     *  @typedef Pathfinder::Node
     *  @typedef Pathfinder::Path
     *  @class Pathfinder
     *@}
     ***
     *  @typedef Pathfinder::Node
     *  @brief A pathfinding node.
     *
     *  A pathfinding node has N amount of connected neighbors and the whole data that a path is to be found in consists of connected nodes.
     ***
     *  @typedef Pathfinder::Path
     *  @brief The returned path.
     *
     *  Simply a vector with nodes that in order makes the path.
     ***
     *  @class Pathfinder
     *  @brief A* algorithm capable of finding a path through a dataset.
     *
     *  This class provides a pathfinding function which can work on any type of data using the A* pathfinding algorithm.
     *
     *  Generally speaking, pathfinding works on datasets known as graphs. A graph is a set of nodes that are connected to each other to form a structure. For example, a 2D tilemap can be seen as such a graph where every tile is a node with zero to four neighbors (zero to eight if diagonal walking is allowed) depending on how many of the neighboring tiles are blocking.
     *
     *  It is not possible to use this class directly on any data since it doesn't know exactly how the layout of the data is. For that reason, the object providing the data which is given to the pathfinder must have four functions implemented which tells the pathfinder the information it needs. The needed functions are:
     *
     *  - A function returning the amount of neighbor that a given neighbor has.
     *  - A function for accessing neighbors of a given node by index.
     *  - A function for estimating the distance between two given nodes.
     *  - A function returning the stepping cost to step between two given nodes.
     *
     *  Here is an example for how these functions could be declared for an adaptor for a tilemap:
     *  - uint32_t TilePathAdaptor::getNeighborAmount(const glm::uvec2& tile) const
     *  - const glm::uvec2 TilePathAdaptor::getNeighbor(const glm::uvec2& tile, uint32_t index) const
     *  - int32_t TilePathAdaptor::estimateDistance(const glm::uvec2& start, const glm::uvec2& target) const
     *  - int32_t TilePathAdaptor::getStepCost(const glm::uvec2& tileA, const glm::uvec2& tileB) const
     *
     *  If these functions are implemented in an object so that they return the expected values, the pathfinding will work.
     *
     *  Note that in the example given above, the node type is glm::uvec2 since the example is about a tilemap and tilemap tiles can be represented by glm::uvec2s but any node type can be used. A less common usage example for this class is to use it to find the shortest path between two words where you are only allowed to change one letter at a time (i.e. hello -> cello -> cell -> tell) in which case the node type could be std::string.
     *
     *  The estimateDistance function lets you implement a heuristics for the A* algorithm used. For the tilemap example, Manhattan distance is good (or Euclidean distance if diagonal walking is allowed). Look up details on the A* algorithm for more details.
     *
     *  When using the pathfinder, two nodes are supplied to the Pathfinder::findPath() function. Start node and target node. The returned value is a vector with the path from the start node to the target node with each node in order, or an empty vector if no path existed.
     *
     *  @tparam NodeProvider Object providing access to the node structure to pathfind. Commonly an adaptor for an already existing object.
     ***
     *  @fn std::vector<Node> Pathfinder::findPath(NodeProvider& nodes, const Node& start, const Node& target, uint32_t costLimit = (uint32_t)-1)
     *  @brief Find a path from a starting node to a target node.
     *
     *  The details behind what nodes are, are explained in the class description.
     *
     *  @param nodes Provider of the node data to search for the path in.
     *  @param start Start node.
     *  @param target Target node.
     *  @param costLimit Maximum distance that the pathfinder considers when traversing nodes. Default is no limit.
     *  @return List with the path from start to end. Will be empty if no path existed.
     ***/
}
