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
        Shader quadShader = AssetManager::LoadShader("assets/shaders/Texture.shader");
        quadShader.Use();
        quadShader.SetInt("u_Texture", 0);
        _quadMesh = Mesh(std::move(vertexArray), std::move(indexBuffer), std::move(quadShader));

        _cam = Camera(glm::perspective(glm::radians(45.0f), 1.33f, 0.1f, 100.0f));
        _cam.GetTransform().SetPosition(0.0f, 0.0f, -2.0f);
    }

    Engine::~Engine()
    {
        delete _renderer;
    }

    void Engine::Run()
    {
        float t = 0;
        
        while (_window->Active())
        {
            const float r = ((glm::sin(t + 0.0f) + 1.0f) * 0.5f) * 0.5f;
            const float g = ((glm::sin(t + 2.0f) + 1.0f) * 0.5f) * 0.5f;
            const float b = ((glm::sin(t + 4.2f) + 1.0f) * 0.5f) * 0.5f;
            t += 0.02f;

            const glm::mat4 model = glm::mat4(1.0f);
            const glm::mat4 viewProj = _cam.GetViewProjMatrix();
            const glm::mat4 mvp = model * viewProj;
            
            _quadMesh.GetShader().SetMat4("u_MVP", model);

            _renderer->Clear();
            _renderer->DrawBackground(r, g, b, 1.0f);
            _renderer->Draw(_quadMesh);
            _window->SwapBuffers();

            _window->PollEvents();
            if(Input::GetKey(NDR_KEY_ESCAPE)) _window->Close();
            if(Input::GetKey(NDR_KEY_W))
                _cam.GetTransform().Translate( 0.0f,  0.1f, 0.0f);
            if(Input::GetKey(NDR_KEY_A))
                _cam.GetTransform().Translate(-0.1f,  0.0f, 0.0f);
            if(Input::GetKey(NDR_KEY_S))
                _cam.GetTransform().Translate( 0.0f, -0.1f, 0.0f);
            if(Input::GetKey(NDR_KEY_D))
                _cam.GetTransform().Translate( 0.1f,  0.0f, 0.0f);

            const glm::vec3 pos = _cam.GetTransform().GetPosition();
            printf("[%f, %f, %f]\n", pos.x, pos.y, pos.z);
        }
    }
}
