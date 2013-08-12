#include <featherkit/rendering/viewport.h>

namespace fea
{
    Viewport::Viewport()
    {
    }

    Viewport::Viewport(uint32_t w, uint32_t h, int32_t x, int32_t y, const Camera& cam) : position(glm::ivec2(x, y)), size(glm::uvec2(w, h)), camera(cam)
    {
    }

    Viewport::Viewport(const glm::uvec2& s, const glm::ivec2& pos, const Camera& cam) : position(pos), size(s), camera(cam)
    {
    }
    
    const glm::ivec2& Viewport::getPosition() const
    {
        return position;
    }

    const glm::uvec2& Viewport::getSize() const
    {
        return size;
    }

    void Viewport::setCamera(const Camera& cam)
    {
        camera = cam;
    }
    
    Camera& Viewport::getCamera()
    {
        return camera;
    }
    
    glm::vec2 Viewport::transformPoint(float x, float y) const
    {
        glm::vec2 halfViewSize = ((glm::vec2) size) * 0.5f;
        return glm::inverse(camera.getRotationMatrix()) * (camera.getZoom() * (glm::vec2(x, y) - camera.getPosition())) + halfViewSize;
    }
    
    glm::vec2 Viewport::transformPoint(const glm::vec2 point) const
    {
        glm::vec2 halfViewSize = ((glm::vec2) size) * 0.5f;
        return glm::inverse(camera.getRotationMatrix()) * (camera.getZoom() * (point - camera.getPosition())) + halfViewSize;
    }
    
    glm::vec2 Viewport::untransformPoint(float x, float y) const
    {
        glm::vec2 halfViewSize = ((glm::vec2) size) * 0.5f;
        return (1.0f/camera.getZoom()) * (camera.getRotationMatrix() * (glm::vec2(x, y) - halfViewSize)) + camera.getPosition();
    }

    glm::vec2 Viewport::untransformPoint(const glm::vec2 point) const
    {
        glm::vec2 halfViewSize = ((glm::vec2) size) * 0.5f;
        return (1.0f/camera.getZoom()) * (camera.getRotationMatrix() * (point - halfViewSize)) + camera.getPosition();
    }
}
