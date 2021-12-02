#include "ndrpch.h"
#include "Engine.h"

#include "Config.h"
#include "Window.h"
#include "Graphics/Renderer.h"
#include "Core/Input.h"
#include "Events/EventDispatcher.h"

namespace NDR
{    
    void Engine::PreInitialize()
    {
        _dispatcher = CreateShared<EventDispatcher>();
        WindowProperties properties
        (
            {
                (UInt32)Config::GetInt(NDR_APP_CONFIG_PATH, "WindowProperties", "XPosition"),
                (UInt32)Config::GetInt(NDR_APP_CONFIG_PATH, "WindowProperties", "YPosition"),
            },
            {
                (UInt32)Config::GetInt(NDR_APP_CONFIG_PATH, "WindowProperties", "Width"),
                (UInt32)Config::GetInt(NDR_APP_CONFIG_PATH, "WindowProperties", "Height"),
            },
            Config::GetString(NDR_APP_CONFIG_PATH, "WindowProperties", "AppName"),
            Config::GetBool(NDR_APP_CONFIG_PATH, "WindowProperties", "VSync")
        );
        _window = Window::Create(properties, _dispatcher);
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
            Renderer::Clear();
            Tick();
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
