#include <featherkit/rendering/rendertarget.h>
#include <featherkit/rendering/renderer2dbackend.h>

namespace fea
{
    RenderTarget::RenderTarget() : creator(nullptr), id(-1), width(0), height(0)
    {
    }

    RenderTarget::RenderTarget(Renderer2DBackend& backend, int32_t i, uint32_t w, uint32_t h) : creator(&backend), id(i), width(w), height(h)
    {
    }

    RenderTarget::RenderTarget(RenderTarget&& other) : creator(other.creator), id(other.id), width(other.width), height(other.height), texture(std::move(other.texture))
    {
        other.creator = nullptr;
        other.id = -1;
    }

    RenderTarget& RenderTarget::operator=(RenderTarget&& other)
    {
        std::swap(creator, other.creator);
        std::swap(id, other.id);
        std::swap(width, other.width);
        std::swap(height, other.height);
        std::swap(texture, other.texture);

        return *this;
    }

    GLuint RenderTarget::getId() const
    {
        return id;
    }

    glm::uvec2 RenderTarget::getSize() const
    {
        return glm::uvec2(width, height);
    }
    
    const Texture& RenderTarget::getTexture() const
    {
        return texture;
    }

    void RenderTarget::create(uint32_t w, uint32_t h, bool smooth)
    {
        GLuint textureId;

        glGenFramebuffers(1, &id);
        glBindFramebuffer(GL_FRAMEBUFFER, id);

        texture.create(w, h, nullptr);
    
        glBindTexture(GL_TEXTURE_2D, texture.getId());
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.getId(), 0);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    RenderTarget::~RenderTarget()
    {
        glDeleteFramebuffers(1, &id);
    }
}
