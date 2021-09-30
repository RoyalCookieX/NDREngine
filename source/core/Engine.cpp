#include "ndrpch.h"
#include "Engine.h"

#include "input/Input.h"
#include "utility/AssetManager.h"

namespace NDR
{
    Engine::Engine()
    {
        _window = Window::Create(WindowProps(800, 600, "NDREngine", true));
        _renderer = new Renderer;
        _renderer->SetBlendMode(BlendMode::TRANSPARENT);

        const std::vector<float> vertices
        {
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        };

        const std::vector<uint32_t> indices
        {
            1, 2, 3,  // 1 0
            1, 3, 0   // 2 3
        };

        VertexBuffer vertexBuffer(vertices);
        IndexBuffer indexBuffer(indices);
        VertexLayout layout;
        layout.AddAttribute({3, false});
        layout.AddAttribute({2, false});
        VertexArray vertexArray(std::move(vertexBuffer), layout);
        
        _quadTexture = AssetManager::LoadTexture("assets/textures/UVTest.png");
        _quadTexture.Bind(0);
        _quadShader = AssetManager::LoadShader("assets/shaders/Texture.shader");
        _quadShader.Use();
        _quadShader.SetInt("u_Texture", 0);
        _quadMesh = Mesh(std::move(vertexArray), std::move(indexBuffer), std::move(_quadShader));

        //_framebuffer = Framebuffer(FramebufferMode::SCREENSIZE, 800, 600);
    }

    Engine::~Engine()
    {
        delete _renderer;
    }

    void Engine::Run() const
    {
        float t = 0;
        while (_window->Active())
        {
            const float r = ((glm::sin(t + 0.0f) + 1.0f) * 0.5f) * 0.5f;
            const float g = ((glm::sin(t + 2.0f) + 1.0f) * 0.5f) * 0.5f;
            const float b = ((glm::sin(t + 4.2f) + 1.0f) * 0.5f) * 0.5f;
            t += 0.02f;

            _renderer->Clear();
            _renderer->DrawBackground(r, g, b, 1.0f);
            //_framebuffer.Bind();
            _renderer->Draw(_quadMesh);
            //_framebuffer.Unbind();
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
