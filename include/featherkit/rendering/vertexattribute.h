#pragma once
#include <cstdint>
#include <cstddef>

namespace fea
{
    enum VertexAttributeType{AVEC2, AVEC4};

    struct VertexAttribute
    {
        VertexAttribute(size_t i, const uint32_t frameAmount, const float* data);
        size_t mIndex;
        uint32_t mFloatAmount;
        const float* mData;
    };
}
