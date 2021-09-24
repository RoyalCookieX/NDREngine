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

    // VertexData
    VertexData::VertexData(const std::vector<float>& vertices):
        _vertexData(vertices),
        _stride(0)
    {
    }

    VertexAttribute& VertexData::operator[](int32_t index) { return GetAttribute(index); }
    float* VertexData::GetBuffer() { return _vertexData.data(); }
    uint32_t VertexData::GetBufferSize() const { return (uint32_t)_vertexData.size() * sizeof(float); }
    uint32_t VertexData::GetStride() const { return _stride; }
    VertexAttribute& VertexData::GetAttribute(int32_t index) { return _attributes[index]; }
    VertexData& VertexData::AddAttribute(const VertexAttribute& attribute)
    {
        _attributes.emplace_back(attribute);
        _stride += attribute.GetStride();
        return *this;
    }  
    uint32_t VertexData::GetAttributeCount() const { return (uint32_t)_attributes.size(); }

    // IndexData
    IndexData::IndexData(const std::vector<uint32_t>& indices):
        _indexData(indices)
    {
    }

    uint32_t* IndexData::GetBuffer() { return _indexData.data(); }
    uint32_t IndexData::GetBufferSize() const { return (uint32_t)_indexData.size() * sizeof(uint32_t); }
    uint32_t IndexData::GetCount() const { return (uint32_t)_indexData.size(); }
}
