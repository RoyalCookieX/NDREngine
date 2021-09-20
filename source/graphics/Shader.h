#pragma once
#include <string>
#include <glad/glad.h>

namespace NDR
{
    class Shader
    {
    public:
        Shader(const char* vertexSource, const char* fragmentSource);
        void Use() const;
        
        static GLuint CompileSource(GLenum shaderType, const char* source);
    private:
        GLuint _program;
    };
}
