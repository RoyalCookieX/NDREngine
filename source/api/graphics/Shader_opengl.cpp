#include "ndrpch.h"
#include "Shader_opengl.h"

namespace NDR
{
    int32_t Shader::CompileSource(uint32_t shaderType, const std::string& source)
    {
        const char* src = source.c_str();
        const GLuint id = glCreateShader(shaderType);
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
    
    Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
    {
        return new GraphicsAPI::Shader_opengl(vertexSource, fragmentSource);
    }

namespace GraphicsAPI
{
    Shader_opengl::Shader_opengl(const std::string& vertexSource, const std::string& fragmentSource)
    {
        _program = glCreateProgram();
        const GLuint vs = CompileSource(GL_VERTEX_SHADER, vertexSource.c_str());
        const GLuint fs = CompileSource(GL_FRAGMENT_SHADER, fragmentSource.c_str());

        glAttachShader(_program, vs);
        glAttachShader(_program, fs);
        glLinkProgram(_program);
        glValidateProgram(_program);
        
        glDeleteShader(vs);
        glDeleteShader(fs);
    }

    Shader_opengl::~Shader_opengl()
    {
        glDeleteProgram(_program);
    }


    void Shader_opengl::Use() const
    {
        glUseProgram(_program);
    }

    void Shader_opengl::SetInt(const std::string& uniformName, int32_t value) const
    {
        const GLuint id = GetUniformLocation(uniformName);
        glUniform1i(id, value);
    }

    void Shader_opengl::SetFloat(const std::string& uniformName, float const value) const
    {
        const GLuint id = GetUniformLocation(uniformName);
        glUniform1f(id, value);
    }

    void Shader_opengl::SetVec2(const std::string& uniformName, glm::vec2 vec2) const { return SetVec2(uniformName, vec2.x, vec2.y); }
    void Shader_opengl::SetVec2(const std::string& uniformName, float const x, float const y) const
    {
        const GLuint id = GetUniformLocation(uniformName);
        glUniform2f(id, x, y);
    }

    void Shader_opengl::SetVec3(const std::string& uniformName, glm::vec3 vec3) const { return SetVec3(uniformName, vec3.x, vec3.y, vec3.z); }
    void Shader_opengl::SetVec3(const std::string& uniformName, float const x, float const y, float const z) const
    {
        const GLuint id = GetUniformLocation(uniformName);
        glUniform3f(id, x, y, z);
    }
    
    void Shader_opengl::SetVec4(const std::string& uniformName, glm::vec4 vec4) const { return SetVec4(uniformName, vec4.x, vec4.y, vec4.z, vec4.w); }
    void Shader_opengl::SetVec4(const std::string& uniformName, float const x, float const y, float const z, const float w) const
    {
        const GLuint id = GetUniformLocation(uniformName);
        glUniform4f(id, x, y, z, w);
    }

    void Shader_opengl::SetMat4(const std::string& uniformName, glm::mat4 mat4) const
    {
        const GLuint id = GetUniformLocation(uniformName);

        float matrix[16] = { 0.0 };
        const float* pSource = value_ptr(mat4);
        for (int i = 0; i < 16; ++i)
            matrix[i] = pSource[i];
        
        glUniformMatrix4fv(id, 1, false, matrix);
    }

    int32_t Shader_opengl::GetUniformLocation(const std::string& uniformName) const
    {
        if(_uniformLocationCache.find(uniformName) == _uniformLocationCache.end())
        {
            int32_t id = glGetUniformLocation(_program, uniformName.c_str());
            _uniformLocationCache.emplace(uniformName, id);
            return id;
        }
        return _uniformLocationCache[uniformName];
    }
}
}
