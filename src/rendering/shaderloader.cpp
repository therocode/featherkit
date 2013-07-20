#include <featherkit/rendering/shaderloader.h>
#include <sstream>

namespace fk
{
    ShaderException::ShaderException(const std::string& message) : std::runtime_error(message)
    {
    };

    GLuint ShaderLoader::createShader(std::string vertexSource, std::string fragmentSource)
    {
        const char* vertexShaderSourcePointer = &vertexSource[0];
        const char* fragmentShaderSourcePointer = &fragmentSource[0];

        GLuint vertexShader = glCreateShaderObjectARB(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSourcePointer, NULL);
        glCompileShader(vertexShader);

        GLuint fragmentShader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSourcePointer, NULL);
        glCompileShader(fragmentShader);

        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        //////getting error
        GLint blen = 0; 
        GLsizei slen = 0;

        if(glGetError())
        {
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH , &blen);       
            if (blen > 1)
            {
                GLchar* compiler_log = (GLchar*)malloc(blen);
                glGetInfoLogARB(vertexShader, blen, &slen, compiler_log);
                std::stringstream ss;
                ss << "Error! Vertex shader compilation:\n" << compiler_log << "\n";
                free (compiler_log);
                throw(ShaderException(ss.str()));
            }
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH , &blen);       
            if (blen > 1)
            {
                GLchar* compiler_log = (GLchar*)malloc(blen);
                glGetInfoLogARB(fragmentShader, blen, &slen, compiler_log);
                std::stringstream ss;
                ss << "Error! Fragment shader compilation:\n" << compiler_log << "\n";
                free (compiler_log);
                throw(ShaderException(ss.str()));
            }
            glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH , &blen);       
            if (blen > 1)
            {
                GLchar* compiler_log = (GLchar*)malloc(blen);
                glGetInfoLogARB(shaderProgram, blen, &slen, compiler_log);
                std::stringstream ss;
                ss << "Error! Shader program compilation:\n" << compiler_log << "\n";
                free (compiler_log);
                throw(ShaderException(ss.str()));
            }
        }

        return shaderProgram;
    }
}
