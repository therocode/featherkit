#include <glm/glm.hpp>
#include <featherkit/rendering/renderer2d.h>
#include <featherkit/rendering/drawable2d.h>
#include <sstream>

#include <featherkit/rendering/text.h> //TEMPHACK
namespace fea
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
            temp.parallax = text.getParallax();
            temp.opacity = text.getOpacity();

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
    
    void Renderer2D::addRenderMode(const std::string& name, RenderMode* newMode)
    {
        backend->addRenderMode(name, newMode);
    }
    
    void Renderer2D::setRenderMode(const std::string& mode)
    {
        backend->setRenderMode(mode);
    }
    
    void Renderer2D::setClearColour(float r, float g, float b)
    {
        backend->setClearColour(glm::vec3(r, g, b));
    }
    
    void Renderer2D::setClearColour(const glm::vec3& colour)
    {
        backend->setClearColour(colour);
    }
}
