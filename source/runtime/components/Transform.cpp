#include "ndrpch.h"
#include "Transform.h"

namespace NDR
{
    Transform::Transform(const glm::mat4& matrix): _matrix(matrix) { }   
    Transform::Transform(): Transform(glm::vec3(0.0f), glm::quat(), glm::vec3(1.0f)) { }
    Transform::Transform(const glm::vec3& position): Transform(position, glm::quat(), glm::vec3(1.0f)) { }
    Transform::Transform(const glm::vec3& position, const glm::quat& rotation): Transform(position, rotation, glm::vec3(1.0f)) { }
    Transform::Transform(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale)
    {
        glm::vec3 euler = glm::radians(glm::eulerAngles(rotation));
        _matrix = glm::mat4(1.0f);
        _matrix = glm::translate(_matrix, position);
        _matrix = glm::rotate(_matrix, euler.x, glm::vec3(1.0f, 0.0, 0.0f));
        _matrix = glm::rotate(_matrix, euler.y, glm::vec3(0.0f, 1.0, 0.0f));
        _matrix = glm::rotate(_matrix, euler.z, glm::vec3(0.0f, 0.0, 1.0f));
        _matrix = glm::scale(_matrix, scale);
        
    }
    
    const glm::mat4& Transform::GetMatrix() const { return _matrix; }
    //TODO: make isLocal return local version
    glm::vec3 Transform::GetPosition(const bool isLocal) const
    {
        auto[p, r, s] = Decompose();
        return p;
    }
    glm::quat Transform::GetRotation(const bool isLocal) const 
    {
        auto[p, r, s] = Decompose();
        return r;
    }
    glm::vec3 Transform::GetScale() const
    {
        auto[p, r, s] = Decompose();
        return s;
    }

    void Transform::SetPosition(const glm::vec3& newPosition, const bool isLocal)
    {
        auto[pos, rot, scale] = Decompose();
        ConstructMatrix(newPosition, rot, scale);
    }
    Transform& Transform::Translate(const glm::vec3& translation, const bool isLocal)
    {
        auto[pos, rot, scale] = Decompose();
        ConstructMatrix(pos + translation, rot, scale);
        return *this;
    }

    void Transform::SetRotation(const glm::quat& newRotation, const bool isLocal)
    {
        ConstructMatrix(GetPosition(), newRotation, GetScale());
    }
    void Transform::SetRotation(const glm::vec3& newEuler, const bool isLocal)
    {
        SetRotation(glm::quat(glm::radians(newEuler)), isLocal);
    }
    void Transform::SetRotation(const float degrees, const glm::vec3& axis, const bool isLocal)
    {
        SetRotation(glm::angleAxis(glm::radians(degrees), axis));
    }
    Transform& Transform::Rotate(const glm::quat& rotation, const bool isLocal)
    {
        if(isLocal)
        {
            auto[pos, rot, scale] = Decompose();
            ConstructMatrix(pos, rot * rotation, scale);           
        }
        else
        {
            const glm::mat4 rot = glm::toMat4(rotation);
            _matrix = rot * _matrix;
        }
        return *this;
    }
    Transform& Transform::Rotate(const glm::vec3& euler, const bool isLocal)
    {
        return Rotate(glm::quat(glm::radians(euler)), isLocal);
    }
    Transform& Transform::Rotate(const float degrees, const glm::vec3& axis, const bool isLocal)
    {
        return Rotate(glm::angleAxis(glm::radians(degrees), axis), isLocal);
    }

    void Transform::SetScale(const glm::vec3& newScale)
    {
        auto[pos, rot, size] = Decompose();
        ConstructMatrix(pos, rot, newScale);
    }
    Transform& Transform::Scale(const glm::vec3& scalar)
    {
        auto[pos, rot, size] = Decompose();
        ConstructMatrix(pos, rot, size + scalar);
        return *this;
    }

    glm::vec3 Transform::GetRight()     const { return glm::normalize(glm::rotate(GetRotation(), glm::vec3(1.0f, 0.0f, 0.0f))); }
    glm::vec3 Transform::GetUp()        const { return glm::normalize(glm::rotate(GetRotation(), glm::vec3(0.0f, 1.0f, 0.0f))); }
    glm::vec3 Transform::GetForward()   const { return glm::normalize(glm::rotate(GetRotation(), glm::vec3(0.0f, 0.0f, 1.0f))); }

    std::tuple<glm::vec3, glm::quat, glm::vec3> Transform::Decompose() const
    {
        glm::vec3 translation;
        glm::quat rotation;
        glm::vec3 scale;
        glm::vec3 skew;
        glm::vec4 perspective;
        glm::decompose(_matrix, scale, rotation, translation, skew, perspective);
        return std::make_tuple(translation, rotation, scale);
    }

    void Transform::ConstructMatrix(const glm::vec3& pos, const glm::quat& rot, const glm::vec3& scale)
    {
        _matrix = glm::translate(glm::mat4(1.0f), pos)
                * glm::toMat4(rot)
                * glm::scale(glm::mat4(1.0f), scale);
    }
}
