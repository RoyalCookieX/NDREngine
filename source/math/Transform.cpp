#include "ndrpch.h"
#include "Transform.h"

namespace NDR
{
    Transform::Transform():
        _matrix(MAT4_IDENTITY)
    {
        
    }

    Transform::Transform(const glm::mat4& matrix):
        _matrix(matrix)
    {
    }

    Transform::Transform(const glm::vec3& position):
        Transform(position, VEC3_ZERO, VEC3_ONE)
    {
    }

    Transform::Transform(const glm::vec3& position, const glm::vec3& euler):
        Transform(position, euler, VEC3_ONE)
    {
    }

    Transform::Transform(const glm::vec3& position, const glm::vec3& euler, const glm::vec3& scale)
    {
        const glm::mat4 posMatrix = glm::translate(position);
        const glm::mat4 rotMatrix = glm::toMat4(glm::quat(glm::radians(euler)));
        const glm::mat4 scaleMatrix = glm::scale(scale);
        _matrix = posMatrix * rotMatrix;
    }

    glm::mat4 Transform::GetMatrix() const { return _matrix; }
    glm::vec3 Transform::GetPosition(TransformSpace space) const
    {
        auto[p, r, s] = Decompose();
        return p;
    }

    glm::quat Transform::GetRotation(TransformSpace space) const
    {
        auto[p, r, s] = Decompose();
        return r;
    }

    glm::vec3 Transform::GetScale(TransformSpace space) const
    {
        auto[p, r, s] = Decompose();
        return s;
    }

    Transform& Transform::SetPosition(const glm::vec3& position, TransformSpace space)
    {
        const glm::mat4 inverse = glm::inverse(_matrix);
        _matrix = _matrix * glm::translate(position) * inverse;
        return *this;
    }

    Transform& Transform::SetRotation(const glm::vec3& eulerDeg, TransformSpace space)
    {
        const glm::mat4 inverse = glm::inverse(_matrix);
        _matrix = _matrix * glm::toMat4(glm::quat(glm::radians(eulerDeg))) * inverse;
        return *this;
    }

    Transform& Transform::SetScale(const glm::vec3& scale)
    {
        const glm::mat4 inverse = glm::inverse(_matrix);
        _matrix = _matrix * glm::scale(scale) * inverse;
        return *this;
    }

    Transform& Transform::Translate(const glm::vec3& translation, TransformSpace space)
    {
        _matrix = glm::translate(_matrix, GetRotation() * translation);
        return *this;
    }

    Transform& Transform::Rotate(const glm::vec3& eulerDeg, TransformSpace space)
    {
        return *this;
    }

    Transform& Transform::Rotate(const float degrees, const glm::vec3& axis, TransformSpace space)
    {
        const float radians = glm::radians(degrees);
        switch(space)
        {
            case TransformSpace::LOCAL:
                {
                    _matrix = glm::rotate(_matrix, radians, GetRotation() * axis);
                    break;
                }
            case TransformSpace::WORLD:
                {
                    _matrix = glm::rotate(_matrix, radians, axis);
                    break;
                }
        }
        return *this;
    }

    Transform& Transform::Scale(const glm::vec3& scalar)
    {
        return *this;
    }

    glm::vec3 Transform::GetRight() const { return GetRotation() * VEC3_RIGHT; }
    glm::vec3 Transform::GetUp() const { return GetRotation() * VEC3_UP; }
    glm::vec3 Transform::GetForward() const { return GetRotation() * VEC3_FORWARD; }

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
