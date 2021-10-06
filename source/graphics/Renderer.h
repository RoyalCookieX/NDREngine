#pragma once

#include "Mesh.h"
#include "Shader.h"
#include "runtime/components/Transform.h"
#include "runtime/objects/Camera.h"

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

        void SetViewProj(const glm::mat4& camera);
        glm::mat4 GetViewProj() const;
        
        void Clear() const;
        void Draw(const VertexArray& vertices);
        void Draw(const VertexArray& vertices, const Shader& shader, const Transform& transform);
        void DrawBackground(float r, float g, float b, float a) const;
        void SetBlendMode(const BlendMode& blendMode) const;
    private:
        glm::mat4 _viewProj;
    };
}
