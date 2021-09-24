#include "Renderer.h"

#include <glad/glad.h>
#include "core/Error.h"

namespace NDR
{
    Renderer::Renderer()
    {
    }

    Renderer::~Renderer()
    {
    }

    void Renderer::Clear() const
    {
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    }

    void Renderer::Draw(const Mesh& mesh, const Shader& shader) const
    {
        mesh.Bind();
        if(mesh.GetIndexCount() > 0)
        {
            GLCall(glDrawElements(GL_TRIANGLES, mesh.GetIndexCount(), GL_UNSIGNED_INT, nullptr));
        }
        else
        {
            GLCall(glDrawArrays(GL_TRIANGLES, 0, mesh.GetVertexCount()));
        }
    }

    void Renderer::DrawBackground(GLfloat r, GLfloat g, GLfloat b, GLfloat a) const
    {
        GLCall(glClearColor(0.1f, 0.2f, 0.3f, 1.f));
    }

    void Renderer::SetBlendMode(const BlendMode& blendMode) const
    {
        switch (blendMode)
        {
            case BlendMode::OPAQUE:
                {
                    GLCall(glDisable(GL_BLEND));
                    break;
                }
            case BlendMode::TRANSPARENT:
                {
                    GLCall(glEnable(GL_BLEND));
                    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
                    break;
                }
        }
    }
}
