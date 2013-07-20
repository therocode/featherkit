#include <featherkit/rendering/texturemanager.h>

namespace fk
{
    InvalidTextureException::InvalidTextureException(const std::string& message) : std::runtime_error(message)
    {
    };
}
