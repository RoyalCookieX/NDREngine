#pragma once

namespace NDR
{
    struct Transform
    {
    public:
        Transform();
        Transform(const glm::mat4& matrix);
        Transform(const glm::vec3& position);
        Transform(const glm::vec3& position, const glm::vec3& euler);
        Transform(const glm::vec3& position, const glm::vec3& euler, const glm::vec3& scale);
        
        glm::mat4 GetMatrix() const;
        const glm::vec3& GetPosition() const;
        const glm::quat& GetRotation() const;
        const glm::vec3& GetScale() const;

        Transform& SetPosition(const glm::vec3& position);
        Transform& SetRotation(const glm::vec3& euler);
        Transform& SetScale(const glm::vec3& scale);

        Transform& Translate(const glm::vec3& translation);
        Transform& Rotate(const glm::vec3& euler);
        Transform& Scale(const glm::vec3& scalar);

        glm::vec3 GetRight() const;
        glm::vec3 GetUp() const;
        glm::vec3 GetForward() const;
    private:     
        //TODO: replace _position, _rotation, and _scale with _matrix
        glm::vec3 _position;
        glm::quat _rotation;
        glm::vec3 _scale;
    };
}
