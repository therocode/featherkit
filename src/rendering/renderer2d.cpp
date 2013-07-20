#include <framework/glm/glm.hpp>
#include <framework/rendering/renderer2d.h>
#include <framework/rendering/drawable2d.h>
#include <sstream>

#include <framework/rendering/text.h> //TEMPHACK
namespace windbreeze
{
    InvalidFontException::InvalidFontException(const std::string& message) : std::runtime_error(message)
    {
    };

    Renderer2D::Renderer2D(Renderer2DBackend* b, Viewport v) : backend(b), currentViewport(v), clock(0)
    {
        backend->setViewport(v);
    }

    void Renderer2D::clear()
    {
        backend->clear();
    }
    
    void Renderer2D::setup()
    {
        backend->setup();
    }

    void Renderer2D::destroy()
    {
        backend->destroy();
    }

    void Renderer2D::preRender()
    {
        backend->setViewport(currentViewport);
        backend->preRender();
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
            temp.size = text.getTextSize();
            temp.font = text.getFont();

            backend->renderText(temp);
            return;
        }
        RenderData temp;

        drawable.getRenderData(temp, clock);

        backend->render(temp);
    }

    void Renderer2D::postRender()
    {
        backend->postRender();
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
    
    void Renderer2D::resize(uint32_t w, uint32_t h)
    {
        currentViewport.setSize(glm::uvec2(w, h));
    }
    
    int32_t Renderer2D::addFont(uint8_t* fontData)
    {
        int32_t font = backend->addFont(fontData);
        if(font != 0)
        {
            return font;
        }
        else
        {
            std::stringstream ss;
            ss << "Error! While adding font to the renderer!\n";
            throw(InvalidFontException(ss.str()));
        }
    }
}
