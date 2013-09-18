#pragma once
#include <cstdint>

namespace fea
{
    struct VertexAttribute
    {
        VertexAttribute(size_t i, uint32_t s, float* d);
        size_t index;
        uint32_t size;
        float* data;
    };
}
