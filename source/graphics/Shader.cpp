#include "ndrpch.h"
#include "Shader.h"

#include "core/Log.h"

namespace NDR
{
    ShaderType GetShaderType(uint32_t shaderType)
    {
        switch (shaderType)
        {
            case GL_BOOL:           return ShaderType::BOOL; 
            case GL_INT:            return ShaderType::INT;  
            case GL_UNSIGNED_INT:   return ShaderType::UINT; 
            case GL_FLOAT:          return ShaderType::FLOAT;
            case GL_FLOAT_VEC2:     return ShaderType::VEC2; 
            case GL_FLOAT_VEC3:     return ShaderType::VEC3; 
            case GL_FLOAT_VEC4:     return ShaderType::VEC4; 
            case GL_FLOAT_MAT4:     return ShaderType::MAT4;
            case GL_SAMPLER_2D:     return ShaderType::SAMPLER2D;
            default:                return ShaderType::NONE;
        }
    }
    
    ShaderUniform::ShaderUniform(const std::string& name, int32_t location, uint32_t count, ShaderType type):
        _name(name),
        _location(location),
        _count(count),
        _type(type)
    {
    }

    std::string ShaderUniform::GetName() const { return _name; }
    int32_t ShaderUniform::GetLocation() const { return _location; }
    ShaderType ShaderUniform::GetType() const { return _type; }

    Shader::Shader():
        _program(0)
    {
    }
    
    Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
    {
        // create shader and its stages
        _program = glCreateProgram();
        const uint32_t vs = CompileSource(VERTEX, vertexSource);
        const uint32_t fs = CompileSource(FRAGMENT, fragmentSource);

        // compile/link shader
        glAttachShader(_program, vs);
        glAttachShader(_program, fs);
        glLinkProgram(_program);
        glValidateProgram(_program);

        // delete shader stages
        glDeleteShader(vs);
        glDeleteShader(fs);

        // get uniforms from shader
        int32_t maxLength;
        glGetProgramiv(_program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength);
        char* name = new char[maxLength + 1];

        // add uniforms to _uniformData
        int32_t uniformCount;
        glGetProgramiv(_program, GL_ACTIVE_UNIFORMS, &uniformCount);
        _uniformData.reserve(uniformCount);
        int32_t offset = 0;
        for(int32_t i = 0; i < uniformCount; i++)
        {
            int32_t size;
            uint32_t type;
            glGetActiveUniform(_program, i, maxLength, nullptr, &size, &type, name);
            std::string uniformName(name);
            //TODO: Only do this step with NVIDIA Drivers
            if(const auto leftBracketIndex = uniformName.find('['); leftBracketIndex != std::string::npos)
                uniformName.replace(leftBracketIndex, maxLength - leftBracketIndex, "");
            
            _uniformData.emplace_back(uniformName, offset, size, GetShaderType(type));
            offset += size;
        }
        
        delete[] name;
    }

    Shader::~Shader() { glDeleteProgram(_program); }

    Shader::Shader(Shader&& other) noexcept:
        _program(other._program),
        _uniformData(std::move(other._uniformData))
    {
        other._program = 0;
    }

    Shader& Shader::operator=(Shader&& other) noexcept
    {
        if(*this != other)
        {
            _program = other._program;
            _uniformData = std::move(other._uniformData);

            other._program = 0;
        }
        return *this;
    }

    bool Shader::operator==(const Shader& other) const { return _program == other._program; }
    bool Shader::operator!=(const Shader& other) const { return !(*this == other); }

    uint32_t Shader::GetProgram() const { return _program; }

    void Shader::Use() const { glUseProgram(_program); }

    void Shader::SetInt(const std::string& uniformName, const int32_t value) const
    {
        const uint32_t id = GetUniformLocation(uniformName);
        glUniform1i(id, value);
    }

    void Shader::SetIntArray(const std::string& uniformName, int32_t* values, uint32_t count) const
    {
        const uint32_t id = GetUniformLocation(uniformName);
        glUniform1iv(id, count, values);
    }

    void Shader::SetFloat(const std::string& uniformName, float const value) const
    {
        const uint32_t id = GetUniformLocation(uniformName);
        glUniform1f(id, value);
    }

    void Shader::SetVec2(const std::string& uniformName, const glm::vec2& vec2) const
    {
        const uint32_t id = GetUniformLocation(uniformName);
        glUniform2f(id, vec2.x, vec2.y);
    }

    void Shader::SetVec3(const std::string& uniformName, const glm::vec3& vec3) const
    {
        const uint32_t id = GetUniformLocation(uniformName);
        glUniform3f(id, vec3.x, vec3.y, vec3.z);
    }
    
    void Shader::SetVec4(const std::string& uniformName, const glm::vec4& vec4) const
    {
        const uint32_t id = GetUniformLocation(uniformName);
        glUniform4f(id, vec4.x, vec4.y, vec4.z, vec4.w);
    }

    void Shader::SetMat4(const std::string& uniformName, const glm::mat4& mat4) const
    {
        const uint32_t id = GetUniformLocation(uniformName);
        glUniformMatrix4fv(id, 1, false, glm::value_ptr(mat4));
    }

    int32_t Shader::GetUniformLocation(const std::string& uniformName) const
    {        
        for(auto uniform : _uniformData)
        {
            if(uniform.GetName() == uniformName)
                return uniform.GetLocation();
        }
        return -1;
    }

    int32_t Shader::CompileSource(ShaderStage stage, const std::string& source)
    {
        const char* src = source.c_str();
        char* shaderTypeName;
        uint32_t shaderType = 0;
        switch(stage)
        {
            case VERTEX:
                {
                    shaderType = GL_VERTEX_SHADER;
                    shaderTypeName = "Vertex";
                    break;
                }
            case FRAGMENT:
                {
                    shaderType = GL_FRAGMENT_SHADER;
                    shaderTypeName = "Fragment";
                    break;
                }
            default:
                {
                    shaderTypeName = "Unknown";
                    break;
                }
        }
        const uint32_t id = glCreateShader(shaderType);
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int32_t result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if(result == GL_FALSE)
        {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = (char*)alloca(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);
            NDR_LOGERROR("[%s Shader]: %s", shaderTypeName, message);
        }
        return id;
    }

    size_t GetShaderTypeSize(ShaderType type)
    {
        switch (type)
        {
            case ShaderType::BOOL:  return sizeof(bool);
            case ShaderType::INT:   return sizeof(int32_t);
            case ShaderType::UINT:  return sizeof(uint32_t);
            case ShaderType::FLOAT: return sizeof(float);
            case ShaderType::VEC2:  return sizeof(glm::vec2);
            case ShaderType::VEC3:  return sizeof(glm::vec3);
            case ShaderType::VEC4:  return sizeof(glm::vec4);
            case ShaderType::MAT4:  return sizeof(glm::mat4);
            default:                return 0;
        }
    }
}
