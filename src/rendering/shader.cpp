#include <featherkit/rendering/shader.h>

namespace fea
{
    void Shader::setSource(const std::string& vertSource, const std::string& fragSource)
    {
        vertexSource = vertSource;
        fragmentSource = fragSource;
    }

    void Shader::activate()
    {
        glUseProgram(programId);
    }

    void deactivate()
    {
        glUseProgram(0);
    }

    void Shader::setUniform(uint32_t index, Uniform::Type type, void* value)
    {
        switch(type)
        {
            case Uniform::FLOAT:
                glUniform1f(uniformLocations[index], *((float*)value));
                break;
            case Uniform::VEC2:
                glUniform2f(uniformLocations[index], *((float*)value), *(((float*)value)++));
                break;
            case Uniform::VEC3:
                glUniform2f(uniformLocations[index], *((float*)value), *(((float*)value) + 1), *(((float*)value) + 2));
                break;
        }
    }
    
    void Shader::setVertexAttribute(uint32_t index, float* data)
    {
        glVertexAttribPointer(vertexAttributeLocations[index], 2, GL_FLOAT, false, 0, data);
    }

    void Shader::compile()
    {
        const char* vertexShaderSourcePointer = &vertexSource[0];
        const char* fragmentShaderSourcePointer = &fragmentSource[0];

        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSourcePointer, NULL);
        glCompileShader(vertexShader);

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSourcePointer, NULL);
        glCompileShader(fragmentShader);

        programId = glCreateProgram();
        glAttachShader(programId, vertexShader);
        glAttachShader(programId, fragmentShader);
        glLinkProgram(programId);

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

        std::hash<str::string> stringHasher;

        std::stringstream vertStream(vertexSource);

        for(std::string line; std::getLine(vertStream, line);)
        {
            if(line.find("attribute") != line.end())
            {
                std::string name = line.substr( line.find_last_of(" ") + 1, std::string::npos);
                vertexAttributeLocations.emplace(stringHasher(name), glGetAttribLocation(programId , name));
            }
            else if(line.find("uniform") != line.end())
            {
                std::string name = line.substr( line.find_last_of(" ") + 1, std::string::npos);
                uniformLocations.emplace(stringHasher(name), glGetUniformLocation(programId , name));
            }
        }
        
        std::stringstream fragStream(fragmentShader);

        for(std::string line; std::getLine(fragStream, line);)
        {
            if(line.find("attribute") != line.end())
            {
                std::string name = line.substr( line.find_last_of(" ") + 1, std::string::npos);
                vertexAttributeLocations.emplace(stringHasher(name), glGetAttribLocation(programId , name));
            }
            else if(line.find("uniform") != line.end())
            {
                std::string name = line.substr( line.find_last_of(" ") + 1, std::string::npos);
                uniformLocations.emplace(stringHasher(name), glGetUniformLocation(programId , name));
            }
        }
    }
}
