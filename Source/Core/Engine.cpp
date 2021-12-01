#include "ndrpch.h"
#include "Engine.h"

#include "Window.h"
#include "graphics/Renderer.h"
#include "Core/Input.h"
#include "utility/Time.h"
#include "Events/EventDispatcher.h"

namespace NDR
{    
    void Engine::PreInitialize()
    {
        _dispatcher = CreateShared<EventDispatcher>();
        _window = Window::Create({{100, 100}, {800, 600}, "NDREngine", false}, _dispatcher);
        Input::Initialize(_dispatcher);
        Renderer::Initialize();
    }

    void Engine::Run()
    {
        PreInitialize();
        Initialize();
        
        while(_window->IsActive())
        {
            _window->PollEvents();
            if(Input::OnKeyPressed(Keycode::ESCAPE))
                _window->Close();

            Renderer::Clear();
            Tick(Time::GetDeltaTime());
            _window->SwapBuffers();
            Input::Tick();
        }
        
        Shutdown();
        PostShutdown();
    }

    void Engine::PostShutdown()
    {
        Renderer::Shutdown();
    }
}
