#pragma once

#include "Mesh.h"
#include "Shader.h"

namespace NDR
{
    enum class BlendMode
    {
        OPAQUE = 0,
        TRANSPARENT = 1
    };

    class Renderer
    {
    public:
        Renderer();
        ~Renderer();
        
        void Clear() const;
        void Draw(const VertexArray& vertices);
        void Draw(const VertexArray& vertices, const Shader& shader);
        void Draw(const VertexArray& vertices, const IndexBuffer& indices);
        void Draw(const VertexArray& vertices, const IndexBuffer& indices, Shader& shader);
        void DrawBackground(float r, float g, float b, float a) const;
        void SetBlendMode(const BlendMode& blendMode) const;
    };
}
