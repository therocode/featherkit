#include <framework/glm/glm.hpp>
#include <framework/rendering/renderer2d.h>
#include <framework/rendering/drawable2d.h>

namespace windbreeze
{
    Renderer2D::Renderer2D(Renderer2DBackend& b) : backend(b), currentCamera(1366.0f * 0.5f, 768.0f * 0.5f, 1366.0f, 768.0f)
    {
    }
            
    void Renderer2D::clear()
    {
        backend.clear();
    }
    
    void Renderer2D::setup()
    {
        backend.setup();
    }

    void Renderer2D::destroy()
    {
        backend.destroy();
    }

    void Renderer2D::preRender()
    {
        float camX = currentCamera.getPosition().x;
        float camY = currentCamera.getPosition().y;
        float camWidth = currentCamera.getSize().x;
        float camHeight = currentCamera.getSize().y;
        backend.setViewRect(camX, camY, camWidth, camHeight);
        backend.setViewTransform(currentCamera.getTransformation());
    }

    void Renderer2D::render(const Drawable2D& drawable)
    {
        const std::vector<float>& vertices = drawable.getVerticesTransformed();

        glm::vec2 vertex;
        glm::vec2 halfCameraSize = currentCamera.getSize() * 0.5f;

        RenderData temp;
        backend.render(temp);
        

    }

    void Renderer2D::postRender()
    {
    }

    void Renderer2D::setCamera(const Camera& camera)
    {
        currentCamera = camera;
    }
    
    Camera& Renderer2D::getCamera()
    {
        return currentCamera;
    }
}
