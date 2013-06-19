#include <framework/glm/glm.hpp>
#include <framework/rendering/renderer2d.h>
#include <framework/rendering/drawable2d.h>

#include <framework/rendering/text.h> //TEMPHACK

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
        backend.preRender();
    }

    void Renderer2D::render(const Drawable2D& drawable)
    {
        if(drawable.isText)
        {
            const Text& text = (const Text&) drawable;
            TextData temp;
            temp.text = text.getText();
            temp.position = text.getPosition();
            temp.colour = text.getColour();

            backend.renderText(temp);
            return;
        }
        RenderData temp;

        drawable.getRenderData(temp, clock);

        backend.render(temp);
    }

    void Renderer2D::postRender()
    {
        backend.postRender();
        clock++;
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
