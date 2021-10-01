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

        std::vector<float> vertices
        {
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        };

        std::vector<uint32_t> indices
        {
            1, 2, 3,  // 1 0
            1, 3, 0   // 2 3
        };
        
        _cubeTexture = AssetManager::LoadTexture("assets/textures/UVTest.png");
        _cubeTexture.Bind(0);
        Shader cubeShader = AssetManager::LoadShader("assets/shaders/Cube.shader");
        cubeShader.Use();
        cubeShader.SetInt("u_Texture", 0);
        _cubeMesh = AssetManager::LoadMesh("assets/meshes/Cube.obj");
    }

    Engine::~Engine()
    {
        delete _renderer;
    }

    void Engine::Run()
    {
        float t = 0;

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, 45.f, {1.0f, 0.0f, 0.0f});
        model = glm::rotate(model, 45.f, {0.0f, 1.0f, 0.0f});
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1.33f, 0.01f, 100.0f);
        //glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.125f, 1.125f, 0.01f, 10.0f);
        
        while (_window->Active())
        {
            const float r = ((glm::sin(t + 0.0f) + 1.0f) * 0.5f) * 0.5f;
            const float g = ((glm::sin(t + 2.0f) + 1.0f) * 0.5f) * 0.5f;
            const float b = ((glm::sin(t + 4.2f) + 1.0f) * 0.5f) * 0.5f;
            t += 0.02f;
            
            _cubeMesh.GetShader().SetMat4("u_MVP", proj * view * model);

            _renderer->Clear();
            _renderer->DrawBackground(r, g, b, 1.0f);
            _renderer->Draw(_cubeMesh);
            _window->SwapBuffers();

            _window->PollEvents();
            if(Input::GetKey(NDR_KEY_ESCAPE)) _window->Close();
            if(Input::GetKey(NDR_KEY_W)) view = glm::translate(view, { 0.00f, 0.00f, 0.05f});
            if(Input::GetKey(NDR_KEY_A)) view = glm::translate(view, { 0.05f, 0.00f, 0.00f});
            if(Input::GetKey(NDR_KEY_S)) view = glm::translate(view, { 0.00f, 0.00f,-0.05f});
            if(Input::GetKey(NDR_KEY_D)) view = glm::translate(view, {-0.05f, 0.00f, 0.00f});
            if(Input::GetKey(NDR_KEY_Q)) view = glm::translate(view, { 0.00f, 0.05f, 0.00f});
            if(Input::GetKey(NDR_KEY_E)) view = glm::translate(view, { 0.00f,-0.05f, 0.00f});
        }
    }
}
