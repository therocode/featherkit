#include <glm/glm.hpp>
#include <featherkit/rendering/renderer2d.h>
#include <featherkit/rendering/drawable2d.h>
#include <sstream>

#include <featherkit/rendering/text.h> //TEMPHACK
namespace fea
{
    InvalidFontException::InvalidFontException(const std::string& message) : std::runtime_error(message)
    {
    }

    Renderer2D::Renderer2D(const Viewport& v) : currentViewport(v)
    {
    }
    
    void Renderer2D::setup()
    {
        glewInit();

        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        stash = sth_create(512, 512);

        defaultTexture.create(4, 4, 1.0f, 1.0f, 1.0f);

        setViewport(currentViewport);
    }

    void Renderer2D::destroy()
    {
        sth_delete(stash);
        defaultTexture.destroy();
    }

    void Renderer2D::clear()
    {
        backend->clear();
    }

    void clear(float r, float g, float b)
    {
        clear(glm::vec3(r, g, b);
    }

    void clear(const glm::vec3& colour = glm::vec3())
    {
        if(clearColour != colour)
        {
            glClearColor(colour.r, colour.g, colour.b, 0.0f);
            clearColour = colour;
        }

        glClear(GL_COLOR_BUFFER_BIT);
    }

    void clear(const RenderTarget& target, float r, float g, float b)
    {
        clear(target, glm::vec3(r, g, b));
    }

    void clear(const RenderTarget& target, const glm::vec3& colour = glm::vec3())
    {
        if(clearColour != colour)
        {
            glClearColor(colour.r, colour.g, colour.b, 0.0f);
            clearColour = colour;
        }

        glBindFramebuffer(GL_FRAMEBUFFER, target.getId());
        glClear(GL_COLOR_BUFFER_BIT);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    
    void queue(const Drawable2D& drawable)
    {
        RenderInfo = drawable.getRenderInfo();

        //queueing!
    }

    void Renderer2D::setViewport(const Viewport& viewport)
    {
        currentViewport = viewport;
        const glm::uvec2& viewSize = view.getSize();
        const glm::ivec2& viewPos = view.getPosition();
        glViewport(viewPos.x, viewPos.y, (GLsizei)viewSize.x, (GLsizei)viewSize.y);

        createOrthoProjection(0.0f, viewSize.x, 0.0f, viewSize.y, 0.000000001f, 100.0f, &projection[0]);
        sth_set_projection(stash, projection);
    }
    
    Viewport& Renderer2D::getViewport()
    {
        return currentViewport;
    }
    
    int32_t Renderer2D::addFont(uint8_t* fontData)
    {
        int32_t font = sth_add_font_from_memory(stash, fontData);
        
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
    
    void Renderer2D::setBlendMode(BlendMode mode)
    {
        switch(mode)
        {
            case NONE:
                glBlendFunc(GL_ONE, GL_ZERO);
                break;
            case ALPHA:
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                break;
            case ADD:
                glBlendFunc(GL_ONE, GL_ONE);
                break;
            case MULTIPLY:
                glBlendFunc(GL_DST_COLOR, GL_ZERO);
                break;
            case MULTIPLY2X:
                glBlendFunc(GL_DST_COLOR, GL_SRC_COLOR);
                break;
            default:
                glBlendFunc(GL_ONE, GL_ZERO);
                break;
        }
    }
}
