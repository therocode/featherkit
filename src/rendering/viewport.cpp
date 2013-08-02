#include <featherkit/rendering/viewport.h>

namespace fea
{
    Viewport::Viewport()
    {
    }

    Viewport::Viewport(uint32_t w, uint32_t h) : size(glm::uvec2(w, h))
    {
    }

    Viewport::Viewport(const glm::vec2& s) : size(s)
    {
    }

    Viewport::Viewport(uint32_t w, uint32_t h, const Camera& cam) : size(glm::uvec2(w, h)), camera(cam)
    {
    }

    Viewport::Viewport(const glm::vec2& s, const Camera& cam) : size(s), camera(cam)
    {
    }

    void Viewport::setSize(float w, float y)
    {
        size = glm::vec2(w, y);
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
