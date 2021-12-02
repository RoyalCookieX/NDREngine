#pragma once
#include "Defines.h"

namespace NDR
{
    struct Event;
    class EventDispatcher;
    
    struct WindowProperties
    {
    public:
        UInt32Pair position;
        UInt32Pair size;
        std::string name;
        bool isVsync;

        WindowProperties(UInt32Pair position, UInt32Pair size, const std::string& name, bool isVsync):
            position(position),
            size(size),
            name(name),
            isVsync(isVsync)
        {
        }
    };
    
    class Window
    {
    public:
        virtual ~Window() = default;

        virtual UInt32Pair GetSize() const = 0;
        virtual const SPointer<EventDispatcher>& GetDispatcher() = 0;
        virtual bool IsActive() const = 0;

        virtual void SetContextCurrent() const = 0;
        virtual void SetVSync(bool vSync) = 0;
        virtual void Close() = 0;
        virtual void SwapBuffers() const = 0;
        virtual void PollEvents() const = 0;
        
        static UPointer<Window> Create(const WindowProperties& properties, const SPointer<EventDispatcher>& dispatcher);
    private:
        virtual void OnEvent(const SPointer<Event>& e) = 0;
    };
}
