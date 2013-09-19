#include <featherkit/rendering/vertexattribute.h>

namespace fea
{
    VertexAttribute::VertexAttribute(size_t i, uint32_t s, const float* d) : index(i), size(i), data(d)
    {
    }
}
