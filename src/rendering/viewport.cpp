#include <featherkit/rendering/viewport.h>

namespace fea
{
    Viewport::Viewport()
    {
    }

    Viewport::Viewport(uint32_t w, uint32_t h) : size(glm::uvec2(w, h))
    {
    }

    Viewport::Viewport(uint32_t w, uint32_t h, const Camera& cam) : size(glm::uvec2(w, h)), camera(cam)
    {
    }

    void Viewport::setSize(const glm::uvec2& s)
    {
        size = s;
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
    
    glm::vec2 Viewport::transformPoint(const glm::vec2 point) const
    {
        glm::vec2 halfViewSize = ((glm::vec2) size) * 0.5f;
        return glm::inverse(camera.getRotationMatrix()) * (camera.getZoom() * (point - camera.getPosition())) + halfViewSize;
    }
    
    glm::vec2 Viewport::untransformPoint(const glm::vec2 point) const
    {
        glm::vec2 halfViewSize = ((glm::vec2) size) * 0.5f;
        return (1.0f/camera.getZoom()) * (camera.getRotationMatrix() * (point - halfViewSize)) + camera.getPosition();
    }
}
