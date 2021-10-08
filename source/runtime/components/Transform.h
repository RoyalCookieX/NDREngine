#pragma once

namespace NDR
{
    struct Transform
    {
    public:
        Transform();
        Transform(const glm::mat4& matrix);
        Transform(const glm::vec3& position);
        Transform(const glm::vec3& position, const glm::quat& rotation);
        Transform(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale);
        
        const glm::mat4& GetMatrix() const;
        glm::vec3 GetPosition(bool isLocal = false) const;
        glm::quat GetRotation(bool isLocal = false) const;
        glm::vec3 GetScale() const;

        void SetPosition(const glm::vec3& position, bool isLocal = false);
        Transform& Translate(const glm::vec3& translation, bool isLocal = false);
        Transform Translate(const glm::vec3& translation, bool isLocal = false) const;
        
        void SetRotation(const glm::quat& rotation, bool isLocal = false);
        void SetRotation(const glm::vec3& euler, bool isLocal = false);
        void SetRotation(float angle, const glm::vec3& axis, bool isLocal = false);
        Transform& Rotate(const glm::quat& rotation, bool isLocal = false);
        Transform& Rotate(const glm::vec3& euler, bool isLocal = false);
        Transform& Rotate(float degrees, const glm::vec3& axis, bool isLocal = false);
        
        void SetScale(const glm::vec3& scale);
        Transform& Scale(const glm::vec3& scalar);

        glm::vec3 GetRight() const;
        glm::vec3 GetUp() const;
        glm::vec3 GetForward() const;
        
    private:
        std::tuple<glm::vec3, glm::quat, glm::vec3> Decompose() const;
        
        glm::mat4 _matrix;
    };
}
