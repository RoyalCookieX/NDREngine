#pragma once
#include <string>
#include <unordered_map>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace NDR
{
    class Shader
    {
    public:
        Shader(const char* vertexSource, const char* fragmentSource);

        void Use() const;

        void SetInt(const std::string& uniformName, GLint value) const;
        void SetFloat(const std::string& uniformName, GLfloat value) const;
        void SetVec2(const std::string& uniformName, glm::vec2 vec2) const;
        void SetVec3(const std::string& uniformName, GLfloat x, GLfloat y, GLfloat z) const;
        void SetVec3(const std::string& uniformName, glm::vec3 vec3) const;
        void SetVec4(const std::string& uniformName, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const;
        void SetVec4(const std::string& uniformName, glm::vec4 vec4) const;
        void SetVec2(const std::string& uniformName, GLfloat x, GLfloat y) const;
        void SetMat4(const std::string& uniformName, glm::mat4 mat4) const;
        
        static GLuint CompileSource(GLenum shaderType, const char* source);
    private:
        GLint GetUniformLocation(const std::string& uniformName) const;
        
        GLuint _program;
        mutable std::unordered_map<std::string, GLint> _uniformLocationCache;
    };
}
