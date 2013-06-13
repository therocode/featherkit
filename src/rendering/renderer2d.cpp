#include <framework/glm/glm.hpp>
#include <framework/rendering/renderer2d.h>
#include <framework/rendering/drawable2d.h>

namespace windbreeze
{
    Renderer2D::Renderer2D(Renderer2DBackend& b, glm::vec2 s, Camera c) : backend(b), renderSize(s), currentCamera(c)
    {
        backend.setViewSize(s);
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
        backend.setCameraPosition(currentCamera.getPosition());
        backend.setCameraTransform(currentCamera.getTransformation());
    }

    void Renderer2D::render(const Drawable2D& drawable)
    {
        RenderData temp;
        temp.vertices = drawable.getVerticesTransformed();

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
