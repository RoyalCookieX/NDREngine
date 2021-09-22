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
        void Draw(const Mesh& mesh, const Shader& shader) const;
        void DrawBackground(GLfloat r, GLfloat g, GLfloat b, GLfloat a) const;
    };
}
