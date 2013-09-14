#include <featherkit/util/rendering/opengl/opengl2dbackend.h>
#include <glm/gtc/type_ptr.hpp>
#include <featherkit/util/rendering/opengl/glslloader.h>

namespace fea
{
    namespace util
    {
        OpenGL2DBackend::OpenGL2DBackend() : nextTextureId(0), nextRenderTargetId(0)
        {
        }

        void OpenGL2DBackend::setup()
        {
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            //glEnable(GL_TEXTURE_2D);
            glDisable(GL_DEPTH_TEST);
            glEnable(GL_BLEND);
            glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glewInit();

            for(auto& mode : renderModes)
            {
                mode.second->setup();
            }

            stash = sth_create(512, 512);

            uint8_t white[4*4*4];

            for(uint32_t i = 0; i < 4*4*4; i++)
            {
                white[i] = 255;
            }

            defaultTexture = createTexture(4, 4, &white[0]);
        }

        void OpenGL2DBackend::destroy()
        {
        }

        void OpenGL2DBackend::clear()
        {
            glClear(GL_COLOR_BUFFER_BIT);
        }
        
        void OpenGL2DBackend::clear(const RenderTarget& target)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, renderTargets.at(target.getId()));

            glClear(GL_COLOR_BUFFER_BIT);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void OpenGL2DBackend::preRender()
        {
            const glm::uvec2& viewSize = viewport->getSize();

            //glEnableClientState(GL_VERTEX_ARRAY);
            //glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            auto mode = currentMode.lock();
            glEnableVertexAttribArray(mode->vertexLocation);
            glEnableVertexAttribArray(mode->texCoordsLocation);

            mode->preRender();
            GLuint shaderProgram = mode->shaderProgram;

            glm::mat2x2 rotation = glm::inverse(viewport->getCamera().getRotationMatrix());

            glUniform2fv(mode->positionUniform, 1, glm::value_ptr(viewport->getCamera().getPosition()));

            glUniform2fv(mode->zoomUniform, 1, glm::value_ptr(viewport->getCamera().getZoom()));

            glUniformMatrix2fv(mode->rotationUniform, 1, false, glm::value_ptr(rotation));

            glUniform2fv(mode->halfSizeUniform, 1, glm::value_ptr((glm::vec2)viewSize * 0.5f));
        }

        void OpenGL2DBackend::render(const RenderData& renderData)
        {
            auto mode = currentMode.lock();
            GLuint shaderProgram = mode->shaderProgram;
            std::vector<float> vertices = renderData.vertices;
            std::vector<float> texCoords = renderData.texCoords;
            glm::vec2 vertex;
            GLsizei quadAmount = (GLsizei) vertices.size() / 2;

            if(renderData.texture == -1)
            {
                glBindTexture(GL_TEXTURE_2D, textures.at(defaultTexture.getId()));
            }
            else
            {
                GLuint texture = textures.at(renderData.texture);
                glBindTexture(GL_TEXTURE_2D, texture);
            }
            //glm::ivec2 size;
            //glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &size[0]);
            //glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &size[1]);

            glUniform2fv(mode->constrainXUniform, 1, glm::value_ptr(renderData.constrainX));

            glUniform2fv(mode->constrainYUniform, 1, glm::value_ptr(renderData.constrainY));

            glUniform2fv(mode->textureScroll, 1, glm::value_ptr(renderData.textureScroll));

            glUniform1fv(mode->parallax, 1, &renderData.parallax);

            glUniform3fv(mode->colour, 1, glm::value_ptr(renderData.colour));

            glUniform1fv(mode->opacity, 1, &renderData.opacity);

            //glVertexPointer(2, GL_FLOAT, 0, &vertices[0]);
            //glTexCoordPointer(2, GL_FLOAT, 0, &texCoords[0]);
            glVertexAttribPointer(mode->vertexLocation, 2, GL_FLOAT, false, 0, &vertices[0]);
            glVertexAttribPointer(mode->texCoordsLocation, 2, GL_FLOAT, false, 0, &texCoords[0]);
            glDrawArrays(GL_TRIANGLES, 0, quadAmount);
        }
        
