#include <featherkit/rendering/texturemanager.h>

namespace fea
{
    InvalidTextureException::InvalidTextureException(const std::string& message) : std::runtime_error(message)
    {
    };
}
