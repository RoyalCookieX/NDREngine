#pragma once

#include "Window.h"
#include "graphics/Framebuffer.h"
#include "graphics/Renderer.h"
#include "graphics/Texture.h"
#include "runtime/objects/Camera.h"

namespace NDR 
{
    class Engine
    {
    public:
        Engine();
        ~Engine();
        
        void Run();
    private:
        Window* _window;
        Renderer* _renderer;

        Camera _cam;
        Texture _texture;
        VertexArray _vertexArray;
        IndexBuffer _indexBuffer;
        Shader _shader;
    };
}
