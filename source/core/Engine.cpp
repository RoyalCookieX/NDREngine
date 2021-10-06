#include "ndrpch.h"
#include "Engine.h"
#include "input/Input.h"

namespace NDR
{
    void Engine::PreInitialize()
    {
        _window = Window::Create({800, 600, "NDREngine", true});
        _renderer = new Renderer();
    }

    void Engine::Run()
    {
        PreInitialize();
        Initialize();
        
        while(_window->Active())
        {
            _window->PollEvents();
            if(Input::GetKey(NDR_KEY_ESCAPE)) _window->Close();

            Tick();

            _renderer->Clear();
            OnDraw();
            _window->SwapBuffers();
        }
        
        Shutdown();
        PostShutdown();
    }

    void Engine::PostShutdown()
    {
        delete _window;
        delete _renderer;
    }
}
