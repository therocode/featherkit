#include <featherkit/window/videomode.hpp>

namespace fea
{
    VideoMode::VideoMode()
    {
    }

    VideoMode::VideoMode(uint32_t width, uint32_t height, uint32_t bitDepth) : mWidth(width), mHeight(height), mBitDepth(bitDepth)
    {
    }
}
