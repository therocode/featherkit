#pragma once
#include <fea/config.hpp>
#include <stdint.h>

namespace fea
{
    struct FEA_API ContextSettings
    {
        explicit ContextSettings(uint32_t depthBits = 0, uint32_t stencilBits = 0, uint32_t antialiasingLevel = 0, uint32_t majorVersion = 2, uint32_t minorVersion = 0);

        uint32_t mDepthBits;         
        uint32_t mStencilBits;       
        uint32_t mAntialiasingLevel; 
        uint32_t mMajorVersion;      
        uint32_t mMinorVersion;   
    };

    /** @addtogroup UserInterface
     *@{
     *  @struct ContextSettings
     *@}
     ***
     *  @struct ContextSettings
     *  @brief Defines the settings of the OpenGL context attached to a window if OpenGL is used.
     *
     ***
     *  @fn explicit ContextSettings::ContextSettings(uint32_t depthBits = 0, uint32_t stencilBits = 0, uint32_t antialiasingLevel = 0, uint32_t majorVersion = 2, uint32_t minorVersion = 0)
     *  @brief Default constructor.
     *
     *  @param depthBits Number of bits per pixel of the depth buffer.
     *  @param stencilBits Number of bits per pixel of the stencil buffer.
     *  @param antialiasingLevel Antialiasing level.
     *  @param majorVersion Major version number of the OpenGL context.
     *  @param minorVersion Minor version number of the OpenGL context.
     ***
     *  @var ContextSettings::mDepthBits
     *  @brief The number of bits per pixel requested for the depth buffer.
     ***
     *  @var ContextSettings::mStencilBits
     *  @brief The number of bits per pixel requested for the stencil buffer.
     ***
     *  @var ContextSettings::mAntialiasingLevel
     *  @brief The number of multisampling levels requested for anti-aliasing.
     ***
     *  @var ContextSettings::mMajorVersion
     *  @brief The major version number of the OpenGL context to be created.
     ***
     *  @var ContextSettings::mMinorVersion
     *  @brief The minor version number of the OpenGL context to be created.
     ***/

}
