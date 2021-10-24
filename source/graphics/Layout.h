#pragma once

namespace NDR
{
    struct VertexAttribute
    {
    public:
        VertexAttribute();
        VertexAttribute(uint32_t count, bool normalized);

        uint32_t GetCount() const;
        bool IsNormalized() const;
        uint32_t GetStride() const;
    private:
        uint32_t _count;
        bool _normalized;
    };
    
    struct VertexLayout
    {
    public:
        VertexLayout();
        VertexLayout(const std::vector<VertexAttribute>& attributes);

        VertexAttribute& operator[](int32_t index);

        size_t GetVertexSize() const;
        uint32_t GetAttributeComponentCount() const;
        uint32_t GetAttributeCount() const;
        
        VertexAttribute& GetAttribute(int32_t index);
        VertexLayout& AddAttribute(const VertexAttribute& attribute);
    private:
        std::vector<VertexAttribute> _attributes;
        uint32_t _attributeComponentCount;
    };
}
