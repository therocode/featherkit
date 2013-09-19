#pragma once
#include <cstdint>
#include <cstddef>

namespace fea
{
    struct VertexAttribute
    {
        VertexAttribute(size_t i, const float* d);
        size_t index;
        const float* data;
    };
}
