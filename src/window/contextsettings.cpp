#include <featherkit/window/contextsettings.h>

namespace fk
{
        ContextSettings::ContextSettings(uint32_t depth, uint32_t stencil, uint32_t antialiasing, uint32_t major, uint32_t minor) : depthBits(depth), stencilBits(stencil), antialiasingLevel(antialiasing), majorVersion(major), minorVersion(minor)
        {
        }
}
