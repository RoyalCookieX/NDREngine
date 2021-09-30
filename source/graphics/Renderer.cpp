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
#ifdef NDR_DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(MessageCallback, nullptr);
#endif
    }
    Renderer::~Renderer() { }

    void Renderer::Clear() const {  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

    void Renderer::Draw(const Mesh& mesh) const
    {
        mesh.GetVertexArray().Bind();
        mesh.GetIndexBuffer().Bind();
        mesh.GetShader().Use();
        glDrawElements(GL_TRIANGLES, (GLsizei)mesh.GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr);
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
