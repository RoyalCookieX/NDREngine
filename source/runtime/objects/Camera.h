#pragma once
#include "Object.h"

namespace NDR
{
    class Camera : public Object
    {
    public:
        float moveSpeed = 0.05f, rotationSpeed = 0.05f;
        
        Camera();
        Camera(const glm::mat4& projMatrix);
        Camera(const Transform& transform, const glm::mat4& projMatrix);
        Camera(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale, const glm::mat4& projMatrix);

        glm::mat4 GetProjMatrix() const;
        glm::mat4 GetViewMatrix() const;
        glm::mat4 GetViewProjMatrix() const;

        virtual void Tick() override;

        void SetProjection(const glm::mat4& projMatrix);
    private:
        glm::mat4 _projMatrix;
    };
}
