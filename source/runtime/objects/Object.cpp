#include "Object.h"

namespace NDR
{
    Transform::Transform()
        : position(glm::vec3(0.0f)),
          rotation(glm::identity<glm::quat>()),
          scale(glm::vec3(1.0f))
    {
    }

    Transform::Transform(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale)
        : position(position),
          rotation(rotation),
          scale(scale)
    {
    }

    glm::mat4 Transform::GetMatrix() const
    {
        const glm::mat4 positionMatrix = glm::translate(glm::mat4(1.0f), position);
        const glm::mat4 rotationMatrix = glm::toMat4(rotation);
        const glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
        return positionMatrix * rotationMatrix * scaleMatrix;
    }

    Object::Object()
    {
    }

    Object::Object(const Transform& transform)
        : _transform(transform)
    {
    }

    Object::Object(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale)
        : _transform(Transform(position, rotation, scale))
    {
    }

    Object::~Object()
    {
    }

    glm::mat4 Object::GetTransformMatrix() const { return _transform.GetMatrix(); }
    
    glm::vec3 Object::GetPosition() const { return _transform.position; }
    glm::quat Object::GetRotation() const { return _transform.rotation; }
    glm::vec3 Object::GetScale() const { return _transform.scale; }

    void Object::SetPosition(const glm::vec3& position) { _transform.position = position; }
    void Object::SetPosition(float x, float y, float z) { SetPosition(glm::vec3(x, y, z)); }
    void Object::Translate(const glm::vec3& position) { _transform.position += position; }
    void Object::Translate(float x, float y, float z) { Translate(glm::vec3(x, y, z)); }

    void Object::SetRotation(const glm::quat& rotation) { _transform.rotation = rotation; }
    void Object::SetRotation(const glm::vec3& euler) { _transform.rotation = glm::quat(euler); }
    void Object::SetRotation(float pitch, float yaw, float roll) { SetRotation(glm::vec3(pitch, yaw, roll)); }
    void Object::SetRotation(float angle, const glm::vec3& axis) { _transform.rotation = glm::quat(angle, axis); }
    void Object::Rotate(const glm::quat& rotation) { _transform.rotation += rotation; }
    void Object::Rotate(const glm::vec3& euler) { _transform.rotation += glm::quat(euler); }
    void Object::Rotate(float pitch, float yaw, float roll) { _transform.rotation += glm::quat(glm::vec3(pitch, yaw, roll)); }
    void Object::Rotate(float angle, const glm::vec3& axis) { _transform.rotation = glm::rotate(_transform.rotation, angle, axis); }

    void Object::SetScale(const glm::vec3& scale) { _transform.scale = scale; }
}
