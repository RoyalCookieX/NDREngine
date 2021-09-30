#pragma once

namespace NDR
{
    class VertexBuffer
    {
    public:
        VertexBuffer(float* vertices);
        ~VertexBuffer();

        VertexBuffer(const VertexBuffer&) = delete;
        VertexBuffer& operator=(const VertexBuffer&) = delete;

        VertexBuffer(VertexBuffer&& other) noexcept;
        VertexBuffer& operator=(VertexBuffer&& other) noexcept;

        size_t GetCount() const;
        size_t GetSize() const;

        void Bind() const;
        void Release();

        friend bool operator==(const VertexBuffer& left, const VertexBuffer& right);
    private:
        uint32_t _id;
        size_t _count, _size;
    };

    static bool operator==(const VertexBuffer& left, const VertexBuffer& right);
    static bool operator!=(const VertexBuffer& left, const VertexBuffer& right);

    class IndexBuffer
    {
    public:
        IndexBuffer(uint32_t* indices);
        ~IndexBuffer();

        IndexBuffer(const IndexBuffer&) = delete;
        IndexBuffer& operator=(const IndexBuffer&) = delete;

        IndexBuffer(IndexBuffer&& other) noexcept;
        IndexBuffer& operator=(IndexBuffer&& other) noexcept;

        size_t GetCount() const;
        size_t GetSize() const;
        
        void Bind() const;
        void Release();

        friend bool operator==(const IndexBuffer& left, const IndexBuffer& right);
    private:
        uint32_t _id;
        size_t _count, _size;
    };

    static bool operator==(const IndexBuffer& left, const IndexBuffer& right);
    static bool operator!=(const IndexBuffer& left, const IndexBuffer& right);
}