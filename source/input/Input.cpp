#include "ndrpch.h"
#include "Input.h"

#include "core/Window.h"

namespace NDR
{
    NDRButtonAction Input::GetKey(NDRKey keycode)
    {
        GLFWwindow* window = glfwGetCurrentContext();
        return glfwGetKey(window, keycode);
    }

    NDRButtonAction Input::GetMouseButton(NDRMouseButton button)
    {
        GLFWwindow* window = glfwGetCurrentContext();
        return glfwGetMouseButton(window, button);
    }
}
