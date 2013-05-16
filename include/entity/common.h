#include <memory>
#include <map>
#include <string>

namespace windgale
{
    struct ArrayObject;
    struct DataContainer;

    class Entity;
    class EntityGroup;

    using EntityPtr = std::shared_ptr<Entity>;
    using WeakEntityPtr = std::weak_ptr<Entity>;
    using EntityType = std::string;
    using EntityId = uint32_t;
    using ArrayPosition = uint32_t;
    using ElementSize = uint32_t;
    using AttributeHash = std::size_t;
    using ArrayMap = std::map<AttributeHash, ArrayObject>;
}
