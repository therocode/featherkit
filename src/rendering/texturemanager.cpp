#include <framework/rendering/texturemanager.h>

namespace windbreeze
{
    InvalidTextureException::InvalidTextureException(const std::string& message) : std::runtime_error(message)
    {
    };
}
