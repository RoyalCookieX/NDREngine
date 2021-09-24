#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

namespace NDR
{
    struct VertexAttribute
    {
    public:
        VertexAttribute() = default;
        VertexAttribute(GLuint count, bool normalized);
        ~VertexAttribute() = default;

        uint32_t GetCount() const;
        bool IsNormalized() const;
        uint32_t GetStride() const;
    private:
        uint32_t _count;
        bool _normalized;
    };

    struct VertexData
    {
    public:
        VertexData() = default;
        VertexData(const std::vector<float>& vertices);
        ~VertexData() = default;

        VertexAttribute& operator[](int32_t index);
        
        float* GetBuffer();
        uint32_t GetBufferSize() const;
        uint32_t GetStride() const;
        VertexAttribute& GetAttribute(int32_t index);
        
        VertexData& AddAttribute(const VertexAttribute& attribute);
        uint32_t GetAttributeCount() const;
    private:
        std::vector<float> _vertexData;
        std::vector<VertexAttribute> _attributes;
        uint32_t _stride;
    };

    struct IndexData
    {
    public:
        IndexData() = default;
        IndexData(const std::vector<uint32_t>& indices);
        ~IndexData() = default;

        uint32_t* GetBuffer();
        uint32_t GetBufferSize() const;
        uint32_t GetCount() const;
    private:
        std::vector<uint32_t> _indexData;
    };
}