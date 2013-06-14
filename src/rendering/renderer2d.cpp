#include <framework/glm/glm.hpp>
#include <framework/rendering/renderer2d.h>
#include <framework/rendering/drawable2d.h>

namespace windbreeze
{
    Renderer2D::Renderer2D(Renderer2DBackend& b, Viewport v) : backend(b), currentViewport(v)
    {
        b.setViewport(v);
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
        backend.setViewport(currentViewport);
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

    void Renderer2D::setViewport(const Viewport& viewport)
    {
        currentViewport = viewport;
    }
    
    Viewport& Renderer2D::getViewport()
    {
        return currentViewport;
    }
}
