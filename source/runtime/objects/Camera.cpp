#include "ndrpch.h"
#include "Camera.h"

#include "input/Input.h"

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
    glm::mat4 Camera::GetViewMatrix() const
    {
        const glm::vec3 position = GetTransform().GetPosition();
        const glm::vec3 forward = position + GetTransform().GetForward();
        const glm::vec3 up(0.0f, 1.0f, 0.0f);
        return glm::lookAt(position, forward, up);
    }
    glm::mat4 Camera::GetViewProjMatrix() const { return _projMatrix * GetViewMatrix(); }

    void Camera::Tick()
    {
        if(Input::GetKey(NDR_KEY_W)) GetTransform().Translate(glm::vec3( 0.00f, 0.00f, 0.05f) * GetTransform().GetRotation());
        if(Input::GetKey(NDR_KEY_A)) GetTransform().Translate(glm::vec3( 0.05f, 0.00f, 0.00f) * GetTransform().GetRotation());
        if(Input::GetKey(NDR_KEY_S)) GetTransform().Translate(glm::vec3( 0.00f, 0.00f,-0.05f) * GetTransform().GetRotation());
        if(Input::GetKey(NDR_KEY_D)) GetTransform().Translate(glm::vec3(-0.05f, 0.00f, 0.00f) * GetTransform().GetRotation());
        if(Input::GetKey(NDR_KEY_Q)) GetTransform().Translate(glm::vec3( 0.00f,-0.05f, 0.00f) * GetTransform().GetRotation());
        if(Input::GetKey(NDR_KEY_E)) GetTransform().Translate(glm::vec3( 0.00f, 0.05f, 0.00f) * GetTransform().GetRotation());

        //TODO: Make camera rotation work
        // if(Input::GetKey(NDR_KEY_I))
        //     GetTransform().Rotate({ 0.05f, 0.00f, 0.00f});
        // if(Input::GetKey(NDR_KEY_J))
        //     GetTransform().Rotate({ 0.00f,-0.05f, 0.00f});
        // if(Input::GetKey(NDR_KEY_K))
        //     GetTransform().Rotate({-0.05f, 0.00f, 0.00f});
        // if(Input::GetKey(NDR_KEY_L))
        //     GetTransform().Rotate({ 0.00f, 0.05f, 0.00f});
    }

    void Camera::SetProjection(const glm::mat4& projMatrix) { _projMatrix = projMatrix; }
}
