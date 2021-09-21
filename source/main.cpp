#include <iostream>

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/Engine.h"
#include "core/Window.h"
#include "graphics/Mesh.h"
#include "graphics/Renderer.h"
#include "graphics/Shader.h"
#include "graphics/Vertex.h"
#include "utility/AssetManager.h"

#if (NDR_RELEASE && NDR_PLATFORM_WINDOWS)
int WinMain()
#else
int main()
#endif
{
    // NDR::Engine* engine = new NDR::Engine();
    // engine->Run();
    // delete engine;
    // return 0;
    
    if(!glfwInit())
    {
        printf("GLFW did not initalize!");
        glfwTerminate();
    }
    const NDR::Window window({ 800, 600, "Rendering Test", true });
    const NDR::Renderer renderer;
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    
    NDR::VertexLayout layout;
    layout.AddAttribute({ 3, GL_FLOAT, GL_FALSE });
    layout.AddAttribute({ 4, GL_FLOAT, GL_FALSE });
    NDR::VertexArray vertexArray(
        {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.5f, 1.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.8f, 0.5f, 1.0f, 1.0f,
             0.5f,  0.5f, 0.0f, 0.8f, 0.5f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.8f, 0.5f, 1.0f, 1.0f,
        },
        layout
        );
    NDR::IndexBuffer indexBuffer({ 0, 1, 2, 2, 3, 0 });
    NDR::Mesh mesh(&vertexArray, &indexBuffer);
    
    NDR::Shader shader = NDR::AssetManager::LoadShader("assets/shaders/PosCol.shader");
    shader.Use();

    float t = 0.f;
    while (window.Active())
    {
        const float r = (std::sinf(t) + 1.f) * 0.5f;
        t += 0.01f;
        shader.SetVec4("u_Col", r, 0.1f, 0.3f, 1.f);
        
        renderer.Clear();
        renderer.DrawBackground(0.1f, 0.2f, 0.3f, 1.f);
        renderer.Draw(&mesh, &shader);
        window.SwapBuffers();
        
        glfwPollEvents();
    }
    glfwTerminate();
}
