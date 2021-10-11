#pragma once

#include "core/Window.h"
#include "graphics/Renderer.h"

namespace NDR 
{
    class Engine
    {
    public:
        virtual ~Engine() = default;

        void Run();

        virtual void Initialize() = 0;
        virtual void Tick() = 0;
        virtual void Shutdown() = 0;

        Window* GetWindow() const { return _window; }
        Renderer* GetRenderer() const { return _renderer; }
    
    private:
        void PreInitialize();
        void PostShutdown();
    
        Window* _window = nullptr;
        Renderer* _renderer = nullptr;
    };
}
