#include "ndrpch.h"
#include "RenderBatch.h"

#include "utility/AssetManager.h"

namespace NDR
{
    /*
    RenderBatch::RenderBatch(uint32_t maxElements, uint32_t verticesPerElement, uint32_t indicesPerElement, const VertexLayout& layout, const SharedPtr<Texture>& texture, const SharedPtr<Shader>& shader):
        _maxElements(maxElements),
        _verticesPerElement(verticesPerElement),
        _indicesPerElement(indicesPerElement),
        _elementCount(0),
        _indicesCount(0),
        _maxTextureSlots(0)
    {        
        Reset();

        // TODO: Move Retrieval of Max Texture Units to a different class
        // get number of texture slots
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &_maxTextureSlots);
        _textureIndexes.reserve(_maxTextureSlots);
        for(int32_t i = 0; i < _maxTextureSlots; i++)
            _textureIndexes.push_back(i);

        // setup index buffer
        std::vector<uint32_t> indices;
        indices.reserve(GetMaxIndices());
        uint32_t index = 0;
        for (uint32_t i = 0; i < GetMaxIndices(); i += 6)
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
        _va->AddVertexBuffer(CreateSharedPtr<VertexBuffer>(_maxElements * GetVerticesPerElement() * layout.GetAttributeComponentCount(), layout));
        _ib = CreateSharedPtr<IndexBuffer>(indices);

        _defaultTexture = CreateSharedPtr<Texture2D>(texture);
        _defaultShader = CreateSharedPtr<Shader>(shader);
        glUseProgram(_defaultShader->GetRendererID());
        _defaultShader->SetIntArray("u_Textures", _textureIndexes.data(), (uint32_t)_textureIndexes.size());
    }

    RenderBatch::~RenderBatch()
    {
    }

    void RenderBatch::Reset()
    {
        _elementCount = 0;
        _indicesCount = 0;
        _boundTextures.clear();
    }

    void RenderBatch::AddElement(std::vector<float> vertices)
    {
        const uint64_t offset = _elementCount * GetVerticesPerElement() * _va->GetVertexBuffer(0)->GetLayout().GetVertexSize();       
        _va->GetVertexBuffer(0)->SetData(offset, vertices);
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
            if(_boundTextures[i]->GetRendererID() == texture.GetRendererID())
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
    */
}
