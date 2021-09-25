#include "ndrpch.h"
#include "Input.h"

#include "core/Window.h"

namespace NDR
{
    Input* Input::_instance = new Input();

    NDRButtonAction Input::GetKey_Impl(NDRKey keycode) const
    {
        GLFWwindow* window = glfwGetCurrentContext();
        return glfwGetKey(window, keycode);
    }

    NDRButtonAction Input::GetMouseButton_Impl(NDRMouseButton button) const
    {
        GLFWwindow* window = glfwGetCurrentContext();
        return glfwGetMouseButton(window, button);
    }
}
