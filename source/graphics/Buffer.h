#pragma once
#include "Layout.h"

namespace NDR
{
    class VertexBuffer
    {
    public:
        VertexBuffer();
        VertexBuffer(size_t count, const VertexLayout& layout);
        VertexBuffer(std::vector<float> vertices, const VertexLayout& layout);
        ~VertexBuffer();

        VertexBuffer(const VertexBuffer&) = delete;
        VertexBuffer& operator=(const VertexBuffer&) = delete;

        VertexBuffer(VertexBuffer&& other) noexcept;
        VertexBuffer& operator=(VertexBuffer&& other) noexcept;

        size_t GetCount() const;
        size_t GetSize() const;
        const VertexLayout& GetLayout() const;

        void Bind() const;
        void SetData(uint64_t offset, std::vector<float> vertices);
        void Release();

        bool operator==(const VertexBuffer& other) const;
        bool operator!=(const VertexBuffer& other) const;
    private:
        uint32_t _id;
        size_t _count;
        VertexLayout _layout;
    };

    class IndexBuffer
    {
    public:
        IndexBuffer();
        IndexBuffer(std::vector<uint32_t> indices);
        ~IndexBuffer();

        IndexBuffer(const IndexBuffer&) = delete;
        IndexBuffer& operator=(const IndexBuffer&) = delete;

        IndexBuffer(IndexBuffer&& other) noexcept;
        IndexBuffer& operator=(IndexBuffer&& other) noexcept;

        size_t GetCount() const;
        size_t GetSize() const;
        
        void Bind() const;
        void Release();

        bool operator==(const IndexBuffer& other) const;
        bool operator!=(const IndexBuffer& other) const;
    private:
        uint32_t _id;
        size_t _count;
    };
}
