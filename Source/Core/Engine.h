#pragma once

#include "core/Window.h"
#include "utility/Memory.h"

namespace NDR
{
    class Engine
    {
    public:
        virtual ~Engine() = default;

        void Run();

        virtual void Initialize() = 0;
        virtual void Tick(float deltaTime) = 0;
        virtual void Shutdown() = 0;

        UniquePtr<Window>& GetWindow() { return _window; }
        const UniquePtr<Window>& GetWindow() const { return _window; }
    
    private:
        void PreInitialize();
        void PostShutdown();
    
        UniquePtr<Window> _window;
    };
}
