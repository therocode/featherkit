#include <set>
#include <sstream>
#include <unordered_map>
#include <fea/assert.hpp>

namespace fea
{
    constexpr int32_t Pow(int32_t base, int32_t exponent)
    {
        return(exponent != 0 )? base * Pow(base, exponent -1) : 1;
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
                    Vector();
                    Vector(std::initializer_list<float> args);
                    float& operator[](const int32_t i);
                    float operator[](const int32_t i) const;
                    bool operator<=(const Vector& other) const;
                    Vector operator*(const Vector& other) const;
                    Vector operator*(float multiplier) const;
                    Vector operator/(const Vector& other) const;
                    Vector operator/(float divisor) const;
                    Vector& operator=(const Vector& other);
                    bool isPositive() const;
                private:
                    float mCoords[Dimensions];
            };

            struct Node
            {
                Node();
                uint32_t mChildren[Pow(2, Dimensions)];
                uint32_t mParent;
            };

        public:
            using TreeEntry = size_t;

            LooseNTree(const Vector& size);
            void add(uint32_t id, const Vector& position, const Vector& size);
            void remove(uint32_t id);
            void move(uint32_t id, const Vector& position);
            std::vector<TreeEntry> get(const Vector& point) const;
            std::vector<TreeEntry> get(const Vector& start, const Vector& end) const;
            void clear();
            ~LooseNTree();
        private:
            void placeTreeEntryInDepth(const TreeEntry& entry, const Vector& position, uint32_t depth);
            void removeTreeEntry(uint32_t id);
            void getFromNode(const Vector& positionPercentage, uint32_t nodeId, std::vector<TreeEntry>& result) const;
            void getFromNode(const Vector& startPercentage, const Vector& endPercentage, uint32_t nodeId, std::vector<TreeEntry>& result) const;
            void setSize(const Vector& size);
            void increaseSize();
            void decreaseSize();
            void checkForRemoval(uint32_t nodeIndex, std::vector<uint32_t>& toCheck);
            void removeNode(uint32_t nodeIndex, std::vector<uint32_t>& toCheck);

            Vector mSize;
            Node* mNodes;
            uint32_t mAllocatedNodesCount;
            uint32_t mUsedNodesCount;
            std::unordered_map<TreeEntry, uint32_t> mEntryLocations;
            std::unordered_multimap<uint32_t, TreeEntry> mEntries;
            float mMoveCache[Pow(2, Dimensions)][Dimensions];
    };

#include <fea/structure/loosentree.inl>

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
     *  This class generalizes the concept of a loose quadtree/octree to make it work in any dimension. The amount of dimensions are passed as template parameters. The tree can be used to track objects with a position and size, to return possible overlaps. The node depth of the tree is also configured with a template parameter as well as if the tree should allocate all memory possibly needed at once, or if it should dynamically grow depending on need.
     *
     *  @tparam Dimensions Amount of dimensions. 2 makes a quadtree and 3 makes an octree.
     *  @tparam Depth Node depth. The deeper the tree, the bigger memory footprint, but might reduce false positives when returning possible overlaps.
     *  @tparam StaticAllocation If this is set to true, the tree allocates all nodes at once. This increases performance of the tree, but with bigger depth and dimensions, the memory usage quickly goes out of hand.
     ***
     *  @fn LooseNTree::LooseNTree(const Vector& size)
     *  @brief Construct a tree with the given size.
     *
     *  Assert/undefined behavior if the size is zero or less in any of the dimensions.
     *  @param size Size.
     ***
     *  @fn void LooseNTree::add(uint32_t id, const Vector& position, const Vector& size)
     *  @brief Add an object to track.
     *  
     *  The added object must have a unique ID. If the object moves, the position must be updated using the LooseNTree::move function.
     *  Assert/undefined behavior if the size is zero or less in any of the dimensions, if the given ID already exists in the tree, or if the position is outside of the bounds of the tree.
     *  @param id ID of the object to track.
     *  @param position Position of the object.
     *  @param size Size of the object. Given as an Axis aligned bounding box.
     ***
     *  @fn void LooseNTree::remove(uint32_t id)
     *  @brief Stop tracking an object.
     *  
     *  Assert/undefined behavior if the object does not exist.
     *  @param id ID of the object to stop tracking.
     ***
     *  @fn void LooseNTree::move(uint32_t id, const Vector& position)
     *  @brief Move a tracked object.
     *
     *  This must be called to keep tracked objects up to date.
     *  Assert/undefined behavior if the object does not exist or if target position is outside of the bounds of the tree.
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
