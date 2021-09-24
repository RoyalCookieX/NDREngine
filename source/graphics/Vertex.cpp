#include "Vertex.h"

#include "core/Error.h"

namespace NDR
{
    // VertexAttribute
    VertexAttribute::VertexAttribute(GLuint count, bool normalized):
        _count(count),
        _normalized(normalized)
    {
    }

    uint32_t VertexAttribute::GetCount() const { return _count; }
    bool VertexAttribute::IsNormalized() const { return _normalized; }
    uint32_t VertexAttribute::GetStride() const { return _count * sizeof(float); }

    // VertexLayout
    VertexLayout::VertexLayout(const std::vector<VertexAttribute>& attributes):
        _attributes(attributes),
        _stride(0)
    {
        for(auto attribute : _attributes)
            _stride += attribute.GetStride();
    }

    VertexAttribute& VertexLayout::operator[](int32_t index) { return GetAttribute(index); }
    uint32_t VertexLayout::GetStride() const { return _stride; }
    VertexAttribute& VertexLayout::GetAttribute(int32_t index) { return _attributes[index]; }
    
    VertexLayout& VertexLayout::AddAttribute(const VertexAttribute& attribute)
    {
        _attributes.emplace_back(attribute);
        _stride += attribute.GetStride();
        return *this;
    }
    
    uint32_t VertexLayout::GetAttributeCount() const { return (uint32_t)_attributes.size(); }

    // VertexData
    VertexData::VertexData(const std::vector<float>& vertices):
        _vertexData(vertices)
    {

    }

    float* VertexData::GetBuffer() { return _vertexData.data(); }
    uint32_t VertexData::GetBufferSize() const { return (uint32_t)_vertexData.size() * sizeof(float); }

    // IndexData
    IndexData::IndexData(const std::vector<uint32_t>& indices):
        _indexData(indices)
    {
    }

    uint32_t* IndexData::GetBuffer() { return _indexData.data(); }
    uint32_t IndexData::GetBufferSize() const { return (uint32_t)_indexData.size() * sizeof(uint32_t); }
    uint32_t IndexData::GetCount() const { return (uint32_t)_indexData.size(); }
}
