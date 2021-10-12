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
        float GetTextureIndex(const Texture& texture);
        void Reset();

        uint32_t quadCount, indicesCount;
        uint32_t maxQuads, maxVertices, maxIndices;

        int32_t maxTextureSlots;
        std::vector<const Texture*> boundTextures;
        std::vector<int32_t> textureIndexes;

        Texture2D whiteTexture;
    };

    class Renderer
    {
    public:
        Renderer(uint32_t maxQuads = 1024);
        ~Renderer();
        
        void SetViewProj(const glm::mat4& viewProj);
        void BindTexture(const Texture& texture, uint32_t slot = 0);
        void BindShader(const Shader& shader);
        void Clear() const;

        void DrawElements(uint32_t count);
        void DrawQuad(const Transform& transform, const glm::vec4& color = glm::vec4(1.0f));
        void DrawQuad(const Transform& transform, Texture2D& texture, const glm::vec4& color = glm::vec4(1.0f));
        void DrawQuad(const Transform& transform, Texture2DAtlas& textureAtlas, int32_t x, int32_t y, const glm::vec4& color = glm::vec4(1.0f));
        void Flush();
        
        void DrawBackground(const glm::vec4& color) const;
        void SetBlendMode(const BlendMode& blendMode) const;
    private:
        glm::mat4 _viewProj;
        RenderBatch _batch;
    };
}
