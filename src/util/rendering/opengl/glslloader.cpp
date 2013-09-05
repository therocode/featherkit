#include <featherkit/util/rendering/opengl/glslloader.h>
#include <sstream>
#include <vector>

namespace fea
{
    GLSLException::GLSLException(const std::string& message) : std::runtime_error(message)
    {
    }

    GLuint GLSLLoader::createShader(std::string vertexSource, std::string fragmentSource)
    {
        const char* vertexShaderSourcePointer = &vertexSource[0];
        const char* fragmentShaderSourcePointer = &fragmentSource[0];

        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSourcePointer, NULL);
        glCompileShader(vertexShader);

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSourcePointer, NULL);
        glCompileShader(fragmentShader);

        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        GLint isCompiled = 0;

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if(!isCompiled)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> infoLog((size_t)maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
            std::stringstream ss;
            ss << "Error! Vertex shader compilation:\n" << std::string(&infoLog[0]) << "\n";
            throw(GLSLException(ss.str()));
            return 0;
        }

        isCompiled = 0;
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if(!isCompiled)
        {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> infoLog((size_t)maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
            std::stringstream ss;
            ss << "Error! Fragment shader compilation:\n" << std::string(&infoLog[0]) << "\n";
            throw(GLSLException(ss.str()));
            return 0;
        }

        return shaderProgram;
    }
}
