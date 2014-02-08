#include <featherkit/rendering/viewport.h>

namespace fea
{
    Viewport::Viewport()
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
    
    glm::vec2 Viewport::transformPoint(const glm::vec2 point) const
    {
        glm::vec2 halfViewSize = ((glm::vec2) mSize) * 0.5f;
        return glm::inverse(mCamera.getRotationMatrix()) * (mCamera.getZoom() * (point - mCamera.getPosition())) + halfViewSize;
    }
    
    glm::vec2 Viewport::untransformPoint(const glm::vec2 point) const
    {
        glm::vec2 halfViewSize = ((glm::vec2) mSize) * 0.5f;
        return (1.0f/mCamera.getZoom()) * (mCamera.getRotationMatrix() * (point - halfViewSize)) + mCamera.getPosition();
    }
}
