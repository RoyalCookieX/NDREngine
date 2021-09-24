#pragma once
#include <memory>

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
        std::unique_ptr<Window> _window;
        std::unique_ptr<Renderer> _renderer;
    };
}
