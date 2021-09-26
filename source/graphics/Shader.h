#pragma once

namespace NDR
{
    class Shader
    {
    public:
        virtual ~Shader() { }
        
        virtual void Use() const = 0;

        virtual void SetInt(const std::string& uniformName, int32_t value) const = 0;
        virtual void SetFloat(const std::string& uniformName, float value) const = 0;
        virtual void SetVec2(const std::string& uniformName, glm::vec2 vec2) const = 0;
        virtual void SetVec3(const std::string& uniformName, float x, float y, float z) const = 0;
        virtual void SetVec3(const std::string& uniformName, glm::vec3 vec3) const = 0;
        virtual void SetVec4(const std::string& uniformName, float x, float y, float z, float w) const = 0;
        virtual void SetVec4(const std::string& uniformName, glm::vec4 vec4) const = 0;
        virtual void SetVec2(const std::string& uniformName, float x, float y) const = 0;
        virtual void SetMat4(const std::string& uniformName, glm::mat4 mat4) const = 0;
        
        static int32_t CompileSource(uint32_t shaderType, const std::string& source);
        static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);
    protected:
        virtual int32_t GetUniformLocation(const std::string& uniformName) const = 0;
    };
}
