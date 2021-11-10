#include "ndrpch.h"
#include "Window_win32.h"

#include "core/Log.h"

namespace NDR
{
    Window* Window::Create(const WindowProps& props)
    {
        return new Window_win32(props);
    }
    
    Window_win32::Window_win32(const WindowProps& properties):
        _properties(properties)
    {
        // initalize glfw
        if(_windowCount == 0)
        {
            if(!glfwInit())
            {
                NDR_LOGFATAL("[GLFW]: GLFW did not initalize!");
                glfwTerminate();
                return;
            }
        }
        _windowCount++;
        
#ifdef NDR_GRAPHICSAPI_OPENGL
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef NDR_DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
#endif
        _window = glfwCreateWindow(properties.width, properties.height, properties.name.c_str(), nullptr, nullptr);
        if(_window == nullptr)
        {
            NDR_LOGFATAL("[GLFW]: GLFW Window did not initalize!");
            glfwTerminate();
        }
        Window_win32::SetContextCurrent();
        Window_win32::SetVSync(properties.isVsync);

        glfwSetWindowUserPointer(_window, this);
        glfwSetWindowCloseCallback(_window, [](GLFWwindow* w)
        {
            ((Window*)glfwGetWindowUserPointer(w))->Close();
        });
    }

    Window_win32::~Window_win32()
    {
        glfwDestroyWindow(_window);
        _windowCount--;
        if(_windowCount == 0)
        {
            glfwTerminate();
        }
    }

    Window_win32::operator struct GLFWwindow*() const { return _window; }

    void Window_win32::AddCallback(EventFunc callback) { _callbacks.push_back(callback); }
    void Window_win32::SetContextCurrent() const { glfwMakeContextCurrent(_window); }
    void Window_win32::SetVSync(bool vSync) { glfwSwapInterval(vSync); }
    bool Window_win32::Active() const { return _active; }
    void Window_win32::Close() { _active = false; }

    void Window_win32::SwapBuffers() const { glfwSwapBuffers(_window); }
    void Window_win32::PollEvents() const { glfwPollEvents(); }

    uint32_t Window_win32::GetWidth() const { return _properties.width; }
    uint32_t Window_win32::GetHeight() const { return _properties.height; }

    void Window_win32::Dispatch(Event* event) const { for (auto callback : _callbacks) callback(event); }
}

