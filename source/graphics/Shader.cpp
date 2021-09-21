#include "Shader.h"

#include <iostream>

namespace NDR
{
    Shader::Shader(const char* vertexSource, const char* fragmentSource)
    {
        _program = glCreateProgram();
        const GLuint vs = CompileSource(GL_VERTEX_SHADER, vertexSource);
        const GLuint fs = CompileSource(GL_FRAGMENT_SHADER, fragmentSource);

        glAttachShader(_program, vs);
        glAttachShader(_program, fs);
        glLinkProgram(_program);
        glValidateProgram(_program);
        
        glDeleteShader(vs);
        glDeleteShader(fs);
    }

    void Shader::Use() const
    {
        glUseProgram(_program);
    }
    
    void Shader::SetFloat(const std::string& uniformName, GLfloat const x) const
    {
        const GLuint id = glGetUniformLocation(_program, uniformName.c_str());
        glUniform1f(id, x);
    }

    void Shader::SetVec2(const std::string& uniformName, GLfloat const x, GLfloat const y) const
    {
        const GLuint id = glGetUniformLocation(_program, uniformName.c_str());
        glUniform2f(id, x, y);
    }

    void Shader::SetVec3(const std::string& uniformName, GLfloat const x, GLfloat const y, GLfloat const z) const
    {
        const GLuint id = glGetUniformLocation(_program, uniformName.c_str());
        glUniform3f(id, x, y, z);
    }

    void Shader::SetVec4(const std::string& uniformName, GLfloat const x, GLfloat const y, GLfloat const z, const GLfloat w) const
    {
        const GLuint id = glGetUniformLocation(_program, uniformName.c_str());
        glUniform4f(id, x, y, z, w);
    }

    GLuint Shader::CompileSource(GLenum shaderType, const char* source)
    {
        const GLuint id = glCreateShader(shaderType);
        glShaderSource(id, 1, &source, nullptr);
        glCompileShader(id);

        GLint result;
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
}
