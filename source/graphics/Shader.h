#pragma once

namespace NDR
{
    /*
     * TODO: Compose Shader of Unique Shader Stages
     * TODO: Use reflection to use the shader data for Materials
    */
    
    enum ShaderStage
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1, COMPUTE = 2, GEOMETRY = 3
    };
    
    class Shader
    {
    public:
        Shader();
        Shader(const std::string& vertexSource, const std::string& fragmentSource); 
        ~Shader();

        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;

        Shader(Shader&& other) noexcept;
        Shader& operator=(Shader&& other) noexcept;

        bool operator==(const Shader& other) const;
        bool operator!=(const Shader& other) const;
        
        uint32_t GetProgram() const;
        void Use() const;

        void SetInt(const std::string& uniformName, int32_t value) const;
        void SetIntArray(const std::string& uniformName, int32_t* value, uint32_t count) const;
        void SetFloat(const std::string& uniformName, float value) const;
        void SetVec2(const std::string& uniformName, const glm::vec2& vec2) const;
        void SetVec3(const std::string& uniformName, const glm::vec3& vec3) const;
        void SetVec4(const std::string& uniformName, const glm::vec4& vec4) const;
        void SetMat4(const std::string& uniformName, const glm::mat4& mat4) const;
        
        static int32_t CompileSource(ShaderStage stage, const std::string& source);
    
    private:
        int32_t GetUniformLocation(const std::string& uniformName) const;

        uint32_t _program;
        mutable std::unordered_map<std::string, uint32_t> _uniformLocationCache;
    };
}