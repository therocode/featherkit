#include <glm/glm.hpp>
#include <featherkit/rendering/renderer2d.h>
#include <featherkit/rendering/drawable2d.h>
#include <featherkit/rendering/projection.h>
#include <sstream>

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

    void Renderer2D::clear(float r, float g, float b)
    {
        clear(glm::vec3(r, g, b));
    }

    void Renderer2D::clear(const glm::vec3& colour)
    {
        if(clearColour != colour)
        {
            glClearColor(colour.r, colour.g, colour.b, 0.0f);
            clearColour = colour;
        }

        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer2D::clear(const RenderTarget& target, float r, float g, float b)
    {
        clear(target, glm::vec3(r, g, b));
    }

    void Renderer2D::clear(const RenderTarget& target, const glm::vec3& colour)
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
    
    void Renderer2D::queue(const Drawable2D& drawable)
    {
        renderQueue.push_back(drawable.getRenderInfo());
        renderQueue.end()->blendMode = currentBlendMode;
    }

    void Renderer2D::render()
    {
        render(defaultShader);
    }

    void Renderer2D::render(const RenderTarget& target)
    {
        render(target, defaultShader);
    }

    void Renderer2D::render(const Shader& shader)
    {
        shader.activate();
        for(auto& renderOperation : renderQueue)
        {
            //setBlendMode

            for(auto& uniform : renderOperation.uniforms)
            {
                shader.setUniform(uniform.index, uniform.type, &uniform.floatVal);
            }
            
            for(auto& vertexAttribute : renderOperation.vertexAttributes)
            {
                shader.setVertexAttribute(vertexAttribute.index, vertexAttribute.data);
            }

            glDrawArrays(renderOperation.drawMode, 0, renderOperation.getDrawAmount());
        }
        shader.deactivate();
    }

    void Renderer2D::render(const RenderTarget& target, const Shader& shader)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, target.getId());
        render(shader);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Renderer2D::setViewport(const Viewport& viewport)
    {
        currentViewport = viewport;
        const glm::uvec2& viewSize = viewport.getSize();
        const glm::ivec2& viewPos = viewport.getPosition();
        glViewport(viewPos.x, viewPos.y, (GLsizei)viewSize.x, (GLsizei)viewSize.y);

        Projection proj;
        proj.createOrthoProjection(0.0f, viewSize.x, 0.0f, viewSize.y, 0.000000001f, 100.0f, &projection[0]);
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
