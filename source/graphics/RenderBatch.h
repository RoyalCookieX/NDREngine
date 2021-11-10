#pragma once
#include "Shader.h"
#include "Texture.h"
#include "Vertex.h"

namespace NDR
{    
    struct RenderBatch
    {
    public:
        RenderBatch();
        RenderBatch(uint32_t maxElements, uint32_t verticesPerElement, uint32_t indicesPerElement, const VertexLayout& layout, Texture&& texture, Shader&& shader);
        ~RenderBatch() { }

        RenderBatch(const RenderBatch&) = delete;
        RenderBatch& operator=(const RenderBatch&) = delete;

        RenderBatch(RenderBatch&& other) noexcept;
        RenderBatch& operator=(RenderBatch&& other) noexcept;

        void Reset();
        
        void AddElement(std::vector<float> vertices);
        bool IsFull() const;
        float GetTextureIndex(Texture& texture);

        const VertexArray& GetVertexArray() const { return _va; }
        const IndexBuffer& GetIndexBuffer() const { return _ib; }
        
        uint32_t GetElementCount() const { return _elementCount; }
        uint32_t GetIndicesCount() const { return _indicesCount; }
        uint32_t GetVerticesPerElement() const { return _verticesPerElement; }
        uint32_t GetIndiciesPerElement() const { return _indicesPerElement; }
        uint32_t GetMaxElements() const { return _maxElements; }
        uint32_t GetMaxVertices() const { return _maxElements * GetVerticesPerElement(); }
        uint32_t GetMaxIndices() const { return _maxElements * GetIndiciesPerElement(); }
        void SetMaxElements(uint32_t maxQuads) { _maxElements = maxQuads; }

        uint32_t GetBoundTextureCount() const { return (uint32_t)_boundTextures.size(); }
        int32_t GetMaxTextureSlots() const { return _maxTextureSlots; }
        Texture& GetBoundTexture(uint64_t index) { return *_boundTextures[index]; }
        Texture2D& GetDefaultTexture() { return _defaultTexture; }
        Shader& GetDefaultShader() { return _defaultShader; }
    private:
        uint32_t _maxElements, _verticesPerElement, _indicesPerElement;
        uint32_t _elementCount, _indicesCount;
        int32_t _maxTextureSlots;

        VertexArray _va;
        IndexBuffer _ib;
        std::vector<int32_t> _textureIndexes;
        std::vector<Texture*> _boundTextures;

        Texture2D _defaultTexture;
        Shader _defaultShader;
    };
}
