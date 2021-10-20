#pragma once
#include "Buffer.h"

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
        VertexAttribute& GetAttribute(int32_t index);
        
        VertexLayout& AddAttribute(const VertexAttribute& attribute);
        uint32_t GetAttributeCount() const;
    private:
        std::vector<VertexAttribute> _attributes;
        size_t _vertexSize;
    };

    class VertexArray
    {
    public:
        VertexArray();
        VertexArray(VertexBuffer&& vertexBuffer, const VertexLayout& layout);
        ~VertexArray();

        VertexArray(const VertexArray&) = delete;
        VertexArray& operator=(const VertexArray&) = delete;

        VertexArray(VertexArray&& other) noexcept;
        VertexArray& operator=(VertexArray&& other) noexcept;

        VertexBuffer& GetVertexBuffer();
        VertexLayout& GetVertexLayout();
        const VertexBuffer& GetVertexBuffer() const;
        size_t GetVertexCount() const;
        void Bind() const;

        friend bool operator==(const VertexArray& left, const VertexArray& right);
    private:
        uint32_t _id;
        
        VertexBuffer _vertexBuffer;
        VertexLayout _layout;
    };

    extern bool operator==(const VertexArray& left, const VertexArray& right);
    extern bool operator!=(const VertexArray& left, const VertexArray& right);
}
