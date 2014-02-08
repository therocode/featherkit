#include <featherkit/rendering/viewport.h>

namespace fea
{
    Viewport::Viewport()
    {
    }

    Viewport::Viewport(uint32_t w, uint32_t h, int32_t x, int32_t y, const Camera& cam) : mPosition(glm::ivec2(x, y)), mSize(glm::uvec2(w, h)), mCamera(cam)
    {
    }

    Viewport::Viewport(const glm::uvec2& s, const glm::ivec2& pos, const Camera& cam) : mPosition(pos), mSize(s), mCamera(cam)
    {
    }
    
    const glm::ivec2& Viewport::getPosition() const
    {
        return mPosition;
    }

    const glm::uvec2& Viewport::getSize() const
    {
        return mSize;
    }

    void Viewport::setCamera(const Camera& cam)
    {
        mCamera = cam;
    }
    
    Camera& Viewport::getCamera()
    {
        return mCamera;
    }
    
    glm::vec2 Viewport::transformPoint(float x, float y) const
    {
        glm::vec2 halfViewSize = ((glm::vec2) mSize) * 0.5f;
        return glm::inverse(mCamera.getRotationMatrix()) * (mCamera.getZoom() * (glm::vec2(x, y) - mCamera.getPosition())) + halfViewSize;
    }
    
    glm::vec2 Viewport::transformPoint(const glm::vec2 point) const
    {
        glm::vec2 halfViewSize = ((glm::vec2) mSize) * 0.5f;
        return glm::inverse(mCamera.getRotationMatrix()) * (mCamera.getZoom() * (point - mCamera.getPosition())) + halfViewSize;
    }
    
    glm::vec2 Viewport::untransformPoint(float x, float y) const
    {
        glm::vec2 halfViewSize = ((glm::vec2) mSize) * 0.5f;
        return (1.0f/mCamera.getZoom()) * (mCamera.getRotationMatrix() * (glm::vec2(x, y) - halfViewSize)) + mCamera.getPosition();
    }

    glm::vec2 Viewport::untransformPoint(const glm::vec2 point) const
    {
        glm::vec2 halfViewSize = ((glm::vec2) mSize) * 0.5f;
        return (1.0f/mCamera.getZoom()) * (mCamera.getRotationMatrix() * (point - halfViewSize)) + mCamera.getPosition();
    }
}
