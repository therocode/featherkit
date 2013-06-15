#include <framework/util/rendering/sfml2dbackend.h>
#include <iostream>
#include <framework/glm/gtc/type_ptr.hpp>

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
                                         "void main()"
                                         "{"
                                         "    vec2 transformedPoint = rotation * (zoom * (gl_Vertex.xy - position)) + halfViewSize;"
                                         "    gl_Position = vec4(transformedPoint.xy, gl_Vertex.zw);"
                                         "    gl_Position = gl_ProjectionMatrix * (gl_Position);"
                                         "}"
                                         "";
        const char* vertexShaderSourcePointer = &vertexShaderSource[0];

        GLuint vertexShader = glCreateShaderObjectARB(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSourcePointer, NULL);
        glCompileShader(vertexShader);

        std::string fragmentShaderSource = "#version 120\n"
                                           ""
                                           "void main()"
                                           "{"
                                           "    gl_FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);"
                                           "}"
                                           "";
        const char* fragmentShaderSourcePointer = &fragmentShaderSource[0];

        GLuint fragmentShader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSourcePointer, NULL);
        glCompileShader(fragmentShader);


        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        //////getting error
        GLint blen = 0; 
        GLsizei slen = 0;

        std::cout << "the shader program is " << shaderProgram << "\n";
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH , &blen);       
        if (blen > 1)
        {
             GLchar* compiler_log = (GLchar*)malloc(blen);
             glGetInfoLogARB(vertexShader, blen, &slen, compiler_log);
             std::cout << "vertex:\n" << compiler_log << "\n";
             free (compiler_log);
             exit(3);
        }
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH , &blen);       
        if (blen > 1)
        {
             GLchar* compiler_log = (GLchar*)malloc(blen);
             glGetInfoLogARB(fragmentShader, blen, &slen, compiler_log);
             std::cout << "fragment:\n" << compiler_log << "\n";
             free (compiler_log);
             exit(3);
        }
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH , &blen);       
        if (blen > 1)
        {
             GLchar* compiler_log = (GLchar*)malloc(blen);
             glGetInfoLogARB(shaderProgram, blen, &slen, compiler_log);
             std::cout << "program:\n" << compiler_log << "\n";
             free (compiler_log);
             exit(3);
        }

        glUseProgram(shaderProgram);

        GLuint error = glGetError();
        if(error)
        {
            std::cout << "ajaj\n";
            std::string errString(reinterpret_cast<const char*>(gluErrorString(error)));
            std::cout << errString << "\n";
            exit(3);
        }
        //////

        
        //std::cout << "program: " << shaderProgram << "\n";
    }

    void Sfml2DBackend::destroy()
    {
    }

    void Sfml2DBackend::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Sfml2DBackend::render(RenderData renderData)
    {
        glEnableClientState(GL_VERTEX_ARRAY);
        std::vector<float> vertices = renderData.vertices;
        std::vector<float> texCoords = renderData.texCoords;
        glm::vec2 vertex;
        glm::vec2 halfViewSize = (glm::vec2)(viewport.getSize()) * 0.5f;
        glm::mat2x2 rotation = glm::inverse(viewport.getCamera().getTransformation());

        if(renderData.textureId != "")
        {
            OpenGLTexture texture = textureManager.getTexture(renderData.textureId);
            glBindTexture(GL_TEXTURE_2D, texture.glId);
            std::cout << "now setting texture " << texture.glId << "\n";
        }

        GLint positionUniform = glGetUniformLocation(shaderProgram, "position");
        glUniform2fv(positionUniform, 1, glm::value_ptr(viewport.getCamera().getPosition()));

        GLint zoomUniform = glGetUniformLocation(shaderProgram, "zoom");
        glUniform2fv(zoomUniform, 1, glm::value_ptr(viewport.getCamera().getZoom()));
        
        GLint rotationUniform = glGetUniformLocation(shaderProgram, "rotation");
        glUniformMatrix2fv(rotationUniform, 1, false, glm::value_ptr(rotation));

        GLint halfSizeUniform = glGetUniformLocation(shaderProgram, "halfViewSize");
        glUniform2fv(halfSizeUniform, 1, glm::value_ptr(halfViewSize));

        glBegin(GL_QUADS);
        for(uint32_t i = 0; i < vertices.size(); i += 2)
        {
            vertex = glm::vec2(vertices[i], vertices[i+1]);
            //vertex = rotation * (viewport.getCamera().getZoom() * (vertex - viewport.getCamera().getPosition())) + halfViewSize;
            glVertex2f(vertex.x, vertex.y);
            glTexCoord2f(texCoords[i], texCoords[i+1]);
        }
        glEnd();

        glBindTexture(GL_TEXTURE_2D, 0);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
}
