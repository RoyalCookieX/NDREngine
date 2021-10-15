#pragma once
#include "Shader.h"
#include "Texture.h"
#include "Vertex.h"

namespace NDR
{
    struct RenderBatch
    {
    public:
        virtual ~RenderBatch() { }

        virtual void Initialize(uint32_t) = 0;
        virtual void Reset() = 0;
        
        virtual void AddElement(std::vector<float> vertices) = 0;
        virtual bool IsFull() const = 0;
        virtual float GetTextureIndex(Texture& texture) = 0;

        virtual const VertexArray& GetVertexArray() const = 0;
        virtual const IndexBuffer& GetIndexBuffer() const = 0;
        
        virtual uint32_t GetElementCount() = 0;
        virtual uint32_t GetIndicesCount() = 0;
        virtual uint32_t GetVerticesPerElement() const = 0;
        virtual uint32_t GetIndiciesPerElement() const = 0;
        virtual uint32_t GetMaxElements() const = 0;
        virtual void SetMaxElements(uint32_t maxElements) = 0;
        
        uint32_t GetMaxVerticies() const { return GetMaxElements() * GetVerticesPerElement(); }
        uint32_t GetMaxIndices() const { return GetMaxElements() * GetIndiciesPerElement(); }

        virtual uint32_t GetBoundTextureCount() const = 0;
        virtual int32_t GetMaxTextureSlots() const = 0;
        virtual Texture& GetBoundTexture(uint64_t index) = 0;
        virtual Texture2D& GetDefaultTexture() = 0;
        virtual Shader& GetDefaultShader() = 0;
    };

    struct QuadRenderBatch : public RenderBatch
    {
    public:
        QuadRenderBatch();
        virtual ~QuadRenderBatch() override { }

        virtual void Initialize(uint32_t maxQuads) override;
        virtual void Reset() override;
        
        virtual void AddElement(std::vector<float> vertices) override;
        virtual bool IsFull() const override;
        virtual float GetTextureIndex(Texture& texture) override;

        virtual const VertexArray& GetVertexArray() const override { return _va; }
        virtual const IndexBuffer& GetIndexBuffer() const override { return _ib; }
        
        virtual uint32_t GetElementCount() override { return _quadCount; }
        virtual uint32_t GetIndicesCount() override { return _indicesCount; }
        virtual uint32_t GetVerticesPerElement() const override { return 4; }
        virtual uint32_t GetIndiciesPerElement() const override { return 6; }
        virtual uint32_t GetMaxElements() const override { return _maxQuads; }
        virtual void SetMaxElements(uint32_t maxElements) override { _maxQuads = maxElements; }

        virtual uint32_t GetBoundTextureCount() const override { return (uint32_t)_boundTextures.size(); }
        virtual int32_t GetMaxTextureSlots() const override { return _maxTextureSlots; }
        virtual Texture& GetBoundTexture(uint64_t index) override { return *_boundTextures[index]; }
        virtual Texture2D& GetDefaultTexture() override { return _defaultTexture; }
        virtual Shader& GetDefaultShader() override { return _defaultShader; }
    private:
        uint32_t _quadCount, _indicesCount, _maxQuads;
        int32_t _maxTextureSlots;

        VertexArray _va;
        IndexBuffer _ib;
        std::vector<int32_t> _textureIndexes;
        std::vector<Texture*> _boundTextures;

        Texture2D _defaultTexture;
        Shader _defaultShader;
    };
}
