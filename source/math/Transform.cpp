#include "ndrpch.h"
#include "Transform.h"

namespace NDR
{
    Transform::Transform():
        Transform(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f))
    {
    }

    Transform::Transform(const glm::mat4& matrix)
    {
        glm::vec3 skew;
        glm::vec4 perspective;
        glm::decompose(matrix, _scale, _rotation, _position, skew, perspective);
    }

    Transform::Transform(const glm::vec3& position):
        Transform(position, glm::vec3(0.0f), glm::vec3(1.0f))
    {
    }

    Transform::Transform(const glm::vec3& position, const glm::vec3& euler):
        Transform(position, euler, glm::vec3(1.0f))
    {
    }

    Transform::Transform(const glm::vec3& position, const glm::vec3& euler, const glm::vec3& scale)
    {
        SetPosition(position);
        SetRotation(euler);
        SetScale(scale);
    }

    glm::mat4 Transform::GetMatrix() const
    {
        const glm::mat4 posMatrix = glm::translate(_position);
        
        const glm::vec3 euler = glm::eulerAngles(_rotation);
        const glm::mat4 rotMatrix = glm::eulerAngleXYZ(euler.x, euler.y, euler.z);       
        const glm::mat4 scaleMatrix = glm::scale(_scale);

        return posMatrix * rotMatrix * scaleMatrix;
    }

    const glm::vec3& Transform::GetPosition() const { return _position; }
    const glm::quat& Transform::GetRotation() const { return _rotation; }
    const glm::vec3& Transform::GetScale() const { return _scale; }

    Transform& Transform::SetPosition(const glm::vec3& position)
    {
        _position = position;
        return *this;
    }

    Transform& Transform::SetRotation(const glm::vec3& euler)
    {
        _rotation = glm::quat(glm::radians(euler));
        return *this;
    }

    Transform& Transform::SetScale(const glm::vec3& scale)
    {
        _scale = scale;
        return *this;
    }

    Transform& Transform::Translate(const glm::vec3& translation)
    {
        _position += translation;
        return *this;
    }
    Transform& Transform::Rotate(const glm::vec3& euler)
    {
        const glm::vec3 degrees = glm::radians(euler);
        _rotation = glm::toQuat(glm::eulerAngleXYZ(degrees.x, degrees.y, degrees.z)) * _rotation;
        return *this;
    }

    Transform& Transform::Scale(const glm::vec3& scalar)
    {
        _scale *= scalar;
        return *this;
    }

    glm::vec3 Transform::GetRight() const       { return _rotation * glm::vec3(1.0f, 0.0f, 0.0f); }
    glm::vec3 Transform::GetUp() const          { return _rotation * glm::vec3(0.0f, 1.0f, 0.0f); }
    glm::vec3 Transform::GetForward() const     { return _rotation * glm::vec3(0.0f, 0.0f, 1.0f); }
}
