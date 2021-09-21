#include "utility/AssetManager.h"
#include "graphics/Mesh.h"
#include "graphics/Shader.h"
#include "core/Engine.h"

#ifdef NDR_DEBUG
int main()
#elif NDR_RELEASE
int WinMain()
#endif
{
    if(!glfwInit())
    {
        printf("GLFW did not initalize!");
        glfwTerminate();
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    const auto window = glfwCreateWindow(800, 600, "Rendering Test", nullptr, nullptr);
    if(window == nullptr)
    {
        printf("GLFW Window did not initalize!");
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
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
    const NDR::Mesh mesh(&vertexArray, &indexBuffer);

    const NDR::Shader shader = NDR::AssetManager::LoadShader("assets/shaders/PosCol.shader");
    shader.Use();

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.1f, 0.2f, 0.3f, 1.f);
        mesh.Draw();
        glfwSwapBuffers(window);
        
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    
    // NDR::Engine* engine = new NDR::Engine();
    // engine->Run();
    // delete engine;
    return 0;
}
