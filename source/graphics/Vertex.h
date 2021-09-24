#pragma once

namespace NDR
{
    struct VertexAttribute
    {
    public:
        VertexAttribute();
        VertexAttribute(GLuint count, bool normalized);
        ~VertexAttribute() = default;

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
        ~VertexLayout() = default;

        VertexAttribute& operator[](int32_t index);

        uint32_t GetStride() const;
        VertexAttribute& GetAttribute(int32_t index);
        
        VertexLayout& AddAttribute(const VertexAttribute& attribute);
        uint32_t GetAttributeCount() const;
    private:
        std::vector<VertexAttribute> _attributes;
        uint32_t _stride;
    };

    struct VertexData
    {
    public:
        VertexData();
        VertexData(const std::vector<float>& vertices);
        ~VertexData() = default;
        
        float* GetBuffer();
        uint32_t GetBufferSize() const;
        uint32_t GetCount() const;
    private:
        std::vector<float> _vertexData;
    };

    struct IndexData
    {
    public:
        IndexData();
        IndexData(const std::vector<uint32_t>& indices);
        ~IndexData() = default;

        uint32_t* GetBuffer();
        uint32_t GetBufferSize() const;
        uint32_t GetCount() const;
    private:
        std::vector<uint32_t> _indexData;
    };
}