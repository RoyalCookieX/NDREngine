#include "Engine.h"

namespace NDR
{
    void Engine::Run()
    {
        if(!glfwInit())
        {
            printf("GLFW did not initalize!");
            glfwTerminate();
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        _window = glfwCreateWindow(800, 600, "Rendering Test", nullptr, nullptr);
        if(_window == nullptr)
        {
            printf("GLFW Window did not initalize!");
            glfwTerminate();
        }
        glfwMakeContextCurrent(_window);

        while (!glfwWindowShouldClose(_window))
        {
            PollEvents(); 
            glfwSwapBuffers(_window);
        }

        glfwDestroyWindow(_window);
        glfwTerminate();
    }

    void Engine::Render(Mesh mesh, Shader shader)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void Engine::PollEvents() const
    {
        if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(_window, true);
        glfwPollEvents();
    }
}
