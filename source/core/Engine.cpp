#include "ndrpch.h"
#include "Engine.h"

#include "input/Input.h"
#include "utility/AssetManager.h"

namespace NDR
{
    static const uint32_t WIDTH = 800;
    static const uint32_t HEIGHT = 600;
    static const float ASPECT_RATIO = (float)WIDTH / (float)HEIGHT;
    
    Engine::Engine()
    {
        _window = Window::Create(WindowProps(WIDTH, HEIGHT, "NDREngine", true));
        _renderer = new Renderer;
        _renderer->SetBlendMode(BlendMode::TRANSPARENT);
        
        _texture = AssetManager::LoadTexture("assets/textures/obama.png");
        _texture.Bind(0);
        _shader = AssetManager::LoadShader("assets/shaders/Quad.shader");
        _shader.Use();
        _shader.SetInt("u_Texture", 0);
        
        VertexBuffer vb(4 * 4);
        _indexBuffer = IndexBuffer({0, 1, 2, 0, 2, 3});
        VertexLayout layout;
        layout.AddAttribute({2, false});
        layout.AddAttribute({2, false});
        _vertexArray = VertexArray(std::move(vb), layout);
    }

    Engine::~Engine()
    {
        delete _renderer;
    }

    void Engine::Run()
    {
        float t = 0;

        Camera camera(glm::perspective(45.0f, ASPECT_RATIO, 0.01f, 10.0f));
        
        while (_window->Active())
        {
            const float r = ((glm::sin(t + 0.0f) + 1.0f) * 0.5f) * 0.5f;
            const float g = ((glm::sin(t + 2.0f) + 1.0f) * 0.5f) * 0.5f;
            const float b = ((glm::sin(t + 4.2f) + 1.0f) * 0.5f) * 0.5f;
            t += 0.02f;
            
            _shader.SetMat4("u_MVP", camera.GetViewProjMatrix());

            _vertexArray.GetVertexBuffer().SetData(
                {
                    -0.5f + r - 0.25f, -0.5f, 0.0f, 0.0f,
                     0.5f + r - 0.25f, -0.5f, 1.0f, 0.0f,
                     0.5f + r - 0.25f,  0.5f, 1.0f, 1.0f,
                    -0.5f + r - 0.25f,  0.5f, 0.0f, 1.0f,
                });

            _renderer->Clear();
            _renderer->DrawBackground(r, g, b, 1.0f);
            _renderer->Draw(_vertexArray, _indexBuffer, _shader);
            _window->SwapBuffers();

            _window->PollEvents();
            if(Input::GetKey(NDR_KEY_ESCAPE)) _window->Close();

            camera.Tick();
        }
    }
}
