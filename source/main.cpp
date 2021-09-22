#include <iostream>

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/Engine.h"
#include "core/Error.h"
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
    {
        NDR::VertexLayout layout;
        layout.AddAttribute({ 3, GL_FLOAT, GL_FALSE }); //position
        layout.AddAttribute({ 2, GL_FLOAT, GL_FALSE }); //texcoords
        const NDR::VertexArray vertexArray(
            {
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
                -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
            },
            layout
            );
        const NDR::IndexBuffer indexBuffer({ 0, 1, 2, 2, 3, 0 });
        const NDR::Mesh mesh(vertexArray, indexBuffer);

        const NDR::Texture texture = NDR::AssetManager::LoadTexture("assets/textures/CPlusPlus17.png");
        texture.Bind();
        const NDR::Shader shader = NDR::AssetManager::LoadShader("assets/shaders/Texture.shader");
        shader.Use();
        shader.SetInt("u_Texture", 0);

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        
        while (window.Active())
        {
            renderer.Clear();
            renderer.DrawBackground(0.1f, 0.2f, 0.3f, 1.f);
            renderer.Draw(mesh, shader);
            window.SwapBuffers();
            
            glfwPollEvents();
        }
    }
    glfwTerminate();
}
