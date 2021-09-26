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
        virtual ~Renderer() { }
        
        virtual void Clear() const = 0;
        virtual void Draw(const Mesh& mesh, const Shader& shader) const = 0;
        virtual void DrawBackground(float r, float g, float b, float a) const = 0;
        virtual void SetBlendMode(const BlendMode& blendMode) const = 0;

        static Renderer* Create();
    };
}
