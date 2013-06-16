#include <framework/util/rendering/sfml2dbackend.h>
#include <framework/glm/gtc/type_ptr.hpp>
#include <framework/rendering/shaderloader.h>
#include <iostream>

namespace windbreeze
{
    void Sfml2DBackend::setup()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0.0f, 1366.0f, 768.0f, 0.0f);
        glMatrixMode(GL_MODELVIEW);
        glEnable(GL_TEXTURE_2D);

        glewInit();

        //vertex = rotation * (viewport.getCamera().getZoom() * (vertex - viewport.getCamera().getPosition())) + halfViewSize

        std::string vertexShaderSource = "#version 120\n"
                                         "uniform vec2 position;"
                                         "uniform vec2 zoom;"
                                         "uniform mat2 rotation;"
                                         "uniform vec2 halfViewSize;"
                                         ""
                                         "varying vec2 texCoords;"
                                         ""
                                         "void main()"
                                         "{"
                                         "    vec2 transformedPoint = rotation * (zoom * (gl_Vertex.xy - position)) + halfViewSize;"
                                         "    gl_Position = vec4(transformedPoint.xy, gl_Vertex.zw);"
                                         "    gl_Position = gl_ProjectionMatrix * (gl_Position);"
                                         "    gl_TexCoord[0]  = gl_MultiTexCoord0;"
                                         "}"
                                         "";

        std::string fragmentShaderSource = "#version 120\n"
                                           "uniform sampler2D texture;"
                                           ""
                                           "varying vec2 texCoords;"
                                           ""
                                           "void main()"
                                           "{"
                                           "    gl_FragColor = texture2D(texture, gl_TexCoord[0].st);"
                                           "}"
                                           "";
        
        ShaderLoader loader;
        shaderProgram = loader.createShader(vertexShaderSource, fragmentShaderSource);
        glUseProgram(shaderProgram);
    }

    void Sfml2DBackend::destroy()
    {
    }

    void Sfml2DBackend::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Sfml2DBackend::preRender()
    {
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glm::vec2 halfViewSize = (glm::vec2)(viewport.getSize()) * 0.5f;
        glm::mat2x2 rotation = glm::inverse(viewport.getCamera().getTransformation());

        GLint positionUniform = glGetUniformLocation(shaderProgram, "position");
        glUniform2fv(positionUniform, 1, glm::value_ptr(viewport.getCamera().getPosition()));

        GLint zoomUniform = glGetUniformLocation(shaderProgram, "zoom");
        glUniform2fv(zoomUniform, 1, glm::value_ptr(viewport.getCamera().getZoom()));
        
        GLint rotationUniform = glGetUniformLocation(shaderProgram, "rotation");
        glUniformMatrix2fv(rotationUniform, 1, false, glm::value_ptr(rotation));

        GLint halfSizeUniform = glGetUniformLocation(shaderProgram, "halfViewSize");
        glUniform2fv(halfSizeUniform, 1, glm::value_ptr(halfViewSize));

        GLint textureUniform = glGetUniformLocation(shaderProgram, "texture");
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(textureUniform, 0);
    }

    void Sfml2DBackend::render(RenderData renderData)
    {
        std::vector<float> vertices = renderData.vertices;
        std::vector<float> texCoords = renderData.texCoords;
        glm::vec2 vertex;

        if(renderData.textureId != "")
        {
            OpenGLTexture texture = textureManager.getTexture(renderData.textureId);
            glBindTexture(GL_TEXTURE_2D, texture.glId);
        }
        else
        {
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        glVertexPointer(2, GL_FLOAT, 0, &vertices[0]);
        glTexCoordPointer(2, GL_FLOAT, 0, &texCoords[0]);
        glDrawArrays(GL_QUADS, 0, 4);
    }

    void Sfml2DBackend::postRender()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }
}