        void OpenGL2DBackend::render(const RenderData& renderData, const RenderTarget& target)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, renderTargets.at(target.getId()));

            render(renderData);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void OpenGL2DBackend::postRender()
        {
            currentMode.lock()->postRender();

            glBindTexture(GL_TEXTURE_2D, 0);
            //glDisableClientState(GL_VERTEX_ARRAY);
            //glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            glDisableVertexAttribArray(currentMode.lock()->vertexLocation);
            glDisableVertexAttribArray(currentMode.lock()->texCoordsLocation);
        }

        void OpenGL2DBackend::renderText(const TextData& textData)
        {
            glUseProgram(0);

            glBindTexture(GL_TEXTURE_2D, 0);
            //glDisableClientState(GL_VERTEX_ARRAY);
            //glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            glDisableVertexAttribArray(currentMode.lock()->vertexLocation);
            glDisableVertexAttribArray(currentMode.lock()->texCoordsLocation);

            //glDisable(GL_TEXTURE_2D);

            //glColor4f(textData.colour.r, textData.colour.g, textData.colour.b, textData.opacity);
            sth_font_colour(stash, textData.colour.r, textData.colour.g, textData.colour.b, textData.opacity);

            glm::vec2 point = glm::vec2(textData.position.x, textData.position.y);

            const Camera& camera = viewport->getCamera();
            point = glm::inverse(camera.getRotationMatrix()) * (camera.getZoom() * (point - camera.getPosition() * textData.parallax)) + (glm::vec2)viewport->getSize() * 0.5f;
            //point = viewport.getCamera().getTransformation() * (point - viewport.getCamera().getPosition());

            float x = point.x;
            float y = point.y;

            sth_begin_draw(stash);
            sth_draw_text(stash, textData.font, textData.size, x, y, textData.text.c_str(), &x);
            sth_end_draw(stash);

            //glEnableClientState(GL_VERTEX_ARRAY);
            //glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glEnableVertexAttribArray(currentMode.lock()->vertexLocation);
            glEnableVertexAttribArray(currentMode.lock()->texCoordsLocation);

            //glEnable(GL_TEXTURE_2D);

            //glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            
            glUseProgram(currentMode.lock()->shaderProgram);
        }
        
        void OpenGL2DBackend::renderText(const TextData& textData, const RenderTarget& target)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, renderTargets.at(target.getId()));

            renderText(textData);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        int32_t OpenGL2DBackend::addFont(uint8_t* fontData)
        {
            int font = sth_add_font_from_memory(stash, fontData);
            if(font == 0)
            {
                //throw font error
            }
            return font;
        }
        
        void OpenGL2DBackend::addRenderMode(const std::string& name, RenderMode* newMode)
        {
            renderModes.emplace(name, std::shared_ptr<OpenGLRenderMode>((OpenGLRenderMode*) newMode));
        }

        void OpenGL2DBackend::setRenderMode(const std::string& mode)
        {
            currentMode = renderModes.at(mode);
        }
        
        void OpenGL2DBackend::setClearColour(const glm::vec3& colour)
        {
            glClearColor(colour.r, colour.g, colour.b, 0.0f);
        }
        
        void OpenGL2DBackend::setBlendMode(BlendMode mode)
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

        void OpenGL2DBackend::setViewport(Viewport& view)
        {
            const glm::uvec2& viewSize = view.getSize();
            const glm::ivec2& viewPos = view.getPosition();
            glViewport(viewPos.x, viewPos.y, (GLsizei)viewSize.x, (GLsizei)viewSize.y);
            //glMatrixMode(GL_PROJECTION);
            //glLoadIdentity();
            //gluOrtho2D(0.0f, viewSize.x, viewSize.y, 0.0f);
            //glMatrixMode(GL_MODELVIEW);
            float projection[16];

            createOrthoProjection(0.0f, viewSize.x, 0.0f, viewSize.y, 0.000000001f, 100.0f, &projection[0]);

            for(auto& renderMode : renderModes)
            {
                renderMode.second->updateProjection(&projection[0]);
            }
            
            sth_set_projection(stash, projection);

            viewport = &view;
        }
        
        Texture OpenGL2DBackend::createTexture(uint32_t w, uint32_t h, const uint8_t* imageData, bool smooth)
        {
            GLuint id;

            glGenTextures(1, &id);
            glBindTexture(GL_TEXTURE_2D, id);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)w, (GLsizei)h, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, smooth ? GL_LINEAR : GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, smooth ? GL_LINEAR : GL_NEAREST);

            glBindTexture(GL_TEXTURE_2D, 0);

            Texture newTexture(*this, nextTextureId);
            textures.emplace(nextTextureId, id);
            nextTextureId++;
            
            return newTexture;
        }
        
        void OpenGL2DBackend::destroyTexture(int32_t id)
        {
            glDeleteTextures(1, &textures.at(id));
            textures.erase(id);
        }
        
        RenderTarget OpenGL2DBackend::createRenderTarget(uint32_t w, uint32_t h, bool smooth)
        {
            GLuint targetId;
            GLuint textureId;

            glGenFramebuffers(1, &targetId);
            glBindFramebuffer(GL_FRAMEBUFFER, targetId);

            glGenTextures(1, &textureId);
            glBindTexture(GL_TEXTURE_2D, textureId);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)w, (GLsizei)h, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, smooth ? GL_LINEAR : GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, smooth ? GL_LINEAR : GL_NEAREST);
            //glGenerateMipmap(GL_TEXTURE_2D);

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId, 0);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glBindTexture(GL_TEXTURE_2D, 0);
            
            RenderTarget newTarget(*this, nextRenderTargetId, w, h, Texture(*this, nextTextureId));
            renderTargets.emplace(nextRenderTargetId, targetId);
            textures.emplace(nextTextureId, textureId);
            nextTextureId++;
            nextRenderTargetId++;

            return newTarget;
        }

        void OpenGL2DBackend::destroyRenderTarget(int32_t id)
        {
            glDeleteFramebuffers(1, &renderTargets.at(id));
            renderTargets.erase(id);
        }

        void OpenGL2DBackend::createOrthoProjection(GLfloat left, GLfloat right, GLfloat top, GLfloat bottom, GLfloat near, GLfloat far, GLfloat* matrix) const
        {
            GLfloat r_l = right - left;
            GLfloat t_b = top - bottom;
            GLfloat f_n = far - near;
            GLfloat tx = -(right + left) / (right - left);
            GLfloat ty = -(top + bottom) / (top - bottom);
            GLfloat tz = -(far + near) / (far - near);

            matrix[0] = 2.0f / r_l;
            matrix[4] = 0.0f;
            matrix[8] = 0.0f;
            matrix[12] = tx;

            matrix[1] = 0.0f;
            matrix[5] = 2.0f / t_b;
            matrix[9] = 0.0f;
            matrix[13] = ty;

            matrix[2] = 0.0f;
            matrix[6] = 0.0f;
            matrix[10] = 2.0f / f_n;
            matrix[14] = tz;

            matrix[3] = 0.0f;
            matrix[7] = 0.0f;
            matrix[11] = 0.0f;
            matrix[15] = 1.0f;
        }
    }
}
