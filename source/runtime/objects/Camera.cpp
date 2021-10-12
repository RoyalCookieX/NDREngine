#include "ndrpch.h"
#include "Camera.h"

#include "input/Input.h"

namespace NDR
{
    Camera::Camera():
        Camera(glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f))
    {
    }

    Camera::Camera(const glm::mat4& projMatrix):
        Camera(projMatrix, {0.0f, 0.0f, 0.0f}, {180.0f, 0.0f})
    {
        
    }

    Camera::Camera(const glm::mat4& projMatrix, const glm::vec3& position, const glm::vec2& yawPitch):
        _projMatrix(projMatrix),
        _position(position),
        _yawPitch(yawPitch)
    {
    }

    glm::vec2 Camera::GetYawPitch() const { return _yawPitch; }
    void Camera::SetYawPitch(const glm::vec2& yawPitch)
    {
        const float newYaw = yawPitch.x <= 0 ? 360.0f - yawPitch.x : yawPitch.x >= 360.0f ? yawPitch.x - 360.0f : yawPitch.x;
        const float newPitch = glm::clamp(yawPitch.y, -89.0f, 89.0f);
        _yawPitch = glm::vec2(newYaw, newPitch);
    }
    glm::vec2 Camera::AddYawPitch(const glm::vec2& yawPitch)
    {
        SetYawPitch(_yawPitch + yawPitch);
        return _yawPitch;
    }

    glm::vec3 Camera::GetRightAxis() const
    {
        const glm::vec3 rightAxis = glm::cross(GetForwardAxis(), GetUpAxis());
        return glm::normalize(rightAxis);
    }
    glm::vec3 Camera::GetUpAxis() const { return glm::vec3(0.0f, 1.0f, 0.0f); }
    glm::vec3 Camera::GetForwardAxis() const
    {
        const glm::vec2 yawPitchRad = glm::radians(_yawPitch);
        const float yaw = yawPitchRad.x;
        const float pitch = yawPitchRad.y;
        const glm::vec3 forward(glm::sin(yaw) * glm::cos(pitch), glm::sin(pitch), glm::cos(yaw) * glm::cos(pitch));
        return glm::normalize(forward);
    }

    glm::mat4 Camera::GetProjMatrix() const { return _projMatrix; }
    glm::mat4 Camera::GetViewMatrix() const
    {        
        return glm::lookAt(_position, _position + GetForwardAxis(), GetUpAxis());
    }
    glm::mat4 Camera::GetViewProjMatrix() const { return _projMatrix * GetViewMatrix(); }

    void Camera::Tick()
    {
        if(Input::GetKey(NDR_KEY_W))
            _position += GetForwardAxis() * moveSpeed;
        if(Input::GetKey(NDR_KEY_A))
            _position += -GetRightAxis() * moveSpeed;
        if(Input::GetKey(NDR_KEY_S))
            _position += -GetForwardAxis() * moveSpeed;
        if(Input::GetKey(NDR_KEY_D))
            _position += GetRightAxis() * moveSpeed;
        if(Input::GetKey(NDR_KEY_Q))
            _position += -GetUpAxis() * moveSpeed;
        if(Input::GetKey(NDR_KEY_E))
            _position += GetUpAxis() * moveSpeed;

        if(Input::GetKey(NDR_KEY_I))
            AddYawPitch({0.0f, rotationSpeed});
        if(Input::GetKey(NDR_KEY_J))
            AddYawPitch({rotationSpeed, 0.0f});
        if(Input::GetKey(NDR_KEY_K))
            AddYawPitch({0.0f, -rotationSpeed});
        if(Input::GetKey(NDR_KEY_L))
            AddYawPitch({-rotationSpeed, 0.0f});
    }

    void Camera::SetProjection(const glm::mat4& projMatrix) { _projMatrix = projMatrix; }
}
