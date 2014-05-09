#include <featherkit/rendering/shader.hpp>
#include <vector>
#include <sstream>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>

namespace fea
{
    GLSLException::GLSLException(const std::string& message) : std::runtime_error(message)
    {
    }

    void Shader::setSource(const std::string& vertexSource, const std::string& fragmentSource)
    {
        mVertexSource = vertexSource;
        mFragmentSource = fragmentSource;
    }

    void Shader::activate() const
    {
        glUseProgram(mProgramId);
    }

    void Shader::deactivate() const
    {
        for(auto location : mEnabledVertexAttributes)
        {
            glDisableVertexAttribArray(location);
        }
        mEnabledVertexAttributes.clear();
        glUseProgram(0);
    }

    void Shader::setUniform(const std::string& name, UniformType type, const void* value) const
    {
        switch(type)
        {
            case FLOAT:
            {
                glUniform1f(mUniformLocations.at(name), *((float*)value));
                break;
            }
            case VEC2:
            {
                const glm::vec2& val2 = *((glm::vec2*)value);
                glUniform2f(mUniformLocations.at(name), val2.x, val2.y);
                break;
            }
            case VEC3:
            {
                const glm::vec3& val3 = *((glm::vec3*)value);
                glUniform3f(mUniformLocations.at(name), val3.x, val3.y, val3.z);
                break;
            }
            case VEC4:
            {
                const glm::vec4& val4 = *((glm::vec4*)value);
                glUniform4f(mUniformLocations.at(name), val4[0], val4[1], val4[2], val4[3]);
                break;
            }
            case MAT2X2:
            {
                const glm::mat2x2 mat = *((glm::mat2x2*)value);
                glUniformMatrix2fv(mUniformLocations.at(name), 1, GL_FALSE, glm::value_ptr(mat));
                break;
            }
            case MAT4X4:
            {
                const glm::mat4x4 mat = *((glm::mat4x4*)value);
                glUniformMatrix4fv(mUniformLocations.at(name), 1, GL_FALSE, glm::value_ptr(mat));
                break;
            }
            case TEXTURE:
            {
                glActiveTexture(GL_TEXTURE0);
                glUniform1i(mUniformLocations.at(name), 0);
                glBindTexture(GL_TEXTURE_2D, *((GLuint*)value));
                break;
            }
        }
    }

    void Shader::setUniform(const std::string& name, UniformType type, int count, const void* value) const
    {
        switch(type)
        {
            case FLOAT:
            {
                glUniform1fv(mUniformLocations.at(name), count, ((float*)value));
                break;
            }
            case VEC2:
            {
                glUniform2fv(mUniformLocations.at(name), count, ((float*)value));
                break;
            }
            case VEC3:
            {
                glUniform3fv(mUniformLocations.at(name), count, ((float*)value));
                break;
            }
            case VEC4:
            {
                glUniform4fv(mUniformLocations.at(name), count, ((float*)value));
                break;
            }
            case MAT2X2:
            {
                const glm::mat2x2* mat = ((glm::mat2x2*)value);
                glUniformMatrix2fv(mUniformLocations.at(name), count, GL_FALSE, glm::value_ptr(*mat));
                break;
            }
            case MAT4X4:
            {
                const glm::mat4x4* mat = ((glm::mat4x4*)value);
                glUniformMatrix4fv(mUniformLocations.at(name), count, GL_FALSE, glm::value_ptr(*mat));
                break;
            }
            case TEXTURE:
            {
                glActiveTexture(GL_TEXTURE0);
                glUniform1i(mUniformLocations.at(name), 0);
                glBindTexture(GL_TEXTURE_2D, *((GLuint*)value));
                break;
            }
        }
    }

    void Shader::setVertexAttribute(const std::string& name, const uint32_t floatAmount, const float* data) const
    {
        glEnableVertexAttribArray(mVertexAttributeLocations.at(name));
        mEnabledVertexAttributes.push_back(mVertexAttributeLocations.at(name));
        glVertexAttribPointer(mVertexAttributeLocations.at(name), floatAmount, GL_FLOAT, false, 0, data);
    }

    void Shader::compile()
    {
        const char* vertexShaderSourcePointer = &mVertexSource[0];
        const char* fragmentShaderSourcePointer = &mFragmentSource[0];

        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSourcePointer, NULL);
        glCompileShader(vertexShader);

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSourcePointer, NULL);
        glCompileShader(fragmentShader);

        mProgramId = glCreateProgram();
        glAttachShader(mProgramId, vertexShader);
        glAttachShader(mProgramId, fragmentShader);
        glLinkProgram(mProgramId);

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

        std::stringstream vertStream(mVertexSource);

        for(std::string line; std::getline(vertStream, line);)
        {
            if(line.find("attribute") != std::string::npos)
            {
                std::string name = line.substr( line.find_first_of(" ", line.find_first_of(" ") + 1) + 1, line.find_first_of(";") - line.find_first_of(" ", line.find_first_of(" ") + 1));
                name.resize(name.size() - 1);
                mVertexAttributeLocations.emplace(name, glGetAttribLocation(mProgramId , name.c_str()));
            }
            else if(line.find("uniform") != std::string::npos)
            {
                std::string name = line.substr( line.find_first_of(" ", line.find_first_of(" ") + 1) + 1, line.find_first_of("[;") - line.find_first_of(" ", line.find_first_of(" ") + 1));
                name.resize(name.size() - 1);
                mUniformLocations.emplace(name, glGetUniformLocation(mProgramId , name.c_str()));
            }
        }
        
        std::stringstream fragStream(mFragmentSource);

        for(std::string line; std::getline(fragStream, line);)
        {
            if(line.find("attribute") != std::string::npos)
            {
                std::string name = line.substr( line.find_first_of(" ", line.find_first_of(" ") + 1) + 1, line.find_first_of(";") - line.find_first_of(" ", line.find_first_of(" ") + 1));
                name.resize(name.size() - 1);
                mVertexAttributeLocations.emplace(name, glGetAttribLocation(mProgramId , name.c_str()));
            }
            else if(line.find("uniform") != std::string::npos)
            {
                std::string name = line.substr( line.find_first_of(" ", line.find_first_of(" ") + 1) + 1, line.find_first_of("[;") - line.find_first_of(" ", line.find_first_of(" ") + 1));
                name.resize(name.size() - 1);
                mUniformLocations.emplace(name, glGetUniformLocation(mProgramId , name.c_str()));
            }
        }
    }
}
