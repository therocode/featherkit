#include <featherkit/window/contextsettings.h>

namespace fea
{
        ContextSettings::ContextSettings(uint32_t depthBits, uint32_t stencilBits, uint32_t antialiasingLevel, uint32_t majorVersion, uint32_t minorVersion) : mDepthBits(depthBits), mStencilBits(stencilBits), mAntialiasingLevel(antialiasingLevel), mMajorVersion(majorVersion), mMinorVersion(minorVersion)
        {
        }
}
