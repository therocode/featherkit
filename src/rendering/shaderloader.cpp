#include <framework/rendering/shaderloader.h>
#include <iostream>

namespace windbreeze
{
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

        return shaderProgram;
    }
}
