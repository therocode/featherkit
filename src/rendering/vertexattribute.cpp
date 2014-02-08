#include <featherkit/rendering/vertexattribute.h>

namespace fea
{
    VertexAttribute::VertexAttribute(size_t i, const uint32_t fAmount, const float* d) : mIndex(i), mFloatAmount(fAmount), mData(d)
    {
    }
}
