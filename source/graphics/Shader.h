#pragma once

namespace NDR
{
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
        
        uint32_t GetProgram() const;

        void SetInt(const std::string& uniformName, int32_t value) const;
        void SetIntArray(const std::string& uniformName, int32_t* value, uint32_t count) const;
        void SetFloat(const std::string& uniformName, float value) const;
        void SetVec2(const std::string& uniformName, float x, float y) const;
        void SetVec2(const std::string& uniformName, glm::vec2 vec2) const;
        void SetVec3(const std::string& uniformName, float x, float y, float z) const;
        void SetVec3(const std::string& uniformName, glm::vec3 vec3) const;
        void SetVec4(const std::string& uniformName, float x, float y, float z, float w) const;
        void SetVec4(const std::string& uniformName, glm::vec4 vec4) const;
        void SetMat4(const std::string& uniformName, glm::mat4 mat4) const;
        
        static int32_t CompileSource(uint32_t shaderType, const std::string& source);

        friend bool operator==(const Shader& left, const Shader& right);
    private:
        int32_t GetUniformLocation(const std::string& uniformName) const;

        uint32_t _program;
        mutable std::unordered_map<std::string, uint32_t> _uniformLocationCache;
    };

    extern bool operator==(const Shader& left, const Shader& right);
    extern bool operator!=(const Shader& left, const Shader& right);
}