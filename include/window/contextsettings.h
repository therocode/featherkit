#pragma once

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

}
