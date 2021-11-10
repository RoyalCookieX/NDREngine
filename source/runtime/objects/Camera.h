#pragma once
#include "Object.h"

namespace NDR
{
    class Camera
    {
    public:
        float moveSpeed = 1.0f, rotationSpeed = 90.0f;
        
        Camera();
        Camera(const glm::mat4& projMatrix);
        Camera(const glm::mat4& projMatrix, const glm::vec3& position, const glm::vec2& yawPitch);

        glm::vec2 GetYawPitch() const;
        void SetYawPitch(const glm::vec2& yawPitch);
        glm::vec2 AddYawPitch(const glm::vec2& yawPitch);
        
        glm::vec3 GetRightAxis() const;
        glm::vec3 GetUpAxis() const;
        glm::vec3 GetForwardAxis() const;
        
        glm::mat4 GetProjMatrix() const;
        glm::mat4 GetViewMatrix() const;
        glm::mat4 GetViewProjMatrix() const;

        void Tick(float deltaTime);

        void SetProjection(const glm::mat4& projMatrix);
    private:
        glm::mat4 _projMatrix;
        glm::vec3 _position;
        glm::vec2 _yawPitch;
    };
}
