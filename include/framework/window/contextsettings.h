sn#pragma once

namespace windbreeze
{
    struct ContextSettings
    {
        explicit ContextSettings(uint32_t depth = 0, uint32_t stencil = 0, uint32_t antialiasing = 0, uint32_t major = 2, uint32_t minor = 0) :
        depthBits(depth), stencilBits(stencil), antialiasingLevel(antialiasing), majorVersion(major), minorVersion(minor) {}

        uint32_t depthBits;         
        uint32_t stencilBits;       
        uint32_t antialiasingLevel; 
        uint32_t majorVersion;      
        uint32_t minorVersion;   
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
     *  @fn explicit ContextSettings::ContextSettings(uint32_t depth = 0, uint32_t stencil = 0, uint32_t antialiasing = 0, uint32_t major = 2, uint32_t minor = 0)
     *  @brief Default constructor.
     *
     *  @param depth Number of bits per pixel of the depth buffer.
     *  @param stencil Number of bits per pixel of the stencil buffer.
     *  @param antialiasing Antialiasing level.
     *  @param major Major version number of the OpenGL context.
     *  @param minor Minor version number of the OpenGL context.
     ***
     *  @var ContextSettings::depthBits
     *  @brief The number of bits per pixel requested for the depth buffer.
     ***
     *  @var ContextSettings::stencilBits
     *  @brief The number of bits per pixel requested for the stencil buffer.
     ***
     *  @var ContextSettings::antialiasingLevel
     *  @brief The number of multisampling levels requested for anti-aliasing.
     ***
     *  @var ContextSettings::majorVersion
     *  @brief The major version number of the OpenGL context to be created.
     ***
     *  @var ContextSettings::minorVersion
     *  @brief The minor version number of the OpenGL context to be created.
     ***/

}
