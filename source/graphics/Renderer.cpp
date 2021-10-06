#include "ndrpch.h"
#include "Renderer.h"

namespace NDR
{
#ifdef NDR_DEBUG
    // from https://www.khronos.org/opengl/wiki/OpenGL_Error
    inline void
    MessageCallback( GLenum source,
                     GLenum type,
                     GLuint id,
                     GLenum severity,
                     GLsizei length,
                     const GLchar* message,
                     const void* userParam )
    {
        fprintf( stderr, "GL CALLBACK: %s message = %s\n",
                 ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
                  message );
    }
#endif    
    Renderer::Renderer()
    {
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            printf("GLAD did not initalize!\n");
            glfwTerminate();
            return;
        }
#ifdef NDR_DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(MessageCallback, nullptr);
#endif
        glEnable(GL_DEPTH_TEST);
    }
    Renderer::~Renderer() { }

    void Renderer::Clear() const {  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

    void Renderer::Draw(const VertexArray& vertices)
    {
        vertices.Bind();
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertices.GetVertexCount());
    }

    void Renderer::Draw(const VertexArray& vertices, const Shader& shader)
    {
        vertices.Bind();
        shader.Use();
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertices.GetVertexCount());
    }

    void Renderer::Draw(const VertexArray& vertices, const IndexBuffer& indices)
    {
        vertices.Bind();
        indices.Bind();
        glDrawElements(GL_TRIANGLES, indices.GetCount(), GL_UNSIGNED_INT, nullptr);
    }

    void Renderer::Draw(const VertexArray& vertices, const IndexBuffer& indices, Shader& shader)
    {
        vertices.Bind();
        indices.Bind();
        shader.Use();
        glDrawElements(GL_TRIANGLES, indices.GetCount(), GL_UNSIGNED_INT, nullptr);
    }

    void Renderer::DrawBackground(const float r, const float g, const float b, const float a) const { glClearColor(r, g, b, a); }
    void Renderer::SetBlendMode(const BlendMode& blendMode) const
    {
        switch (blendMode)
        {
        case BlendMode::OPAQUE:
            {
                glDisable(GL_BLEND);
                break;
            }
        case BlendMode::TRANSPARENT:
            {
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                break;
            }
        }
    }
}
