#pragma once
#include <cstdint>

namespace windbreeze
{
    class VideoMode
    {
        public:
            VideoMode() {}
            VideoMode(uint32_t w, uint32_t h, uint32_t bitDepth=32) : width(w), height(h), bitsPerPixel(bitDepth) {}

            uint32_t width;
            uint32_t height;
            uint32_t bitsPerPixel;
    };

}
