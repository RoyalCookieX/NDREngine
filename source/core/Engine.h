#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "graphics/Mesh.h"
#include "graphics/Shader.h"

namespace NDR 
{
    class Engine
    {
    public:
        void Run();
        void Render(Mesh mesh, Shader shader);
        void PollEvents() const;
    private:
        GLFWwindow* _window = nullptr;
    };
}
