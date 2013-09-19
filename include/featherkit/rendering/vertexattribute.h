#pragma once
#include <cstdint>
#include <cstddef>

namespace fea
{
    struct VertexAttribute
    {
        VertexAttribute(size_t i, uint32_t s, const float* d);
        size_t index;
        uint32_t size;
        const float* data;
    };
}
