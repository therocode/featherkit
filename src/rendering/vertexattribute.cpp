#include <fea/rendering/vertexattribute.hpp>

namespace fea
{
    VertexAttribute::VertexAttribute(uint32_t fAmount, std::vector<float> d) : mAttributeFloatAmount(std::move(fAmount)), mData(std::move(d))
    {
    }
}
