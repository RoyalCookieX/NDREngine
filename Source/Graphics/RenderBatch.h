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
        RenderBatch(UInt32 maxElements, UInt32 verticesPerElement, UInt32 indicesPerElement, const VertexLayout& layout, const SharedPtr<Texture>& texture, const SharedPtr<Shader>& shader);
        ~RenderBatch();

        RenderBatch(const RenderBatch&) = delete;
        RenderBatch& operator=(const RenderBatch&) = delete;

        void Reset();
        
        void AddElement(std::vector<float> vertices);
        bool IsFull() const;
        float GetTextureIndex(Texture& texture);

        const SharedPtr<VertexArray>& GetVertexArray() const { return _va; }
        const SharedPtr<IndexBuffer>& GetIndexBuffer() const { return _ib; }
        
        UInt32 GetElementCount() const { return _elementCount; }
        UInt32 GetIndicesCount() const { return _indicesCount; }
        UInt32 GetVerticesPerElement() const { return _verticesPerElement; }
        UInt32 GetIndiciesPerElement() const { return _indicesPerElement; }
        UInt32 GetMaxElements() const { return _maxElements; }
        UInt32 GetMaxVertices() const { return _maxElements * GetVerticesPerElement(); }
        UInt32 GetMaxIndices() const { return _maxElements * GetIndiciesPerElement(); }
        void SetMaxElements(UInt32 maxQuads) { _maxElements = maxQuads; }

        UInt32 GetBoundTextureCount() const { return (UInt32)_boundTextures.size(); }
        Int32 GetMaxTextureSlots() const { return _maxTextureSlots; }
        Texture& GetBoundTexture(uint64_t index) { return *_boundTextures[index]; }
        SharedPtr<Texture2D>& GetDefaultTexture() { return _defaultTexture; }
        SharedPtr<Shader>& GetDefaultShader() { return _defaultShader; }
    private:
        UInt32 _maxElements, _verticesPerElement, _indicesPerElement;
        UInt32 _elementCount, _indicesCount;
        Int32 _maxTextureSlots;

        SharedPtr<VertexArray> _va;
        SharedPtr<IndexBuffer> _ib;
        std::vector<Int32> _textureIndexes;
        std::vector<Texture*> _boundTextures;

        SharedPtr<Texture2D> _defaultTexture;
        SharedPtr<Shader> _defaultShader;
    };
    */
}
