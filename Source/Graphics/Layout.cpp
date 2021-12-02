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

    VertexAttribute::VertexAttribute(UInt32 count, bool normalized):
        _count(count),
        _normalized(normalized)
    {
#ifdef NDR_DEBUG
        assert(("[VertexAttribute Error]: Count is not 1-4!", _count >= 1 && _count <= 4));
#endif
    }

    UInt32 VertexAttribute::GetCount() const { return _count; }
    bool VertexAttribute::IsNormalized() const { return _normalized; }
    UInt32 VertexAttribute::GetStride() const { return _count * sizeof(float); }

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

    VertexAttribute& VertexLayout::operator[](Int32 index) { return GetAttribute(index); }

    size_t VertexLayout::GetVertexSize() const { return _attributeComponentCount * sizeof(float); }
    UInt32 VertexLayout::GetAttributeComponentCount() const { return _attributeComponentCount; }
    UInt32 VertexLayout::GetAttributeCount() const { return (UInt32)_attributes.size(); }

    VertexAttribute& VertexLayout::GetAttribute(Int32 index) { return _attributes[index]; }
    VertexLayout& VertexLayout::AddAttribute(const VertexAttribute& attribute)
    {
        _attributes.push_back(attribute);
        _attributeComponentCount += attribute.GetCount();
        return *this;
    }
}
