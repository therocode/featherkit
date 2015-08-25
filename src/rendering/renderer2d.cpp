#include <glm/glm.hpp>
#include <fea/rendering/renderer2d.hpp>
#include <fea/rendering/drawable2d.hpp>
#include <fea/rendering/projection.hpp>
#include <fea/rendering/defaultshader.hpp>
#include <fea/assert.hpp>
#include <sstream>

namespace fea
{
    Renderer2D::Renderer2D(const Viewport& v) : mCurrentViewport(v), mCurrentBlendMode(ALPHA)
    {
#ifdef EMSCRIPTEN
#else
        auto glStatus = feaogl_LoadFunctions();
        FEA_ASSERT(glStatus != feaogl_LOAD_FAILED, "Could not initialize the renderer! Make sure there is a valid OpenGL context!");
#endif
        //glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        mDefaultTexture.create(16, 16, fea::Color(1.0f, 1.0f, 1.0f));

        mDefaultShader.setSource(DefaultShader::vertexSource, DefaultShader::fragmentSource);
        mDefaultShader.compile();

        setViewport(mCurrentViewport);
    }
    
    void Renderer2D::clear(const Color& color)
    {
        if(mClearColor != color)
        {
            glClearColor(color.rAsFloat(), color.gAsFloat(), color.bAsFloat(), 0.0f);
            mClearColor = color;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer2D::clear(const RenderTarget& target, const Color& color)
    {
        if(mClearColor != color)
        {
            glClearColor(color.rAsFloat(), color.gAsFloat(), color.bAsFloat(), 0.0f);
            mClearColor = color;
        }

        glBindFramebuffer(GL_FRAMEBUFFER, target.getId());
        glClear(GL_COLOR_BUFFER_BIT);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    
    void Renderer2D::queue(const Drawable2D& drawable)
    {
        for(const auto& renderEntity : drawable.getRenderInfo())
        {
            mRenderQueue.push_back(renderEntity);
            mRenderQueue.back().mBlendMode = mCurrentBlendMode;
        }

    }

    void Renderer2D::render()
    {
        render(mDefaultShader);
    }

    void Renderer2D::render(const RenderTarget& target)
    {
        render(target, mDefaultShader);
    }

    void Renderer2D::render(const Shader& shader)
    {
        shader.activate();

        shader.setUniform("camPosition", VEC2, &mCurrentViewport.getCamera().getPosition());
        shader.setUniform("camZoom", VEC2, &mCurrentViewport.getCamera().getZoom());
        glm::mat2x2 camRot = mCurrentViewport.getCamera().getRotationMatrix();
        shader.setUniform("camRotation", MAT2X2, &camRot);
        glm::vec2 halfViewSize = glm::vec2((float)mCurrentViewport.getSize().x / 2.0f, (float)mCurrentViewport.getSize().y / 2.0f);
        shader.setUniform("halfViewSize", VEC2, &halfViewSize);
        shader.setUniform("projection", MAT4X4, &mProjection);

        GLuint defaultTextureId = mDefaultTexture.getId();

        for(auto& renderOperation : mRenderQueue)
        {
            shader.setUniform("texture", TEXTURE, &defaultTextureId); //may be overriden
            setBlendModeGl(renderOperation.mBlendMode);

            for(auto& uniform : renderOperation.mUniforms)
            {
                shader.setUniform(uniform.mName, uniform.mType, &uniform.mFloatVal);
            }
            
            for(auto& vertexAttribute : renderOperation.mVertexAttributes)
            {
                shader.setVertexAttribute(vertexAttribute.mName, vertexAttribute.mFloatAmount, vertexAttribute.mData.data());
            }

            glDrawArrays(renderOperation.mDrawMode, 0, renderOperation.mElementAmount);
        }

        setBlendMode(ALPHA);
        shader.deactivate();
        mRenderQueue.clear();
    }

    void Renderer2D::render(const RenderTarget& target, const Shader& shader)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, target.getId());
        render(shader);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Renderer2D::setViewport(const Viewport& viewport)
    {
        mCurrentViewport = viewport;
        const glm::uvec2& viewSize = viewport.getSize();
        const glm::ivec2& viewPos = viewport.getPosition();
        glViewport(viewPos.x, viewPos.y, (GLsizei)viewSize.x, (GLsizei)viewSize.y);

        Projection proj;
        mProjection = proj.createOrthoProjection(0.0f, (GLfloat)viewSize.x, 0.0f, (GLfloat)viewSize.y, 0.000000001f, 100.0f);
    }
    
    Viewport& Renderer2D::getViewport()
    {
        return mCurrentViewport;
    }
    
    void Renderer2D::setBlendMode(BlendMode mode)
    {
        mCurrentBlendMode = mode;
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
