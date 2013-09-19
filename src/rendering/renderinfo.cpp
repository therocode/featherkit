#include <featherkit/rendering/renderinfo.h>

namespace fea
{
    uint32_t RenderInfo::getDrawAmount() const
    {
        return vertexAttributes[0].size / 2 / 3;
    }
}
