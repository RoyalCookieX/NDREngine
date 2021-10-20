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
        virtual ~RenderBatch() { }

        RenderBatch(const RenderBatch&) = delete;
        RenderBatch& operator=(const RenderBatch&) = delete;

        RenderBatch(RenderBatch&& other) noexcept;
        RenderBatch& operator=(RenderBatch&& other) noexcept;

        virtual void Reset();
        
        virtual void AddElement(std::vector<float> vertices);
        virtual bool IsFull() const;
        virtual float GetTextureIndex(Texture& texture);

        virtual const VertexArray& GetVertexArray() const { return _va; }
        virtual const IndexBuffer& GetIndexBuffer() const { return _ib; }
        
        virtual uint32_t GetElementCount() { return _elementCount; }
        virtual uint32_t GetIndicesCount() { return _indicesCount; }
        virtual uint32_t GetVerticesPerElement() const { return _verticesPerElement; }
        virtual uint32_t GetIndiciesPerElement() const { return _indicesPerElement; }
        virtual uint32_t GetMaxElements() const { return _maxElements; }
        virtual uint32_t GetMaxVertices() const { return _maxElements * GetVerticesPerElement(); }
        virtual uint32_t GetMaxIndices() const { return _maxElements * GetIndiciesPerElement(); }
        virtual void SetMaxElements(uint32_t maxQuads) { _maxElements = maxQuads; }

        virtual uint32_t GetBoundTextureCount() const { return (uint32_t)_boundTextures.size(); }
        virtual int32_t GetMaxTextureSlots() const { return _maxTextureSlots; }
        virtual Texture& GetBoundTexture(uint64_t index) { return *_boundTextures[index]; }
        virtual Texture2D& GetDefaultTexture() { return _defaultTexture; }
        virtual Shader& GetDefaultShader() { return _defaultShader; }
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
