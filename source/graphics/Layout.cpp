#include "ndrpch.h"
#include "Layout.h"

namespace NDR
{
    // VertexAttribute
    VertexAttribute::VertexAttribute():
        _count(1),
        _normalized(false)
    {
    }

    VertexAttribute::VertexAttribute(uint32_t count, bool normalized):
        _count(count),
        _normalized(normalized)
    {
#ifdef NDR_DEBUG
        assert(("[VertexAttribute Error]: Count is not 1-4!", _count >= 1 && _count <= 4));
#endif
    }

    uint32_t VertexAttribute::GetCount() const { return _count; }
    bool VertexAttribute::IsNormalized() const { return _normalized; }
    uint32_t VertexAttribute::GetStride() const { return _count * sizeof(float); }

    VertexLayout::VertexLayout():
        _attributeComponentCount(0)
    {
    }

    VertexLayout::VertexLayout(const std::vector<VertexAttribute>& attributes):
        _attributes(attributes),
        _attributeComponentCount(0)
    {
        for (auto attribute : _attributes)
            _attributeComponentCount += attribute.GetCount();
    }

    VertexAttribute& VertexLayout::operator[](int32_t index) { return GetAttribute(index); }

    size_t VertexLayout::GetVertexSize() const { return _attributeComponentCount * sizeof(float); }
    uint32_t VertexLayout::GetAttributeComponentCount() const { return _attributeComponentCount; }
    uint32_t VertexLayout::GetAttributeCount() const { return (uint32_t)_attributes.size(); }

    VertexAttribute& VertexLayout::GetAttribute(int32_t index) { return _attributes[index]; }
    VertexLayout& VertexLayout::AddAttribute(const VertexAttribute& attribute)
    {
        _attributes.push_back(attribute);
        _attributeComponentCount += attribute.GetCount();
        return *this;
    }
}
