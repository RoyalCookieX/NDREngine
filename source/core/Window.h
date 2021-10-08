#pragma once
#include "input/Event.h"

namespace NDR
{
    struct WindowProps
    {
    public:
        uint32_t width;
        uint32_t height;
        std::string name;
        bool isVsync;

        WindowProps(int width, int height, const std::string& name, bool isVsync):
            width(width),
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
        virtual ~Window() { }

        virtual void AddCallback(EventFunc callback) = 0;
        virtual void SetContextCurrent() const = 0;
        virtual void SetVSync(bool vSync) = 0;
        virtual bool Active() const = 0;
        virtual void Close() = 0;

        virtual void SwapBuffers() const = 0;
        virtual void PollEvents() const = 0;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        static Window* Create(const WindowProps& props);
    protected:
        virtual void Dispatch(Event* event) const = 0;
    };
}
