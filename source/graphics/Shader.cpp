#include "ndrpch.h"
#include "Shader.h"

namespace NDR
{
    Shader::Shader():
        _program(0)
    {
    }
    
    Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
    {
        _program = glCreateProgram();
        const uint32_t vs = CompileSource(VERTEX, vertexSource);
        const uint32_t fs = CompileSource(FRAGMENT, fragmentSource);

        glAttachShader(_program, vs);
        glAttachShader(_program, fs);
        glLinkProgram(_program);
        glValidateProgram(_program);
        
        glDeleteShader(vs);
        glDeleteShader(fs);
    }

    Shader::~Shader() { glDeleteProgram(_program); }

    Shader::Shader(Shader&& other) noexcept:
        _program(other._program),
        _uniformLocationCache(std::move(other._uniformLocationCache))
    {
        other._program = 0;
    }

    Shader& Shader::operator=(Shader&& other) noexcept
    {
        if(*this != other)
        {
            _program = other._program;
            _uniformLocationCache = std::move(other._uniformLocationCache);

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
        if(_uniformLocationCache.find(uniformName) == _uniformLocationCache.end())
        {
            uint32_t id = glGetUniformLocation(_program, uniformName.c_str());
            _uniformLocationCache.emplace(uniformName, id);
            return id;
        }
        return _uniformLocationCache[uniformName];
    }

    int32_t Shader::CompileSource(ShaderStage stage, const std::string& source)
    {
        const char* src = source.c_str();
        uint32_t shaderType = 0;
        switch(stage)
        {
            case VERTEX: shaderType = GL_VERTEX_SHADER; break;
            case FRAGMENT: shaderType = GL_FRAGMENT_SHADER; break;
            default: break;
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
            std::cout << "[OpenGL Error]: " <<
                ( shaderType == GL_VERTEX_SHADER ?   "Vertex"
                : shaderType == GL_FRAGMENT_SHADER ? "Fragment"
                : "Unknown")
            << " Shader Failed to compile! " << message << std::endl;
        }
        return id;
    }
}
