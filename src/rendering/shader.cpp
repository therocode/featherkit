#include <featherkit/rendering/shader.h>
#include <vector>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

namespace fea
{
    GLSLException::GLSLException(const std::string& message) : std::runtime_error(message)
    {
    }

    void Shader::setSource(const std::string& vertSource, const std::string& fragSource)
    {
        vertexSource = vertSource;
        fragmentSource = fragSource;
    }

    void Shader::activate() const
    {
        std::cout << "using shader id " << programId << "\n";
        glUseProgram(programId);
    }

    void Shader::deactivate() const
    {
        for(auto location : enabledVertexAttributes)
        {
            glDisableVertexAttribArray(location);
        }
        enabledVertexAttributes.clear();
        glUseProgram(0);
    }

    void Shader::setUniform(size_t index, UniformType type, const void* value) const
    {
        switch(type)
        {
            case FLOAT:
            {
                glUniform1f(uniformLocations.at(index), *((float*)value));
                break;
            }
            case VEC2:
            {
                const glm::vec2& val2 = *((glm::vec2*)value);
                glUniform2f(uniformLocations.at(index), val2.x, val2.y);
                break;
            }
            case VEC3:
            {
                const glm::vec3& val3 = *((glm::vec3*)value);
                glUniform3f(uniformLocations.at(index), val3.x, val3.y, val3.z);
                break;
            }
            case VEC4:
            {
                const glm::vec4& val4 = *((glm::vec4*)value);
                glUniform4f(uniformLocations.at(index), val4[0], val4[1], val4[2], val4[3]);
                break;
            }
            case MAT2X2:
            {
                const glm::mat2x2 mat = *((glm::mat2x2*)value);
                glUniformMatrix2fv(uniformLocations.at(index), 1, GL_FALSE, glm::value_ptr(mat));
                break;
            }
            case MAT4X4:
            {
                const glm::mat4x4 mat = *((glm::mat4x4*)value);
                glUniformMatrix4fv(uniformLocations.at(index), 1, GL_FALSE, glm::value_ptr(mat));
                break;
            }
            case TEXTURE:
            {
                glActiveTexture(GL_TEXTURE0);
                glUniform1i(uniformLocations.at(index), 0);
                glBindTexture(GL_TEXTURE_2D, *((GLuint*)value));
                break;
            }
        }
    }
    
    void Shader::setVertexAttribute(size_t index, const float* data) const
    {
        glEnableVertexAttribArray(vertexAttributeLocations.at(index));
        enabledVertexAttributes.push_back(vertexAttributeLocations.at(index));
        glVertexAttribPointer(vertexAttributeLocations.at(index), 2, GL_FLOAT, false, 0, data);
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
        }

        std::hash<std::string> stringHasher;

        std::stringstream vertStream(vertexSource);

        for(std::string line; std::getline(vertStream, line);)
        {
            if(line.find("attribute") != std::string::npos)
            {
                std::string name = line.substr( line.find_first_of(" ", line.find_first_of(" ") + 1) + 1, line.find_first_of(";") - line.find_first_of(" ", line.find_first_of(" ") + 1));
                name.resize(name.size() - 1);
                vertexAttributeLocations.emplace(stringHasher(name), glGetAttribLocation(programId , name.c_str()));
            }
            else if(line.find("uniform") != std::string::npos)
            {
                std::string name = line.substr( line.find_first_of(" ", line.find_first_of(" ") + 1) + 1, line.find_first_of(";") - line.find_first_of(" ", line.find_first_of(" ") + 1));
                name.resize(name.size() - 1);
                uniformLocations.emplace(stringHasher(name), glGetUniformLocation(programId , name.c_str()));
            }
        }
        
        std::stringstream fragStream(fragmentSource);

        for(std::string line; std::getline(fragStream, line);)
        {
            if(line.find("attribute") != std::string::npos)
            {
                std::string name = line.substr( line.find_first_of(" ", line.find_first_of(" ") + 1) + 1, line.find_first_of(";") - line.find_first_of(" ", line.find_first_of(" ") + 1));
                name.resize(name.size() - 1);
                vertexAttributeLocations.emplace(stringHasher(name), glGetAttribLocation(programId , name.c_str()));
            }
            else if(line.find("uniform") != std::string::npos)
            {
                std::string name = line.substr( line.find_first_of(" ", line.find_first_of(" ") + 1) + 1, line.find_first_of(";") - line.find_first_of(" ", line.find_first_of(" ") + 1));
                name.resize(name.size() - 1);
                uniformLocations.emplace(stringHasher(name), glGetUniformLocation(programId , name.c_str()));
            }
        }
    }
}
