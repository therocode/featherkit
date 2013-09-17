#pragma once
#include <cstdint>

namespace fea
{
    class VertexAttribute
    {
        private:
            uint8_t index;
            float* data;
    };
}
