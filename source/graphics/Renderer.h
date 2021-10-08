#pragma once

#include "Mesh.h"
#include "Shader.h"
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

        uint32_t quadCount, indicesCount;
        uint32_t maxQuads, maxVertices, maxIndices;
        int32_t maxTextureSlots;
    };

    class Renderer
    {
    public:
        Renderer(uint32_t maxQuads = 1024);
        ~Renderer();
        
        void Clear() const;

        void SetViewProj(const glm::mat4& viewProj);
        void DrawQuad(const Transform& t);
        void Flush();
        
        void DrawBackground(float r, float g, float b, float a) const;
        void SetBlendMode(const BlendMode& blendMode) const;
    private:
        glm::mat4 _viewProj;
        RenderBatch _batch;
        bool _isActive;
    };
}
