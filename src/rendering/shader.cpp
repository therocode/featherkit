#include <fea/rendering/shader.hpp>
#include <fea/assert.hpp>
#include <vector>
#include <sstream>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>

namespace fea
{
    GLSLException::GLSLException(const std::string& message) : std::runtime_error(message)
    {
    }

    Shader::Shader() :
        mVertexShader(0),
        mFragmentShader(0),
        mProgramId(0)
    {
    }

    Shader::Shader(Shader&& other) :
        mVertexShader(0),
        mFragmentShader(0),
        mProgramId(0)
    {
        mUniformLocations = std::move(other.mUniformLocations);
        mVertexAttributeLocations = std::move(other.mVertexAttributeLocations);
        mVertexSource = std::move(other.mVertexSource);
        mFragmentSource = std::move(other.mFragmentSource);
        mEnabledVertexAttributes = std::move(other.mEnabledVertexAttributes);
        std::swap(mProgramId, other.mProgramId);
        std::swap(mVertexShader, other.mVertexShader);
        std::swap(mFragmentShader, other.mFragmentShader);
    }

    Shader& Shader::operator=(Shader&& other)
    {
        mUniformLocations = std::move(other.mUniformLocations);
        mVertexAttributeLocations = std::move(other.mVertexAttributeLocations);
        mVertexSource = std::move(other.mVertexSource);
        mFragmentSource = std::move(other.mFragmentSource);
        mEnabledVertexAttributes = std::move(other.mEnabledVertexAttributes);
        std::swap(mProgramId, other.mProgramId);
        std::swap(mVertexShader, other.mVertexShader);
        std::swap(mFragmentShader, other.mFragmentShader);
        return *this;
    }

    Shader::~Shader()
    {
        if(mProgramId)
        {
            glDeleteShader(mVertexShader);
            glDeleteShader(mFragmentShader);
            glDeleteProgram(mProgramId);
        }

        for(const auto& buffer : mVertexAttributeBuffers)
        {
            glDeleteBuffers(1, &buffer.second);
        }
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

    void Shader::setUniform(const std::string& name, const Uniform& uniform) const
    {
        auto type = uniform.mType;
        const void* value = &uniform.mFloatVal;

        switch(type)
        {
            case FLOAT:
            {
                glUniform1f(mUniformLocations.at(name), *((const float*)value));
                break;
            }
            case INT:
            {
                glUniform1i(mUniformLocations.at(name), *((const int32_t*)value));
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
                FEA_ASSERT(GL_TEXTURE0 + 1 == GL_TEXTURE1, "Wrong assumption about GL constants. This is a bug");
                glActiveTexture(GL_TEXTURE0 + uniform.mTextureVal.index);
                glUniform1i(mUniformLocations.at(name), uniform.mTextureVal.index);
                glBindTexture(GL_TEXTURE_2D, uniform.mTextureVal.id);
                break;
            }
            case NO_TYPE:
            {
                FEA_ASSERT(false, "Cannot set null uniform on shader!\n");
                break;
            }
        }
    }

    void Shader::setUniform(const std::string& name, UniformType type, int32_t count, const void* value) const
    {
        switch(type)
        {
            case FLOAT:
            {
                glUniform1fv(mUniformLocations.at(name), count, ((float*)value));
                break;
            }
            case INT:
            {
                glUniform1iv(mUniformLocations.at(name), count, ((int32_t*)value));
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
                FEA_ASSERT(false, "Not supported");
                break;
            }
            case NO_TYPE:
            {
                FEA_ASSERT(false, "Cannot set null uniform on shader!\n");
                break;
            }
        }
    }

    void Shader::setVertexAttribute(const std::string& name, const uint32_t floatAmount, const float* data, int32_t count)
    {
        if(mVertexAttributeBuffers.count(name) == 0)
        {
            GLuint newBuffer;
            glGenBuffers(1, &newBuffer);

            mVertexAttributeBuffers.emplace(name, newBuffer);
        }

        glBindBuffer(GL_ARRAY_BUFFER, mVertexAttributeBuffers.at(name));
        glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(mVertexAttributeLocations.at(name));
        mEnabledVertexAttributes.push_back(mVertexAttributeLocations.at(name));
        glVertexAttribPointer(mVertexAttributeLocations.at(name), floatAmount, GL_FLOAT, false, 0, nullptr);
    }

    void Shader::compile()
    {
        const char* mVertexShaderSourcePointer = &mVertexSource[0];
        const char* mFragmentShaderSourcePointer = &mFragmentSource[0];

        mVertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(mVertexShader, 1, &mVertexShaderSourcePointer, NULL);
        glCompileShader(mVertexShader);

        mFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(mFragmentShader, 1, &mFragmentShaderSourcePointer, NULL);
        glCompileShader(mFragmentShader);

        mProgramId = glCreateProgram();
        glAttachShader(mProgramId, mVertexShader);
        glAttachShader(mProgramId, mFragmentShader);
        glLinkProgram(mProgramId);

        GLint isCompiled = 0;

        glGetShaderiv(mVertexShader, GL_COMPILE_STATUS, &isCompiled);
        if(!isCompiled)
        {
            GLint maxLength = 0;
            glGetShaderiv(mVertexShader, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> infoLog((size_t)maxLength);
            glGetShaderInfoLog(mVertexShader, maxLength, &maxLength, &infoLog[0]);
            std::stringstream ss;
            ss << "Error! Vertex shader compilation:\n" << std::string(&infoLog[0]) << "\n";
            throw(GLSLException(ss.str()));
        }

        isCompiled = 0;
        glGetShaderiv(mFragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if(!isCompiled)
        {
            GLint maxLength = 0;
            glGetShaderiv(mFragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> infoLog((size_t)maxLength);
            glGetShaderInfoLog(mFragmentShader, maxLength, &maxLength, &infoLog[0]);
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
