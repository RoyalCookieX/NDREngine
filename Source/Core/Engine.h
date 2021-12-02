#pragma once
#include "Defines.h"

namespace NDR
{
    class Window;
    class EventDispatcher;
    
    class Engine
    {
    public:
        virtual ~Engine() = default;
        
        void Run();

        virtual void Initialize() = 0;
        virtual void Tick() = 0;
        virtual void Shutdown() = 0;

        UPointer<Window>& GetWindow() { return _window; }
        const UPointer<Window>& GetWindow() const { return _window; }
    
    private:
        void PreInitialize();
        void PostShutdown();
    
        UPointer<Window> _window;
        SPointer<EventDispatcher> _dispatcher;
    };
}
