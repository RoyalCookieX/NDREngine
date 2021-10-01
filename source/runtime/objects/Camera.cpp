#include "ndrpch.h"
#include "Camera.h"

namespace NDR
{
    Camera::Camera():
        _projMatrix(glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f))
    {
    }

    Camera::Camera(const glm::mat4& projMatrix):
        Object(),
        _projMatrix(projMatrix)
    {       
    }

    Camera::Camera(const Transform& transform, const glm::mat4& projMatrix):
        Object(transform),
        _projMatrix(projMatrix)
    {
    }

    Camera::Camera(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale, const glm::mat4& projMatrix):
        Object(position, rotation, scale),
        _projMatrix(projMatrix)
    {
    }

    glm::mat4 Camera::GetProjMatrix() const { return _projMatrix; }
    glm::mat4 Camera::GetViewMatrix() const { return glm::inverse(GetTransformMatrix()); }
    glm::mat4 Camera::GetViewProjMatrix() const { return GetViewMatrix() * _projMatrix; }
    void Camera::SetProjection(const glm::mat4& projMatrix) { _projMatrix = projMatrix; }
}
