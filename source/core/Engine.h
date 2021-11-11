#pragma once

#include "core/Window.h"
#include "graphics/Renderer.h"
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
        UniquePtr<Renderer>& GetRenderer() { return _renderer; }
        const UniquePtr<Renderer>& GetRenderer() const { return _renderer; }
    
    private:
        void PreInitialize();
        void PostShutdown();
    
        UniquePtr<Window> _window;
        UniquePtr<Renderer> _renderer;
    };
}
