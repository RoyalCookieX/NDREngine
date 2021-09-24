#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "core/Engine.h"
#include "core/Error.h"
#include "core/Window.h"
#include "graphics/Mesh.h"
#include "graphics/Renderer.h"
#include "graphics/Shader.h"
#include "graphics/Vertex.h"
#include "utility/AssetManager.h"
#include "runtime/objects/Camera.h"

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

    const int windowWidth = 1280;
    const int windowHeight = 720;
    const float halfWidth = windowWidth / 2.0f;
    const float halfHeight = windowHeight / 2.0f;
    
    const NDR::Window window({ windowWidth, windowHeight, "NDREngine", true });
    const NDR::Renderer renderer;
    renderer.SetBlendMode(NDR::BlendMode::TRANSPARENT);

#define TEST 0
#if TEST
#define DRAW_ARRAYS 0
#if DRAW_ARRAYS
    NDR::VertexData vertexData(
    {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
    }
);
    const NDR::IndexData indexData;
#else
    NDR::VertexData vertexData(
        {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        }
    );
    const NDR::IndexData indexData({0, 1, 2, 2, 3, 0 });
#endif
    const NDR::VertexLayout layout(
{
            {3, GL_FALSE}, // position
            {2, GL_FALSE}  // texcoords
        }
    );
    const NDR::Mesh mesh(vertexData, indexData, layout);
#else 
    const NDR::Mesh mesh = NDR::AssetManager::LoadMesh("assets/meshes/Cube.obj");
#endif
    const NDR::Texture texture = NDR::AssetManager::LoadTexture("assets/textures/UVTest.png");
    texture.Bind();
    const NDR::Shader shader = NDR::AssetManager::LoadShader("assets/shaders/MVP.shader");
    shader.Use();
    shader.SetInt("u_Texture", 0);

    float t = 0;
    const glm::mat4x4 orthoProj = glm::ortho(-2.0f, 2.0f, -1.125f, 1.125f, -1.0f, 1.0f);
    NDR::Camera cam(orthoProj);
    cam.SetPosition(0.0f, 0.0f, -1.0f);
    
    while (window.Active())
    {
        const float sine = sinf(t);
        const float g = (sine + 1.0f) * 0.5f;
        //cam.SetPosition(sine * 0.2f, 0.0f, 0.0f);
        cam.Rotate(0.02f, glm::vec3(1.0f, 0.0f, 1.0f));
        
        t += 0.05f;
        shader.SetVec4("u_Color", 1.f, g, 1.f, 1.f);

        shader.SetMat4("u_MVP", cam.GetViewProjMatrix());
        
        renderer.Clear();
        renderer.DrawBackground(0.1f, 0.2f, 0.3f, 1.f);
        renderer.Draw(mesh, shader);
        window.SwapBuffers();
        
        window.PollEvents();
    }
    return 0;
}
