#include "ndrpch.h"
#include "Engine.h"

#include "input/Input.h"
#include "utility/AssetManager.h"

namespace NDR
{
    Engine::Engine()
    {
        _window = Window::Create(WindowProps(800, 600, "NDREngine", true));
        _renderer = Renderer::Create();
        _renderer->SetBlendMode(BlendMode::TRANSPARENT);

        _quadMesh = AssetManager::LoadMesh("assets/meshes/Quad.obj");
        _renderTexture = AssetManager::LoadTexture("assets/textures/UVTest.png");
        _renderTexture->Bind();
        _shader = AssetManager::LoadShader("assets/shaders/Texture.shader");
        _shader->Use();
        _shader->SetInt("u_Texture", 0);
        //_framebuffer = Framebuffer::Create(FramebufferMode::FIXED, 800, 600);
    }

    Engine::~Engine()
    {
        delete _renderTexture, _shader, _quadMesh, _renderer, _window;
        //delete _framebuffer;
    }

    void Engine::Run() const
    {
        while (_window->Active())
        {
            _renderer->Clear();
            _renderer->DrawBackground(0.1f, 0.3f, 0.6f, 1.0f);
            _renderer->Draw(_quadMesh, _shader);
            _window->SwapBuffers();

            
            _window->PollEvents();
            if(Input::GetKey(NDR_KEY_ESCAPE)) _window->Close();
            if(Input::GetKey(NDR_KEY_W)) printf("Up\n");
            if(Input::GetKey(NDR_KEY_A)) printf("Left\n");
            if(Input::GetKey(NDR_KEY_S)) printf("Down\n");
            if(Input::GetKey(NDR_KEY_D)) printf("Right\n");
        }
    }
}
