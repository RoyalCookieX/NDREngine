#pragma once
#include "Defines.h"

namespace NDR
{
    struct VertexAttribute
    {
    public:
        VertexAttribute();
        VertexAttribute(UInt32 count, bool normalized);

        UInt32 GetCount() const;
        bool IsNormalized() const;
        UInt32 GetStride() const;
    private:
        UInt32 _count;
        bool _normalized;
    };
    
    struct VertexLayout
    {
    public:
        VertexLayout();
        VertexLayout(const std::vector<VertexAttribute>& attributes);

        VertexAttribute& operator[](Int32 index);

        size_t GetVertexSize() const;
        UInt32 GetAttributeComponentCount() const;
        UInt32 GetAttributeCount() const;
        
        VertexAttribute& GetAttribute(Int32 index);
        VertexLayout& AddAttribute(const VertexAttribute& attribute);
    private:
        std::vector<VertexAttribute> _attributes;
        UInt32 _attributeComponentCount;
    };
}
