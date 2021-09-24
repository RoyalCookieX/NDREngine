#include "ndrpch.h"
#include "Window.h"

#include <glad/glad.h>

namespace NDR
{
    Window::Window(const WindowProps& properties)
        : _properties(properties)
    {
        // initalize glfw
        if(_windowCount == 0)
        {
            if(!glfwInit())
            {
                printf("GLFW did not initalize!\n");
                glfwTerminate();
                return;
            }
        }
        _windowCount++;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        _window = glfwCreateWindow(properties.width, properties.height, properties.name.c_str(), nullptr, nullptr);
        if(_window == nullptr)
        {
            printf("GLFW Window did not initalize!");
            glfwTerminate();
        }
        SetContextCurrent();
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            printf("GLAD did not initalize!\n");
            glfwTerminate();
            return;
        }
        SetVSync(properties.isVsync);

        glfwSetWindowUserPointer(_window, this);
        glfwSetWindowCloseCallback(_window, [](GLFWwindow* w)
        {
            ((Window*)glfwGetWindowUserPointer(w))->Close();
        });

        glfwSetKeyCallback(_window, [](GLFWwindow* w, int key, int scancode, int action, int mods)
        {
            if(key == GLFW_KEY_ESCAPE) ((Window*)glfwGetWindowUserPointer(w))->Close();
        });
    }

    Window::~Window()
    {
        glfwDestroyWindow(_window);
        _windowCount--;
        if(_windowCount == 0)
        {
            glfwTerminate();
        }
    }

    void Window::SetContextCurrent() const { glfwMakeContextCurrent(_window); }
    void Window::SetVSync(bool vSync) { glfwSwapInterval(vSync); }
    bool Window::Active() const { return _active; }
    void Window::Close() { _active = false; }

    void Window::SwapBuffers() const { glfwSwapBuffers(_window); }
    void Window::PollEvents() const { glfwPollEvents(); }

    uint32_t Window::GetWidth() const { return _properties.width; }
    uint32_t Window::GetHeight() const { return _properties.height; }
}
