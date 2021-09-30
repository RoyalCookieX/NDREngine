#pragma once

#include "Window.h"
#include "graphics/Framebuffer.h"
#include "graphics/Renderer.h"
#include "graphics/Texture.h"

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
        
        Mesh _quadMesh;
        Texture _quadTexture;
        Shader _quadShader;
        Framebuffer _framebuffer;
    };
}
