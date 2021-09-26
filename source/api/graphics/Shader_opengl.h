#pragma once
#include "graphics/Shader.h"

namespace NDR {namespace GraphicsAPI
{
    class Shader_opengl : public Shader
    {
    public:
        Shader_opengl(const std::string& vertexSource, const std::string& fragmentSource);
        virtual ~Shader_opengl() override;

        virtual void Use() const override;
        
        virtual void SetInt(const std::string& uniformName, int32_t value) const override;
        virtual void SetFloat(const std::string& uniformName, float value) const override;
        virtual void SetVec2(const std::string& uniformName, glm::vec2 vec2) const override;
        virtual void SetVec3(const std::string& uniformName, float x, float y, float z) const override;
        virtual void SetVec3(const std::string& uniformName, glm::vec3 vec3) const override;
        virtual void SetVec4(const std::string& uniformName, float x, float y, float z, float w) const override;
        virtual void SetVec4(const std::string& uniformName, glm::vec4 vec4) const override;
        virtual void SetVec2(const std::string& uniformName, float x, float y) const override;
        virtual void SetMat4(const std::string& uniformName, glm::mat4 mat4) const override;
    protected:
        virtual int32_t GetUniformLocation(const std::string& uniformName) const override;
    private:
        int32_t _program = 0;
        mutable std::unordered_map<std::string, uint32_t> _uniformLocationCache;
    };
}
}
