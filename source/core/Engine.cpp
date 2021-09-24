#include "ndrpch.h"
#include "Engine.h"

namespace NDR
{
    Engine::Engine()
    {
        _window = std::make_unique<Window>(WindowProps(800, 600, "NDREngine", true));
        _renderer = std::make_unique<Renderer>();
        _renderer->SetBlendMode(BlendMode::TRANSPARENT);
    }

    Engine::~Engine()
    {
        _renderer.release();
        _window.release();
    }

    void Engine::Run() const
    {
        while (_window->Active())
        {
            _renderer->Clear();
            _renderer->DrawBackground(0.1f, 0.3f, 0.6f, 1.0f);
            _window->SwapBuffers();
            
            _window->PollEvents();
        }
    }
}
