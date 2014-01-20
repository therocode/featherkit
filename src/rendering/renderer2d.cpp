#include <glm/glm.hpp>
#include <featherkit/rendering/renderer2d.h>
#include <featherkit/rendering/drawable2d.h>
#include <featherkit/rendering/projection.h>
#include <featherkit/rendering/defaultshader.h>
#include <sstream>

namespace fea
{
    Renderer2D::Renderer2D(const Viewport& v) : currentViewport(v), currentBlendMode(ALPHA)
    {
    }
    
    void Renderer2D::setup()
    {
        glewInit();

        //glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        defaultTexture.create(16, 16, 1.0f, 1.0f, 1.0f);

        defaultShader.setSource(DefaultShader::vertexSource, DefaultShader::fragmentSource);
        defaultShader.compile();

        setViewport(currentViewport);
    }

    void Renderer2D::destroy()
    {
        defaultTexture.destroy();
    }

    void Renderer2D::clear(const Colour& colour)
    {
        if(clearColour != colour)
        {
            glClearColor(colour.r(), colour.g(), colour.b(), 0.0f);
            clearColour = colour;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer2D::clear(const RenderTarget& target, const Colour& colour)
    {
        if(clearColour != colour)
        {
            glClearColor(colour.r(), colour.g(), colour.b(), 0.0f);
            clearColour = colour;
        }

        glBindFramebuffer(GL_FRAMEBUFFER, target.getId());
        glClear(GL_COLOR_BUFFER_BIT);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    
    void Renderer2D::queue(const Drawable2D& drawable)
    {
        renderQueue.push_back(drawable.getRenderInfo());
        renderQueue[renderQueue.size() - 1].blendMode = currentBlendMode;
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
        std::hash<std::string> stringHasher;
        shader.activate();

        shader.setUniform(stringHasher("camPosition"), VEC2, &currentViewport.getCamera().getPosition());
        shader.setUniform(stringHasher("camZoom"), VEC2, &currentViewport.getCamera().getZoom());
        glm::mat2x2 camRot = currentViewport.getCamera().getRotationMatrix();
        shader.setUniform(stringHasher("camRotation"), MAT2X2, &camRot);
        glm::vec2 halfViewSize = glm::vec2((float)currentViewport.getSize().x / 2.0f, (float)currentViewport.getSize().y / 2.0f);
        shader.setUniform(stringHasher("halfViewSize"), VEC2, &halfViewSize);
        shader.setUniform(stringHasher("projection"), MAT4X4, &projection);

        GLuint defaultTextureId = defaultTexture.getId();

        for(auto& renderOperation : renderQueue)
        {
            shader.setUniform(stringHasher("texture"), TEXTURE, &defaultTextureId); //may be overriden
            setBlendModeGl(renderOperation.blendMode);

            for(auto& uniform : renderOperation.uniforms)
            {
                shader.setUniform(uniform.index, uniform.type, &uniform.floatVal);
            }
            
            for(auto& vertexAttribute : renderOperation.vertexAttributes)
            {
                shader.setVertexAttribute(vertexAttribute.index, vertexAttribute.floatAmount, vertexAttribute.data);
            }

            glDrawArrays(renderOperation.drawMode, 0, renderOperation.elementAmount);
        }

        setBlendMode(ALPHA);
        shader.deactivate();
        renderQueue.clear();
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
        projection = proj.createOrthoProjection(0.0f, viewSize.x, 0.0f, viewSize.y, 0.000000001f, 100.0f);
    }
    
    Viewport& Renderer2D::getViewport()
    {
        return currentViewport;
    }
    
    void Renderer2D::setBlendMode(BlendMode mode)
    {
        currentBlendMode = mode;
    }
    
    void Renderer2D::setBlendModeGl(BlendMode mode)
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
