#include <featherkit/rendering/rendertarget.h>

namespace fea
{
    RenderTarget::RenderTarget() : id(0), width(0), height(0)
    {
    }

    RenderTarget::RenderTarget(RenderTarget&& other) : id(0), width(0), height(0)
    {
        std::swap(id, other.id);
        std::swap(width, other.width);
        std::swap(height, other.height);
        std::swap(texture, other.texture);
    }

    RenderTarget& RenderTarget::operator=(RenderTarget&& other)
    {
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
        if(id)
        {
            destroy();
        }

        GLuint textureId;

        glGenFramebuffers(1, &id);
        glBindFramebuffer(GL_FRAMEBUFFER, id);

        texture.create(w, h, nullptr);
    
        glBindTexture(GL_TEXTURE_2D, texture.getId());
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.getId(), 0);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void RenderTarget::destroy()
    {
        if(id)
        {
            texture.destroy();
            glDeleteFramebuffers(1, &id);
            id = 0;
        }
    }

    RenderTarget::~RenderTarget()
    {
        if(id)
        {
            destroy();
        }
    }
}
