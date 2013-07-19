#include <framework/window/videomode.h>

namespace windbreeze
{
    VideoMode::VideoMode()
    {
    }

    VideoMode::VideoMode(uint32_t w, uint32_t h, uint32_t bitDepth) : width(w), height(h), bitsPerPixel(bitDepth)
    {
    }
}
