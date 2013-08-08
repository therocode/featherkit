#include <featherkit/rendering/texture.h>
#include <featherkit/rendering/renderer2dbackend.h>

namespace fea
{
    Texture::Texture() : creator(nullptr), id(-1)
    {
        
    }

    Texture::Texture(Renderer2DBackend& backend, int32_t i) : creator(&backend), id(i)
    {
    }
    
    Texture::Texture(Texture&& other) : creator(other.creator), id(other.id)
    {
        other.creator = nullptr;
        other.id = -1;
    }
    
    Texture& Texture::operator=(Texture&& other)
    {
        std::swap(creator, other.creator);
        std::swap(id, other.id);
        return *this;
    }

    int32_t Texture::getId() const
    {
        return id;
    }
    
    Texture::~Texture()
    {
        if(creator != nullptr)
        {
            creator->destroyTexture(id);
        }
    }
}
