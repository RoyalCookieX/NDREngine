#pragma once

#include "RenderBatch.h"
#include "Texture.h"
#include "math/Transform.h"

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
        Renderer(uint32_t maxQuads = 1024);
        ~Renderer();
        
        void SetViewProj(const glm::mat4& viewProj);
        void BindTexture(const Texture& texture, uint32_t slot = 0);
        void Clear() const;

        void DrawElements(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
        void DrawQuad(const Transform& transform, const glm::vec4& color = glm::vec4(1.0f));
        void DrawQuad(const Transform& transform, Texture2D& texture, const glm::vec4& color = glm::vec4(1.0f));
        void DrawQuad(const Transform& transform, Texture2DAtlas& textureAtlas, int32_t x, int32_t y, const glm::vec4& color = glm::vec4(1.0f));
        void Flush();
        
        void DrawBackground(const glm::vec4& color) const;
        void SetBlendMode(const BlendMode& blendMode) const;
    private:
        glm::mat4 _viewProj;
        QuadRenderBatch _batch;
    };
}
