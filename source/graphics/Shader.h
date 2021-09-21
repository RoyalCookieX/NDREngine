#pragma once
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace NDR
{
    class Shader
    {
    public:
        Shader(const char* vertexSource, const char* fragmentSource);

        void Use() const;
        
        void SetFloat(const std::string& uniformName, GLfloat x) const;
        void SetVec2(const std::string& uniformName, GLfloat x, GLfloat y) const;
        void SetVec3(const std::string& uniformName, GLfloat x, GLfloat y, GLfloat z) const;
        void SetVec4(const std::string& uniformName, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const;
        
        static GLuint CompileSource(GLenum shaderType, const char* source);
    private:
        GLuint _program;
    };
}
