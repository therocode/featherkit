#include <featherkit/util/rendering/opengl/opengl2dbackend.h>
#include <glm/gtc/type_ptr.hpp>
#include <featherkit/util/rendering/opengl/glslloader.h>

namespace fea
{
    namespace util
    {
        OpenGL2DBackend::OpenGL2DBackend(HashedStorage<std::string, OpenGLTexture>& t) : textures(t)
        {
        }

        void OpenGL2DBackend::setup()
        {
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glEnable(GL_TEXTURE_2D);
            glDisable(GL_DEPTH_TEST);
            glEnable(GL_BLEND);
            glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glewInit();

            for(auto& mode : renderModes)
            {
                mode.second->setup();
            }

            stash = sth_create(512, 512);
        }

        void OpenGL2DBackend::destroy()
        {
        }

        void OpenGL2DBackend::clear()
        {
            glClear(GL_COLOR_BUFFER_BIT);
        }

        void OpenGL2DBackend::preRender()
        {
            const glm::uvec2& viewSize = viewport->getSize();

            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);

            currentMode.lock()->preRender();
            GLuint shaderProgram = currentMode.lock()->getShader();

            glm::mat2x2 rotation = glm::inverse(viewport->getCamera().getRotationMatrix());

            GLint positionUniform = glGetUniformLocation(shaderProgram, "position");
            glUniform2fv(positionUniform, 1, glm::value_ptr(viewport->getCamera().getPosition()));

            GLint zoomUniform = glGetUniformLocation(shaderProgram, "zoom");
            glUniform2fv(zoomUniform, 1, glm::value_ptr(viewport->getCamera().getZoom()));

            GLint rotationUniform = glGetUniformLocation(shaderProgram, "rotation");
            glUniformMatrix2fv(rotationUniform, 1, false, glm::value_ptr(rotation));

            GLint halfSizeUniform = glGetUniformLocation(shaderProgram, "halfViewSize");
            glUniform2fv(halfSizeUniform, 1, glm::value_ptr((glm::vec2)viewSize * 0.5f));
        }

        void OpenGL2DBackend::render(const RenderData& renderData)
        {
            GLuint shaderProgram = currentMode.lock()->getShader();
            std::vector<float> vertices = renderData.vertices;
            std::vector<float> texCoords = renderData.texCoords;
            glm::vec2 vertex;
            uint32_t quadAmount = vertices.size() / 2;

            if(renderData.textureId != "")
            {
                OpenGLTexture texture = *textures.at(renderData.textureId).lock();
                glBindTexture(GL_TEXTURE_2D, texture.glId);

                glm::ivec2 size;
                glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &size[0]);
                glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &size[1]);

                GLint constrainXUniform = glGetUniformLocation(shaderProgram, "constrainX");
                glUniform2fv(constrainXUniform, 1, glm::value_ptr(renderData.constrainX));

                GLint constrainYUniform = glGetUniformLocation(shaderProgram, "constrainY");
                glUniform2fv(constrainYUniform, 1, glm::value_ptr(renderData.constrainY));

                GLint textureScroll = glGetUniformLocation(shaderProgram, "textureScroll");
                glUniform2fv(textureScroll, 1, glm::value_ptr(renderData.textureScroll));

                GLint parallax = glGetUniformLocation(shaderProgram, "parallax");
                glUniform1fv(parallax, 1, &renderData.parallax);
                
                GLint colour = glGetUniformLocation(shaderProgram, "colour");
                glUniform3fv(colour, 1, glm::value_ptr(renderData.colour));

                GLint opacity = glGetUniformLocation(shaderProgram, "opacity");
                glUniform1fv(opacity, 1, &renderData.opacity);
            }
            else
            {
                glBindTexture(GL_TEXTURE_2D, 0);
            }

            glVertexPointer(2, GL_FLOAT, 0, &vertices[0]);
            glTexCoordPointer(2, GL_FLOAT, 0, &texCoords[0]);
            glDrawArrays(GL_QUADS, 0, quadAmount);
        }

        void OpenGL2DBackend::postRender()
        {
            currentMode.lock()->postRender();

            glBindTexture(GL_TEXTURE_2D, 0);
            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);

        }

        void OpenGL2DBackend::renderText(const TextData& textData)
        {
            glUseProgram(0);

            glBindTexture(GL_TEXTURE_2D, 0);
            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);

            glDisable(GL_TEXTURE_2D);

            glColor4f(textData.colour.r, textData.colour.g, textData.colour.b, textData.opacity);

            glm::vec2 point = glm::vec2(textData.position.x, textData.position.y);

            Camera camera = viewport->getCamera();
            point = glm::inverse(camera.getRotationMatrix()) * (camera.getZoom() * (point - camera.getPosition() * textData.parallax)) + (glm::vec2)viewport->getSize() * 0.5f;
            //point = viewport.getCamera().getTransformation() * (point - viewport.getCamera().getPosition());

            float x = point.x;
            float y = point.y;

            sth_begin_draw(stash);
            sth_draw_text(stash, textData.font, textData.size, x, y, textData.text.c_str(), &x);
            sth_end_draw(stash);

            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);

            glEnable(GL_TEXTURE_2D);
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
            glViewport(viewPos.x, viewPos.y, viewSize.x, viewSize.y);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluOrtho2D(0.0f, viewSize.x, viewSize.y, 0.0f);
            glMatrixMode(GL_MODELVIEW);

            viewport = &view;
        }
    }
}
