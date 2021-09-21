#include "Window.h"

namespace NDR
{
    Window::Window(const WindowProps& properties)
         : _window(nullptr)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        _window = glfwCreateWindow(800, 600, "Rendering Test", nullptr, nullptr);
        if(_window == nullptr)
        {
            printf("GLFW Window did not initalize!");
            glfwTerminate();
        }
        SetFocus();
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
    }

    void Window::SetFocus() const { glfwMakeContextCurrent(_window); }
    void Window::SetVSync(bool vSync) { glfwSwapInterval(vSync); }
    bool Window::Active() const { return _active; }
    void Window::Close() { _active = false; }

    void Window::SwapBuffers() const { glfwSwapBuffers(_window); }
}
