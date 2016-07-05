#include <fea/ui/contextsettings.hpp>

namespace fea
{
        ContextSettings::ContextSettings(uint32_t depthBits, uint32_t stencilBits, uint32_t antialiasingLevel, uint32_t majorVersion, uint32_t minorVersion, Type type) : mDepthBits(depthBits), mStencilBits(stencilBits), mAntialiasingLevel(antialiasingLevel), mMajorVersion(majorVersion), mMinorVersion(minorVersion), mType(type)
        {
        }
}
