#pragma once
#include "Defines.h"

namespace NDR
{
    /*
     * TODO: Compose Shader of Unique Shader Stages
    */
    
    enum ShaderStage
    {
        VERTEX = 0, FRAGMENT = 1, COMPUTE = 2, GEOMETRY = 3
    };

    enum class ShaderType
    {
        NONE,
        BOOL,
        INT,
        UINT,
        FLOAT,
        VEC2,
        VEC3,
        VEC4,
        MAT4,
        SAMPLER2D
    };

    struct ShaderUniform
    {
    public:
        ShaderUniform(const std::string& name, Int32 location, UInt32 count, ShaderType type);

        std::string GetName() const;
        Int32 GetLocation() const;
        ShaderType GetType() const;
    private:
        std::string _name;
        Int32 _location;
        UInt32 _count;
        ShaderType _type;
    };
    
    class Shader
    {
    public:
        Shader(const std::string& vertexSource, const std::string& fragmentSource); 
        ~Shader();

        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;

        Shader(Shader&& other) noexcept;
        Shader& operator=(Shader&& other) noexcept;

        bool operator==(const Shader& other) const;
        bool operator!=(const Shader& other) const;
        
        RendererID GetRendererID() const { return _rendererID; }

        void SetInt(const std::string& uniformName, Int32 value) const;
        void SetIntArray(const std::string& uniformName, Int32* value, UInt32 count) const;
        void SetFloat(const std::string& uniformName, float value) const;
        void SetVec2(const std::string& uniformName, const glm::vec2& vec2) const;
        void SetVec3(const std::string& uniformName, const glm::vec3& vec3) const;
        void SetVec4(const std::string& uniformName, const glm::vec4& vec4) const;
        void SetMat4(const std::string& uniformName, const glm::mat4& mat4) const;
        
        static Int32 CompileSource(ShaderStage stage, const std::string& source);
    private:
        Int32 GetUniformLocation(const std::string& uniformName) const;
        
        RendererID _rendererID;
        std::vector<ShaderUniform> _uniformData;
    };

    size_t GetShaderTypeSize(ShaderType type);
}
