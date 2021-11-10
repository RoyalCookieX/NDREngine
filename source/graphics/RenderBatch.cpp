#include "ndrpch.h"
#include "RenderBatch.h"

#include "utility/AssetManager.h"

namespace NDR
{
    RenderBatch::RenderBatch():
        _maxElements(1),
        _verticesPerElement(1),
        _indicesPerElement(1),
        _elementCount(0),
        _indicesCount(0),
        _maxTextureSlots(0)
    {
    }

    RenderBatch::RenderBatch(const uint32_t maxElements, const uint32_t verticesPerElement, const uint32_t indicesPerElement, const VertexLayout& layout, Texture&& texture, Shader&& shader):
        _maxElements(maxElements),
        _verticesPerElement(verticesPerElement),
        _indicesPerElement(indicesPerElement),
        _elementCount(0),
        _indicesCount(0),
        _maxTextureSlots(0)
    {        
        RenderBatch::Reset();

        // TODO: Move Retrieval of Max Texture Units to a different class
        // get number of texture slots
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &_maxTextureSlots);
        _textureIndexes.reserve(_maxTextureSlots);
        for(int32_t i = 0; i < _maxTextureSlots; i++)
            _textureIndexes.push_back(i);

        // setup vertex buffer 
        VertexBuffer vb(_maxElements * RenderBatch::GetVerticesPerElement() * layout.GetAttributeComponentCount(), layout);

        // setup index buffer
        std::vector<uint32_t> indices;
        indices.reserve(RenderBatch::GetMaxIndices());
        uint32_t index = 0;
        for (uint32_t i = 0; i < RenderBatch::GetMaxIndices(); i += 6)
        {
            indices.push_back(index + 0);
            indices.push_back(index + 1);
            indices.push_back(index + 2);
            indices.push_back(index + 0);
            indices.push_back(index + 2);
            indices.push_back(index + 3);
            index += 4;
        }
        
        // setup vertex array and index buffer
        _va = VertexArray(std::move(vb));
        _ib = IndexBuffer(indices);

        _defaultTexture = (Texture2D&&)texture;
        _defaultShader = (Shader&&)shader;
        _defaultShader.Use();
        _defaultShader.SetIntArray("u_Textures", _textureIndexes.data(), (uint32_t)_textureIndexes.size());
    }

    RenderBatch::RenderBatch(RenderBatch&& other) noexcept
    {
        _maxElements = other._maxElements;
        _verticesPerElement = other._verticesPerElement;
        _indicesPerElement = other._indicesPerElement;
        _elementCount = other._elementCount;
        _indicesCount = other._indicesCount;
        _maxTextureSlots = other._maxTextureSlots;
        _va = std::move(other._va);
        _ib = std::move(other._ib);
        _textureIndexes = std::move(other._textureIndexes);
        _boundTextures = std::move(other._boundTextures);
        _defaultTexture = std::move(other._defaultTexture);
        _defaultShader = std::move(other._defaultShader);

        other._maxElements = 0;
        other._verticesPerElement = 0;
        other._indicesPerElement = 0;
        other._elementCount = 0;
        other._indicesCount = 0;
        other._maxTextureSlots = 0;
    }

    RenderBatch& RenderBatch::operator=(RenderBatch&& other) noexcept
    {
        if(this->_va != other._va)
        {
            _maxElements = other._maxElements;
            _verticesPerElement = other._verticesPerElement;
            _indicesPerElement = other._indicesPerElement;
            _elementCount = other._elementCount;
            _indicesCount = other._indicesCount;
            _maxTextureSlots = other._maxTextureSlots;
            _va = std::move(other._va);
            _ib = std::move(other._ib);
            _textureIndexes = std::move(other._textureIndexes);
            _boundTextures = std::move(other._boundTextures);
            _defaultTexture = std::move(other._defaultTexture);
            _defaultShader = std::move(other._defaultShader);

            other._maxElements = 0;
            other._verticesPerElement = 0;
            other._indicesPerElement = 0;
            other._elementCount = 0;
            other._indicesCount = 0;
            other._maxTextureSlots = 0;
        }
        return *this;
    }

    void RenderBatch::Reset()
    {
        _elementCount = 0;
        _indicesCount = 0;
        _boundTextures.clear();
    }

    void RenderBatch::AddElement(std::vector<float> vertices)
    {
        const uint64_t offset = _elementCount * GetVerticesPerElement() * _va.GetVertexBuffer().GetLayout().GetVertexSize();       
        _va.GetVertexBuffer().SetData(offset, vertices);
        _elementCount++;
        _indicesCount += GetIndiciesPerElement();
    }

    bool RenderBatch::IsFull() const
    {
        return _elementCount >= _maxElements || _boundTextures.size() >= _maxTextureSlots;
    }

    float RenderBatch::GetTextureIndex(Texture& texture)
    {
        float texIndex = -1.0f;
        for(size_t i = 0; i < _boundTextures.size(); i++)
        {
            if(_boundTextures[i]->GetTextureID() == texture.GetTextureID())
            {
                texIndex = (float)i;
                break;
            }
        }
        if(texIndex == -1.0f)
        {
            const int32_t newIndex = (int32_t)_boundTextures.size();
            _boundTextures.push_back(&texture);
            texIndex = (float)newIndex;
        }
        return texIndex;
    }
}
