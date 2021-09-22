#include "Object.h"

namespace NDR
{
    Object::Object(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale)
        : _position(position),
          _rotation(rotation),
          _scale(scale)
    {
    }

    Object::~Object()
    {
    }

    glm::mat4 Object::GetTransformMatrix() const
    {
        const glm::mat4 positionMatrix = glm::translate(glm::mat4(1.0f), _position);
        const glm::mat4 rotationMatrix = glm::toMat4(_rotation);
        const glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), _scale);
        return positionMatrix * rotationMatrix * scaleMatrix;
    }
    
    glm::vec3 Object::GetPosition() const { return _position; }
    glm::quat Object::GetRotation() const { return _rotation; }
    glm::vec3 Object::GetScale() const { return _scale; }

    void Object::SetPosition(const glm::vec3& position) { _position = position; }
    void Object::SetPosition(float x, float y, float z) { SetPosition(glm::vec3(x, y, z)); }
    
    void Object::SetRotation(const glm::quat& rotation) { _rotation = rotation; }
    void Object::SetRotation(const glm::vec3& euler) { _rotation = glm::quat(euler); }
    void Object::SetRotation(float pitch, float yaw, float roll) { SetRotation(glm::vec3(pitch, yaw, roll)); }
    void Object::SetRotation(float angle, const glm::vec3& axis) { _rotation = glm::quat(angle, axis); }

    void Object::SetScale(const glm::vec3& scale) { _scale = scale; }
}
