#include "ndrpch.h"
#include "Window_Win32.h"

#include "Core/Log.h"
#include "Events/EventDispatcher.h"

#define NDR_CAST_WIN32WINDOW(GLFWwindowPtr, name) Win32Window* name = static_cast<Win32Window*>(glfwGetWindowUserPointer(GLFWwindowPtr))

namespace NDR
{
    static Int32 sWindowCount;
    
    Win32Window::Win32Window(const WindowProps& properties, const SPointer<EventDispatcher>& dispatcher):
        _properties(properties),
        _dispatcher(dispatcher)
    {
        _dispatcher->AddCallback(EventCategory::WINDOW, NDR_BIND_NONSTATIC_EVENTFUNC(Win32Window::OnEvent));
        
        if(sWindowCount == 0)
        {
            // initalize glfw
            if(!glfwInit())
            {
                NDR_LOGFATAL("[GLFW]: GLFW did not initalize!");
                glfwTerminate();
                return;
            }
        }
        sWindowCount++;
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef NDR_DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
        _window = glfwCreateWindow(properties.size.width, properties.size.height, properties.name.c_str(), nullptr, nullptr);
        if(_window == nullptr)
        {
            NDR_LOGFATAL("[GLFW]: Failed to initialize Window!");
            glfwTerminate();
        }
        Win32Window::SetContextCurrent();
        Win32Window::SetVSync(properties.isVsync);
        
        glfwSetWindowUserPointer(_window, this);
        glfwSetWindowCloseCallback(_window, [](GLFWwindow* w)
        {
            NDR_CAST_WIN32WINDOW(w, win32Window);
            win32Window->GetDispatcher()->Brodcast<WindowCloseEvent>();
        });
        glfwSetWindowPosCallback(_window, [](GLFWwindow* w, Int32 x, Int32 y)
        {
            NDR_CAST_WIN32WINDOW(w, win32Window);
            UInt32Pair newPosition = { (UInt32)x, (UInt32)y };
            win32Window->GetDispatcher()->Brodcast<WindowMoveEvent>(newPosition);
        });
        glfwSetFramebufferSizeCallback(_window, [](GLFWwindow* w, Int32 width, Int32 height)
        {
            NDR_CAST_WIN32WINDOW(w, win32Window);
            UInt32Pair newSize = { (UInt32)width, (UInt32)height };
            win32Window->GetDispatcher()->Brodcast<WindowResizeEvent>(newSize);
        });
        glfwSetKeyCallback(_window, [](GLFWwindow* w, Int32 key, Int32 scancode, Int32 action, Int32 mods)
        {
            NDR_CAST_WIN32WINDOW(w, win32Window);
            win32Window->GetDispatcher()->Brodcast<KeyPressEvent>(FromNativeKeycode(key), action);
        });
        glfwSetMouseButtonCallback(_window, [](GLFWwindow* w, Int32 button, Int32 pressed, Int32 mods)
        {
            NDR_CAST_WIN32WINDOW(w, win32Window);
            win32Window->GetDispatcher()->Brodcast<MousePressEvent>(FromNativeMouseButton(button), pressed);
        });
        glfwSetCursorPosCallback(_window, [](GLFWwindow* w, double xPosition, double yPosition)
        {
            NDR_CAST_WIN32WINDOW(w, win32Window);
            UInt32 xPos = (UInt32)std::trunc(std::round(xPosition));
            UInt32 yPos = (UInt32)std::trunc(std::round(yPosition));
            win32Window->GetDispatcher()->Brodcast<MouseMoveEvent>(UInt32Pair(xPos, yPos));
        });
        glfwSetScrollCallback(_window, [](GLFWwindow* w, double xOffset, double yOffset)
        {
            NDR_CAST_WIN32WINDOW(w, win32Window);
            win32Window->GetDispatcher()->Brodcast<MouseScrollEvent>((Int32)std::trunc(std::round(yOffset)));
        });
    }

    Win32Window::~Win32Window()
    {
        glfwDestroyWindow(_window);
        sWindowCount--;
        if(sWindowCount == 0)
            glfwTerminate();
    }
    
    void Win32Window::SetContextCurrent() const { glfwMakeContextCurrent(_window); }
    void Win32Window::SetVSync(bool vSync) { glfwSwapInterval(vSync); }
    void Win32Window::Close() { _active = false; }
    void Win32Window::SwapBuffers() const { glfwSwapBuffers(_window); }
    void Win32Window::PollEvents() const { glfwPollEvents(); }

    void Win32Window::OnEvent(const SPointer<Event>& e)
    {
        switch (e->GetCategory())
        {
            case EventCategory::WINDOWCLOSE:
            {
                Close();
                e->Consume();
                break;
            }
            case EventCategory::WINDOWMOVE:
            {
                NDR_CAST_EVENT(e, WindowMoveEvent, windowMoveEvent);
                _properties.position = windowMoveEvent->GetPosition();
                e->Consume();
                break;
            }
            case EventCategory::WINDOWRESIZE:
            {
                NDR_CAST_EVENT(e, WindowResizeEvent, windowResizeEvent);
                _properties.size = windowResizeEvent->GetSize();
                glViewport(0, 0, _properties.size.x, _properties.size.y);
                e->Consume();
                break;
            }
            default: break;
        }
    }
}