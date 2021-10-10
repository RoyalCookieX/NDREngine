#pragma once

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "math/Transform.h"

namespace NDR
{
    enum class BlendMode
    {
        OPAQUE = 0,
        TRANSPARENT = 1
    };

    struct RenderBatch
    {
    public:
        RenderBatch();
        RenderBatch(uint32_t maxQuads);
        
        VertexArray va;
        VertexLayout layout;
        IndexBuffer ib;
        Shader shader;

        void AddQuad(std::vector<float> vertices);
        bool IsBatchFull() const;
        void Reset();

        uint32_t quadCount, indicesCount;
        uint32_t maxQuads, maxVertices, maxIndices;

        uint32_t maxTextureSlots;
        std::map<Texture*, int32_t> boundTextures;
        std::vector<int32_t> boundSlots;

        Texture2D whiteTexture;
    };

    class Renderer
    {
    public:
        Renderer(uint32_t maxQuads = 1024);
        ~Renderer();
        
        void Clear() const;

        void SetViewProj(const glm::mat4& viewProj);
        void DrawQuad(const Transform& t, const glm::vec4& color = glm::vec4(1.0f));
        void DrawQuad(const Transform& t, Texture2D& texture, const glm::vec4& color = glm::vec4(1.0f));
        void DrawQuad(const Transform& t, Texture2DAtlas& textureAtlas, int32_t x, int32_t y, const glm::vec4& color = glm::vec4(1.0f));
        void Flush();
        
        void DrawBackground(const glm::vec4& color) const;
        void SetBlendMode(const BlendMode& blendMode) const;
    private:
        glm::mat4 _viewProj;
        RenderBatch _batch;
    };
}
