#include "ndrpch.h"
#include "RenderBatch.h"

#include "utility/AssetManager.h"

namespace NDR
{
    QuadRenderBatch::QuadRenderBatch():
        _quadCount(0),
        _indicesCount(0),
        _maxQuads(0),
        _maxTextureSlots(0)
    {
    }

    void QuadRenderBatch::Initialize(uint32_t maxQuads)
    {
        _maxQuads = maxQuads;
        QuadRenderBatch::Reset();

        // get number of texture slots
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &_maxTextureSlots);
        _textureIndexes.reserve(_maxTextureSlots);
        for(int32_t i = 0; i < _maxTextureSlots; i++)
            _textureIndexes.push_back(i);

        // setup vertex array
        VertexLayout layout;
        layout.AddAttribute({4, false}); // position
        layout.AddAttribute({4, false}); // color
        layout.AddAttribute({2, false}); // texCoords
        layout.AddAttribute({1, false}); // texIndex
        VertexBuffer vb(GetMaxVerticies() * layout.GetStride());
        _va = VertexArray(std::move(vb), layout);

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
        _ib = IndexBuffer(indices);

        _defaultTexture = Texture2D({1, 1, 1});
        //TODO: get assets from engine path, instead of application path
        _defaultShader = LoadShader("assets/shaders/Quad.shader");
        _defaultShader.Use();
        _defaultShader.SetIntArray("u_Textures", _textureIndexes.data(), (uint32_t)_textureIndexes.size());
    }

    void QuadRenderBatch::Reset()
    {
        _quadCount = 0;
        _indicesCount = 0;
        _boundTextures.clear();
    }

    void QuadRenderBatch::AddElement(std::vector<float> vertices)
    {
        _va.GetVertexBuffer().SetData(_quadCount * 4 * _va.GetVertexLayout().GetStride(), vertices);
        _quadCount++;
        _indicesCount += 6;
    }

    bool QuadRenderBatch::IsFull() const
    {
        return _quadCount >= _maxQuads || _boundTextures.size() >= _maxTextureSlots;
    }

    float QuadRenderBatch::GetTextureIndex(Texture& texture)
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
