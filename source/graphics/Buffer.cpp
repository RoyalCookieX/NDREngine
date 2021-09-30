#include "ndrpch.h"
#include "Buffer.h"
#include "glad/glad.h"

namespace NDR
{
    VertexBuffer::VertexBuffer(float* vertices)
    {
        _size = sizeof(vertices) * sizeof(float);
        _count = sizeof(vertices) / sizeof(float);
        glCreateBuffers(1, &_id);
        glBufferData(GL_ARRAY_BUFFER, _size, vertices, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer() { Release(); }

    VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept:
        _id(other._id),
        _count(other._count),
        _size(other._size)
    {
        other._id = 0;
        other._count = 0;
        other._size = 0;
    }

    VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
    {
        if(*this != other)
        {
            Release();
            _id = other._id;
            _count = other._count;
            _size = other._size;

            other._id = 0;
            other._count = 0;
            other._size = 0;
        }
        return *this;
    }
    size_t VertexBuffer::GetCount() const { return _count; }
    size_t VertexBuffer::GetSize() const { return _size; }

    void VertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, _id); }
    void VertexBuffer::Release()
    {
        glDeleteBuffers(1, &_id);
        _id = 0;
        _count = 0;
        _size = 0;
    }
    
    bool operator==(const VertexBuffer& left, const VertexBuffer& right) { return left._id == right._id; }
    bool operator!=(const VertexBuffer& left, const VertexBuffer& right) { return !(left == right); }

    IndexBuffer::IndexBuffer(uint32_t* indices)
    {
        _size = sizeof(indices) * sizeof(float);
        _count = sizeof(indices) / sizeof(float);
        glCreateBuffers(1, &_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _size, indices, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer() { Release(); }

    IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept:
        _id(other._id),
        _count(other._count),
        _size(other._size)
    {
        other._id = 0;
        other._count = 0;
        other._size = 0;
    }

    IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept
    {
        if(*this != other)
        {
            Release();
            _id = other._id;
            _count = other._count;
            _size = other._size;

            other._id = 0;
            other._count = 0;
            other._size = 0;
        }
        return *this;
    }
    
    size_t IndexBuffer::GetCount() const { return _count; }
    size_t IndexBuffer::GetSize() const { return _size; }

    void IndexBuffer::Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id); }
    void IndexBuffer::Release()
    {
        glDeleteBuffers(1, &_id);
        _id = 0;
        _count = 0;
        _size = 0;
    }

    bool operator==(const IndexBuffer& left, const IndexBuffer& right) { return left._id == right._id; }
    bool operator!=(const IndexBuffer& left, const IndexBuffer& right) { return !(left == right); }
}
