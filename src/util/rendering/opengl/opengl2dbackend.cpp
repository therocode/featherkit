#include <featherkit/util/rendering/opengl/opengl2dbackend.h>
#include <featherkit/glm/gtc/type_ptr.hpp>
#include <featherkit/rendering/shaderloader.h>

namespace fea
{
    namespace util
    {
        OpenGL2DBackend::OpenGL2DBackend(TextureManager<OpenGLTexture>& tm) : textureManager(tm), shaderProgram(0)
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

            std::string vertexShaderSource = "#version 120\n"
                "\n"
                "uniform vec2 position;\n"
                "uniform vec2 zoom;\n"
                "uniform mat2 rotation;\n"
                "uniform vec2 halfViewSize;\n"
                "uniform float parallax;"
                "\n"
                "void main()\n"
                "{\n"
                "    vec2 transformedPoint = rotation * (zoom * (gl_Vertex.xy - position * parallax)) + halfViewSize;\n"
                "    gl_Position = vec4(transformedPoint.xy, gl_Vertex.zw);\n"
                "    gl_Position = gl_ProjectionMatrix * (gl_Position);\n"
                "    gl_TexCoord[0]  = gl_MultiTexCoord0;\n"
                "}\n"
                "";

            std::string fragmentShaderSource = "#version 120\n"
                "uniform sampler2D texture;\n"
                "uniform vec2 constrainX;\n"
                "uniform vec2 constrainY;\n"
                "uniform vec2 textureScroll;"
                "\n"
                "float boundBetween(float val, float lowerBound, float upperBound)\n"
                "{\n"
                "    if(lowerBound > upperBound)\n"
                "    {\n"
                "        float temp = lowerBound;\n"
                "        lowerBound = upperBound;\n"
                "        upperBound = temp;\n"
                "    }\n"
                "    \n"
                "    val = val - lowerBound;\n"
                "    float rangeSize = upperBound - lowerBound;\n"
                "    if(rangeSize == 0)\n"
                "    {\n"
                "        return upperBound;\n"
                "    }\n"
                "    return val - (rangeSize * floor(val/rangeSize)) + lowerBound;\n"
                "}\n"
                "\n"
                "void main()\n"
                "{\n"
                "\n"
                "    vec2 constraintSize = abs(vec2(constrainX[1] - constrainX[0] , constrainY[1] - constrainY[0]));\n"
                "    vec2 texCoords = constraintSize * gl_TexCoord[0].st + vec2(constrainX[0], constrainY[0]) - textureScroll;\n"
                "    texCoords = vec2(boundBetween(texCoords.s, constrainX[0], constrainX[1]), boundBetween(texCoords.t, constrainY[0], constrainY[1]));\n"
                "    gl_FragColor = texture2D(texture, texCoords);\n"
                "}\n"
                "";

            ShaderLoader loader;
            shaderProgram = loader.createShader(vertexShaderSource, fragmentShaderSource);

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
            const glm::uvec2& viewSize = viewport.getSize();
            glViewport(0, 0, viewSize.x, viewSize.y);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluOrtho2D(0.0f, viewSize.x, viewSize.y, 0.0f);
            glMatrixMode(GL_MODELVIEW);
            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);

            glUseProgram(shaderProgram);

            glm::mat2x2 rotation = glm::inverse(viewport.getCamera().getRotationMatrix());

            GLint positionUniform = glGetUniformLocation(shaderProgram, "position");
            glUniform2fv(positionUniform, 1, glm::value_ptr(viewport.getCamera().getPosition()));

            GLint zoomUniform = glGetUniformLocation(shaderProgram, "zoom");
            glUniform2fv(zoomUniform, 1, glm::value_ptr(viewport.getCamera().getZoom()));

            GLint rotationUniform = glGetUniformLocation(shaderProgram, "rotation");
            glUniformMatrix2fv(rotationUniform, 1, false, glm::value_ptr(rotation));

            GLint halfSizeUniform = glGetUniformLocation(shaderProgram, "halfViewSize");
            glUniform2fv(halfSizeUniform, 1, glm::value_ptr((glm::vec2)viewSize * 0.5f));

            GLint textureUniform = glGetUniformLocation(shaderProgram, "texture");
            glActiveTexture(GL_TEXTURE0);
            glUniform1i(textureUniform, 0);
        }

        void OpenGL2DBackend::render(RenderData renderData)
        {
            std::vector<float> vertices = renderData.vertices;
            std::vector<float> texCoords = renderData.texCoords;
            glm::vec2 vertex;
            uint32_t quadAmount = vertices.size() / 2;

            if(renderData.textureId != "")
            {
                OpenGLTexture texture = textureManager.getTexture(renderData.textureId);
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
            glUseProgram(0);

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

            glColor3f(textData.colour.r, textData.colour.g, textData.colour.b);

            glm::vec2 point = glm::vec2(textData.position.x, textData.position.y);

            Camera camera = viewport.getCamera();
            point = glm::inverse(camera.getRotationMatrix()) * (camera.getZoom() * (point - camera.getPosition() * textData.parallax)) + (glm::vec2)viewport.getSize() * 0.5f;
            //point = viewport.getCamera().getTransformation() * (point - viewport.getCamera().getPosition());

            float x = point.x;
            float y = point.y;

            sth_begin_draw(stash);
            sth_draw_text(stash, textData.font, textData.size, x, y, textData.text.c_str(), &x);
            sth_end_draw(stash);

            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);

            glEnable(GL_TEXTURE_2D);
            glUseProgram(shaderProgram);
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
    }
}
