#include "ndrpch.h"
#include "Renderer_opengl.h"

namespace NDR
{
    Renderer* Renderer::Create()
    {
        return new GraphicsAPI::Renderer_opengl();
    }
namespace GraphicsAPI
{

        Renderer_opengl::Renderer_opengl() { }
        Renderer_opengl::~Renderer_opengl() { }

        void Renderer_opengl::Clear() const
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void Renderer_opengl::Draw(Mesh* mesh, Shader* shader) const
        {
            mesh->Bind();
            if(mesh->GetIndexCount() > 0)
            {
                glDrawElements(GL_TRIANGLES, mesh->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
            }
            else
            {
                glDrawArrays(GL_TRIANGLES, 0, mesh->GetVertexCount());
            }
        }

        void Renderer_opengl::DrawBackground(GLfloat r, GLfloat g, GLfloat b, GLfloat a) const
        {
            glClearColor(0.1f, 0.2f, 0.3f, 1.f);
        }

        void Renderer_opengl::SetBlendMode(const BlendMode& blendMode) const
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
}
