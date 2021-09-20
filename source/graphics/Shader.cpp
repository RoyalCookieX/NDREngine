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
