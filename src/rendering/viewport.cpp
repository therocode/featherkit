#include <fea/rendering/viewport.hpp>
#include <fea/assert.hpp>
#include <string>

namespace fea
{
    Viewport::Viewport()
    {
    }

    Viewport::Viewport(const glm::uvec2& s, const glm::ivec2& pos, const Camera& cam) : mPosition(pos), mSize(s), mCamera(cam)
    {
        FEA_ASSERT(s.x > 0 && s.y > 0, "Viewport size cannot be zero or negative in any dimension! " + std::to_string(s.x) + " " + std::to_string(s.y) + " provided.");
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
        return mCamera.getRotationMatrix() * (mCamera.getZoom() * (point - mCamera.getPosition())) + halfViewSize;
    }

    glm::vec2 Viewport::untransformPoint(const glm::vec2 point) const
    {
        glm::vec2 halfViewSize = ((glm::vec2) mSize) * 0.5f;
        return (1.0f/mCamera.getZoom()) * (glm::inverse(mCamera.getRotationMatrix()) * (point - halfViewSize)) + mCamera.getPosition();
    }
}
