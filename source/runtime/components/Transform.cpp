#include "ndrpch.h"
#include "Transform.h"

namespace NDR
{
    Transform::Transform():
        Transform(glm::vec3(0.0f), glm::identity<glm::quat>(), glm::vec3(1.0f))
    {
    }

    Transform::Transform(const glm::vec3& position):
        Transform(position, glm::identity<glm::quat>(), glm::vec3(1.0f))
    {
    }

    Transform::Transform(const glm::vec3& position, const glm::quat& rotation):
        Transform(position, rotation, glm::vec3(1.0f))
    {
    }

    Transform::Transform(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale)
    {
        SetPosition(position);
        SetRotation(rotation);
        SetScale(scale);
    }

    glm::mat4 Transform::GetMatrix() const { return _matrix; }
    glm::vec3 Transform::GetPosition() const
    {
        auto[position,rotation,scale] = Decompose();
        return position;
    }
    glm::quat Transform::GetRotation() const
    {
        auto[position,rotation,scale] = Decompose();
        return rotation;
    }
    glm::vec3 Transform::GetScale() const
    {
        auto[position,rotation,scale] = Decompose();
        return scale;
    }

    void Transform::SetPosition(const glm::vec3& position) { _matrix = glm::translate(glm::mat4(1.0f), position); }
    void Transform::Translate(const glm::vec3& translation) { _matrix = glm::translate(_matrix, translation); }

    void Transform::SetRotation(const glm::quat& rotation) { _matrix = glm::toMat4(rotation); }
    void Transform::SetRotation(const glm::vec3& euler) { SetRotation(glm::quat(euler)); }
    void Transform::SetRotation(const float angle, const glm::vec3& axis) { SetRotation(glm::angleAxis(angle, axis)); }
    void Transform::Rotate(const glm::quat& rotation) { Rotate(glm::eulerAngles(rotation)); }
    void Transform::Rotate(const glm::vec3& euler) { _matrix = glm::toMat4(glm::quat(euler)) * _matrix; }
    void Transform::Rotate(const float angle, const glm::vec3& axis) { _matrix = glm::rotate(_matrix, angle, axis); }

    void Transform::SetScale(const glm::vec3& scale) { _matrix = glm::scale(glm::mat4(1.0f), scale); }
    void Transform::Scale(const glm::vec3& scalar) { _matrix = glm::scale(glm::mat4(1.0f), scalar); }

    glm::vec3 Transform::GetRight()     const { return glm::vec3(1.0f, 0.0f, 0.0f) * GetRotation(); }
    glm::vec3 Transform::GetUp()        const { return glm::vec3(0.0f, 1.0f, 0.0f) * GetRotation(); }
    glm::vec3 Transform::GetForward()   const { return glm::vec3(0.0f, 0.0f, 1.0f) * GetRotation(); }

    std::tuple<glm::vec3, glm::quat, glm::vec3> Transform::Decompose() const
    {
        glm::vec3 position;
        glm::quat rotation;
        glm::vec3 scale;
        glm::vec3 skew;
        glm::vec4 perspective;
        glm::decompose(_matrix, scale, rotation, position, skew, perspective);
        return std::make_tuple(position, rotation, scale);
    }
}
