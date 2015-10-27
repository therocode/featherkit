#include <fea/rendering/rendertarget.hpp>
#include <fea/assert.hpp>
#include <string>

namespace fea
{
    RenderTarget::RenderTarget() : mId(0)
    {
    }

    RenderTarget::RenderTarget(RenderTarget&& other) : mId(0)
    {
        std::swap(mId, other.mId);
        std::swap(mSize, other.mSize);
        std::swap(mTexture, other.mTexture);
    }

    RenderTarget& RenderTarget::operator=(RenderTarget&& other)
    {
        std::swap(mId, other.mId);
        std::swap(mSize, other.mSize);
        std::swap(mTexture, other.mTexture);

        return *this;
    }

    GLuint RenderTarget::getId() const
    {
        return mId;
    }

    const glm::ivec2& RenderTarget::getSize() const
    {
        return mSize;
    }
    
    const Texture& RenderTarget::getTexture() const
    {
        return mTexture;
    }

    void RenderTarget::create(const glm::ivec2& size, bool smooth)
    {
        FEA_ASSERT(size.x > 0 && size.y > 0, "Size must be greater than zero in both dimensions. " + std::to_string(size.x) + " " + std::to_string(size.y) + " provided.");
        if(mId)
        {
            destroy();
        }

        mSize = size;

        glGenFramebuffers(1, &mId);
        glBindFramebuffer(GL_FRAMEBUFFER, mId);

        mTexture.create(size, nullptr);
    
        glBindTexture(GL_TEXTURE_2D, mTexture.getId());
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexture.getId(), 0);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void RenderTarget::destroy()
    {
        if(mId)
        {
            mTexture.destroy();
            glDeleteFramebuffers(1, &mId);
            mId = 0;
        }
    }

    RenderTarget::~RenderTarget()
    {
        if(mId)
        {
            destroy();
        }
    }
}
