#include "ndrpch.h"
#include "Shader.h"

namespace NDR
{
    Shader::Shader(const char* vertexSource, const char* fragmentSource)
    {
        GLCall(_program = glCreateProgram());
        const GLuint vs = CompileSource(GL_VERTEX_SHADER, vertexSource);
        const GLuint fs = CompileSource(GL_FRAGMENT_SHADER, fragmentSource);

        GLCall(glAttachShader(_program, vs));
        GLCall(glAttachShader(_program, fs));
        GLCall(glLinkProgram(_program));
        GLCall(glValidateProgram(_program));
        
        GLCall(glDeleteShader(vs));
        GLCall(glDeleteShader(fs));
    }

    void Shader::Use() const
    {
        GLCall(glUseProgram(_program));
    }

    void Shader::SetInt(const std::string& uniformName, GLint value) const
    {
        const GLuint id = GetUniformLocation(uniformName);
        GLCall(glUniform1i(id, value));
    }

    void Shader::SetFloat(const std::string& uniformName, GLfloat const value) const
    {
        const GLuint id = GetUniformLocation(uniformName);
        GLCall(glUniform1f(id, value));
    }

    void Shader::SetVec2(const std::string& uniformName, glm::vec2 vec2) const { return SetVec2(uniformName, vec2.x, vec2.y); }
    void Shader::SetVec2(const std::string& uniformName, GLfloat const x, GLfloat const y) const
    {
        const GLuint id = GetUniformLocation(uniformName);
        GLCall(glUniform2f(id, x, y));
    }

    void Shader::SetVec3(const std::string& uniformName, glm::vec3 vec3) const { return SetVec3(uniformName, vec3.x, vec3.y, vec3.z); }
    void Shader::SetVec3(const std::string& uniformName, GLfloat const x, GLfloat const y, GLfloat const z) const
    {
        const GLuint id = GetUniformLocation(uniformName);
        GLCall(glUniform3f(id, x, y, z));
    }
    
    void Shader::SetVec4(const std::string& uniformName, glm::vec4 vec4) const { return SetVec4(uniformName, vec4.x, vec4.y, vec4.z, vec4.w); }
    void Shader::SetVec4(const std::string& uniformName, GLfloat const x, GLfloat const y, GLfloat const z, const GLfloat w) const
    {
        const GLuint id = GetUniformLocation(uniformName);
        GLCall(glUniform4f(id, x, y, z, w));
    }

    void Shader::SetMat4(const std::string& uniformName, glm::mat4 mat4) const
    {
        const GLuint id = GetUniformLocation(uniformName);

        GLfloat matrix[16] = { 0.0 };
        const GLfloat* pSource = value_ptr(mat4);
        for (int i = 0; i < 16; ++i)
            matrix[i] = pSource[i];
        
        GLCall(glUniformMatrix4fv(id, 1, false, matrix));
    }
    
    GLuint Shader::CompileSource(GLenum shaderType, const char* source)
    {
        GLCall(const GLuint id = glCreateShader(shaderType));
        GLCall(glShaderSource(id, 1, &source, nullptr));
        GLCall(glCompileShader(id));

        GLint result;
        GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
        if(result == GL_FALSE)
        {
            int length;
            GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
            char* message = (char*)alloca(length * sizeof(char));
            GLCall(glGetShaderInfoLog(id, length, &length, message));
            std::cout << "[OpenGL]: " << (shaderType == GL_VERTEX_SHADER ? "Vertex"
                :shaderType == GL_FRAGMENT_SHADER ? "Fragment"
                :"Unknown") << " Shader Failed to compile!\n" << message << std::endl;;
        }
        return id;
    }

    GLint Shader::GetUniformLocation(const std::string& uniformName) const
    {
        if(_uniformLocationCache.find(uniformName) == _uniformLocationCache.end())
        {
            GLCall(GLint id = glGetUniformLocation(_program, uniformName.c_str()));
            _uniformLocationCache.emplace(uniformName, id);
            return id;
        }
        return _uniformLocationCache[uniformName];
    }
}
