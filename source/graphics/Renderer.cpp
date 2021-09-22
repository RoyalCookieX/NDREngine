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
        GLCall(glDrawElements(GL_TRIANGLES, mesh.GetIndexData().Count(), GL_UNSIGNED_INT, nullptr));
    }

    void Renderer::DrawBackground(GLfloat r, GLfloat g, GLfloat b, GLfloat a) const
    {
        glClearColor(0.1f, 0.2f, 0.3f, 1.f);
    }
}
