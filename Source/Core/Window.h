#pragma once
#include "Defines.h"

namespace NDR
{
    struct Event;
    
    struct WindowProps
    {
    public:
        UInt32 width;
        UInt32 height;
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
        virtual ~Window() = default;

        virtual void AddCallback(EventFunc callback) = 0;
        virtual void SetContextCurrent() const = 0;
        virtual void SetVSync(bool vSync) = 0;
        virtual bool Active() const = 0;
        virtual void Close() = 0;

        virtual void SwapBuffers() const = 0;
        virtual void PollEvents() const = 0;

        virtual UInt32 GetWidth() const = 0;
        virtual UInt32 GetHeight() const = 0;

        static UPointer<Window> Create(const WindowProps& props);
    protected:
        virtual void Dispatch(Event* event) const = 0;
    };
}
