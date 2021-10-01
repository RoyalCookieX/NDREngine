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
        void Draw(const Mesh& mesh) const;
        void Draw(const Mesh& mesh, const Shader& shader) const;
        void DrawBackground(float r, float g, float b, float a) const;
        void SetBlendMode(const BlendMode& blendMode) const;
    };
}
