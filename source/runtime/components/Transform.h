#pragma once

namespace NDR
{
    struct Transform
    {
    public:
        Transform();
        Transform(const glm::vec3& position);
        Transform(const glm::vec3& position, const glm::quat& rotation);
        Transform(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale);
        
        glm::mat4 GetMatrix() const;
        glm::vec3 GetPosition() const;
        glm::quat GetRotation() const;
        glm::vec3 GetScale() const;

        void SetPosition(const glm::vec3& position);
        void Translate(const glm::vec3& translation);
        
        void SetRotation(const glm::quat& rotation);
        void SetRotation(const glm::vec3& euler);
        void SetRotation(float angle, const glm::vec3& axis);
        void Rotate(const glm::quat& rotation);
        void Rotate(const glm::vec3& euler);
        void Rotate(float angle, const glm::vec3& axis);
        
        void SetScale(const glm::vec3& scale);
        void Scale(const glm::vec3& scalar);

        glm::vec3 GetRight() const;
        glm::vec3 GetUp() const;
        glm::vec3 GetForward() const;
        
    private:
        std::tuple<glm::vec3, glm::quat, glm::vec3> Decompose() const;
        
        glm::mat4 _matrix;
    };
}
