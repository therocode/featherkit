#pragma once
#include <fea/config.hpp>
#include <cstdint>

namespace fea
{
    struct FEA_API VideoMode
    {
            VideoMode();
            VideoMode(uint32_t width, uint32_t height, uint32_t bitDepth = 32);

            uint32_t mWidth;
            uint32_t mHeight;
            uint32_t mBitDepth;
    };

    /** @addtogroup UserInterface
     *@{
     *  @struct VideoMode
     *@}
     ***
     *  @struct VideoMode
     *  @brief Defines a video mode used to set up windows at creation time.
     *
     ***
     *  @fn VideoMode::VideoMode(uint32_t width, uint32_t height, uint32_t bitDepth=32) 
     *  @brief Default constructor.
     *
     *  @param width Width in pixels.
     *  @param height Height in pixels.
     *  @param bitDepth Pixel depth in bits per pixel.
     ***
     *  @var VideoMode::mWidth
     *  @brief The width of the video mode in pixels.
     ***
     *  @var VideoMode::mHeight
     *  @brief The height of the video mode in pixels.
     ***
     *  @var VideoMode::mBitDepth
     *  @brief The depth of the video mode in bits per pixels.
     ***/

}
