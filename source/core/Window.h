#pragma once
#include "input/Event.h"

namespace NDR
{
    struct WindowProps
    {
    public:
        int width;
        int height;
        std::string name;
        bool isVsync;

        WindowProps(int width, int height, const std::string& name, bool isVsync)
            : width(width),
              height(height),
              name(name),
              isVsync(isVsync)
        {
        }
    };
    
    typedef void (*EventFunc)(Event*);
    
    class Window
    {
    public:
        Window(const WindowProps& properties);
        ~Window();

        explicit operator GLFWwindow*() const;

        void AddCallback(EventFunc callback);
        void SetContextCurrent() const;
        void SetVSync(bool vSync);
        bool Active() const;
        void Close();

        void SwapBuffers() const;
        void PollEvents() const;

        uint32_t GetWidth() const;
        uint32_t GetHeight() const;
    private:
        void Dispatch(Event* event) const;
        
        GLFWwindow* _window;
        WindowProps _properties;
        bool _active;
        std::vector<EventFunc> _callbacks;
        
        inline static uint32_t _windowCount = 0;
    };
}
