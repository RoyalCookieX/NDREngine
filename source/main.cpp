#include <memory>

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
    NDR::VertexArray* vertexArray = new NDR::VertexArray(
        {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        },
        layout
        );
    NDR::IndexBuffer* indexBuffer = new NDR::IndexBuffer({ 0, 1, 2 });
    const NDR::Mesh mesh(vertexArray, indexBuffer);

    const char* vertexSource = R"(
    #version 330 core
    
    layout(location = 0) in vec4 inPos;
    layout(location = 1) in vec4 inCol;

    out vec4 v_Col;
    
    void main()
    {
        gl_Position = inPos;
        v_Col = inCol;
    }
    )";

    const char* fragmentSource = R"(
    #version 330 core

    in vec4 v_Col;
    
    out vec4 FragColor;

    void main()
    {
        FragColor = v_Col;
    }
    )";
    
    const NDR::Shader shader(vertexSource, fragmentSource);
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
