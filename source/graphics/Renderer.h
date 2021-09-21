#pragma once

#include "Mesh.h"
#include "Shader.h"

namespace NDR
{

    class Renderer
    {
    public:
        Renderer();
        ~Renderer();
        
        void Clear() const;
        void Draw(Mesh* mesh, Shader* shader) const;
        void DrawBackground(GLfloat r, GLfloat g, GLfloat b, GLfloat a) const;
    };
}
