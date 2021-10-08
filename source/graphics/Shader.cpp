#include "ndrpch.h"
#include "Shader.h"

namespace NDR
{
    Shader::Shader(): _program(0) { }
    Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
    {
        _program = glCreateProgram();
        const uint32_t vs = CompileSource(GL_VERTEX_SHADER, vertexSource.c_str());
        const uint32_t fs = CompileSource(GL_FRAGMENT_SHADER, fragmentSource.c_str());

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
        _uniformLocationCache(other._uniformLocationCache)
    {
        other._program = 0;
        other._uniformLocationCache.clear();
    }

    Shader& Shader::operator=(Shader&& other) noexcept
    {
        if(*this != other)
        {
            _program = other._program;
            _uniformLocationCache = other._uniformLocationCache;

            other._program = 0;
            other._uniformLocationCache.clear();
        }
        return *this;
    }

    void Shader::Use() const { glUseProgram(_program); }

        void Shader::SetInt(const std::string& uniformName, int32_t value) const
    {
        const uint32_t id = GetUniformLocation(uniformName);
        glUniform1i(id, value);
    }

    void Shader::SetFloat(const std::string& uniformName, float const value) const
    {
        const uint32_t id = GetUniformLocation(uniformName);
        glUniform1f(id, value);
    }

    void Shader::SetVec2(const std::string& uniformName, glm::vec2 vec2) const { return SetVec2(uniformName, vec2.x, vec2.y); }
    void Shader::SetVec2(const std::string& uniformName, float const x, float const y) const
    {
        const uint32_t id = GetUniformLocation(uniformName);
        glUniform2f(id, x, y);
    }

    void Shader::SetVec3(const std::string& uniformName, glm::vec3 vec3) const { return SetVec3(uniformName, vec3.x, vec3.y, vec3.z); }
    void Shader::SetVec3(const std::string& uniformName, float const x, float const y, float const z) const
    {
        const uint32_t id = GetUniformLocation(uniformName);
        glUniform3f(id, x, y, z);
    }
    
    void Shader::SetVec4(const std::string& uniformName, glm::vec4 vec4) const { return SetVec4(uniformName, vec4.x, vec4.y, vec4.z, vec4.w); }

    void Shader::SetVec4(const std::string& uniformName, float const x, float const y, float const z, const float w) const
    {
        const uint32_t id = GetUniformLocation(uniformName);
        glUniform4f(id, x, y, z, w);
    }

    void Shader::SetMat4(const std::string& uniformName, glm::mat4 mat4) const
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

    int32_t Shader::CompileSource(uint32_t shaderType, const std::string& source)
    {
        const char* src = source.c_str();
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
            std::cout << "[OpenGL]: " << (shaderType == GL_VERTEX_SHADER ? "Vertex"
                :shaderType == GL_FRAGMENT_SHADER ? "Fragment"
                :"Unknown") << " Shader Failed to compile!\n" << message << std::endl;;
        }
        return id;
    }
    bool operator==(const Shader& left, const Shader& right) { return left._program == right._program; }
    bool operator!=(const Shader& left, const Shader& right) { return !(left == right); }
}
