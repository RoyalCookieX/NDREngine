#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace NDR
{
    class Object
    {
    public:
        Object(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale);
        virtual ~Object();

        glm::mat4 GetTransformMatrix() const;
        glm::vec3 GetPosition() const;
        glm::quat GetRotation() const;
        glm::vec3 GetScale() const;

        void SetPosition(const glm::vec3& position);
        void SetPosition(float x, float y, float z);
        
        void SetRotation(const glm::quat& rotation);
        void SetRotation(const glm::vec3& euler);
        void SetRotation(float pitch, float yaw, float roll);
        void SetRotation(float angle, const glm::vec3& axis);
        
        void SetScale(const glm::vec3& scale);
    private:
        glm::vec3 _position;
        glm::quat _rotation;
        glm::vec3 _scale;
    };
}
