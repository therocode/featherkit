#include <featherkit/rendering/texture.h>
#include <featherkit/rendering/renderer2dbackend.h>

namespace fea
{

    Texture::Texture(Renderer2DBackend& backend, int32_t i) : creator(backend), id(i)
    {
    }
    
    Texture::Texture(Texture&& other) : creator(other.creator), id(other.id)
    {
        other.id = -1;
    }

    int32_t Texture::getId() const
    {
        return id;
    }
    
    Texture::~Texture()
    {
        creator.destroyTexture(id);
    }
}
