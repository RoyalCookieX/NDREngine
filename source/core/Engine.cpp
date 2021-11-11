#include "ndrpch.h"
#include "Engine.h"

#include "input/Input.h"
#include "utility/Time.h"

namespace NDR
{    
    void Engine::PreInitialize()
    {
        _window = Window::Create({800, 600, "NDREngine", false});
        _renderer = CreateUniquePtr<Renderer>();
    }

    void Engine::Run()
    {
        PreInitialize();
        Initialize();
        
        while(_window->Active())
        {
            _window->PollEvents();
            if(Input::GetKey(NDR_KEY_ESCAPE))
                _window->Close();

            _renderer->Clear();
            Tick(Time::GetDeltaTime());
            _renderer->Flush();
            _window->SwapBuffers();
        }
        
        Shutdown();
        PostShutdown();
    }

    void Engine::PostShutdown()
    {
    }
}
