#pragma once

#include "Window.h"
#include "graphics/Renderer.h"

namespace NDR 
{
    class Engine
    {
    public:
        Engine();
        ~Engine();
        
        void Run() const;
    private:
        Window* _window;
        Renderer* _renderer;
    };
}
