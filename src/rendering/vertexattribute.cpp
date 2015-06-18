#include <fea/rendering/vertexattribute.hpp>

namespace fea
{
    VertexAttribute::VertexAttribute(std::string name, uint32_t fAmount, std::vector<float> d) : mName(std::move(name)), mFloatAmount(std::move(fAmount)), mData(std::move(d))
    {
    }
}
