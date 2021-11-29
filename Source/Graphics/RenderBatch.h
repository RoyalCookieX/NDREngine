#pragma once
#include "Shader.h"
#include "Texture.h"
#include "Vertex.h"

namespace NDR
{
    /*
     *TODO: Reimplement later
    struct RenderBatch
    {
    public:
        RenderBatch(uint32_t maxElements, uint32_t verticesPerElement, uint32_t indicesPerElement, const VertexLayout& layout, const SharedPtr<Texture>& texture, const SharedPtr<Shader>& shader);
        ~RenderBatch();

        RenderBatch(const RenderBatch&) = delete;
        RenderBatch& operator=(const RenderBatch&) = delete;

        void Reset();
        
        void AddElement(std::vector<float> vertices);
        bool IsFull() const;
        float GetTextureIndex(Texture& texture);

        const SharedPtr<VertexArray>& GetVertexArray() const { return _va; }
        const SharedPtr<IndexBuffer>& GetIndexBuffer() const { return _ib; }
        
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
        SharedPtr<Texture2D>& GetDefaultTexture() { return _defaultTexture; }
        SharedPtr<Shader>& GetDefaultShader() { return _defaultShader; }
    private:
        uint32_t _maxElements, _verticesPerElement, _indicesPerElement;
        uint32_t _elementCount, _indicesCount;
        int32_t _maxTextureSlots;

        SharedPtr<VertexArray> _va;
        SharedPtr<IndexBuffer> _ib;
        std::vector<int32_t> _textureIndexes;
        std::vector<Texture*> _boundTextures;

        SharedPtr<Texture2D> _defaultTexture;
        SharedPtr<Shader> _defaultShader;
    };
    */
}
