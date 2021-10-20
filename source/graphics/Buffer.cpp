#include "ndrpch.h"
#include "Buffer.h"
#include "glad/glad.h"

namespace NDR
{
    VertexBuffer::VertexBuffer():
        _id(0),
        _count(0)
    {
    }

    VertexBuffer::VertexBuffer(size_t count):
        _count(count)
    {
        glCreateBuffers(1, &_id);
        glBindBuffer(GL_ARRAY_BUFFER, _id);
        glBufferData(GL_ARRAY_BUFFER, GetSize(), nullptr, GL_DYNAMIC_DRAW);
    }

    VertexBuffer::VertexBuffer(std::vector<float> vertices):
        _count(vertices.size())
    {
        glCreateBuffers(1, &_id);
        glBindBuffer(GL_ARRAY_BUFFER, _id);
        glBufferData(GL_ARRAY_BUFFER, GetSize(), vertices.data(), GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer() { Release(); }

    VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept:
        _id(other._id),
        _count(other._count)
    {
        other._id = 0;
        other._count = 0;
    }

    VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
    {
        if(*this != other)
        {
            Release();
            _id = other._id;
            _count = other._count;

            other._id = 0;
            other._count = 0;
        }
        return *this;
    }
    size_t VertexBuffer::GetCount() const { return _count; }
    size_t VertexBuffer::GetSize() const { return _count * sizeof(float); }

    void VertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, _id); }

    void VertexBuffer::SetData(const uint64_t offset, std::vector<float> vertices)
    {
#ifdef NDR_DEBUG
        assert(("[VertexBuffer Error]: Data and Offset are invalid!", vertices.size() + offset <= GetSize()));
#endif
        glBindBuffer(GL_ARRAY_BUFFER, _id);
        glBufferSubData(GL_ARRAY_BUFFER, offset, vertices.size() * sizeof(float), vertices.data());
    }

    void VertexBuffer::Release()
    {
        glDeleteBuffers(1, &_id);
        _id = 0;
        _count = 0;
    }
    
    bool operator==(const VertexBuffer& left, const VertexBuffer& right) { return left._id == right._id; }
    bool operator!=(const VertexBuffer& left, const VertexBuffer& right) { return !(left == right); }

    IndexBuffer::IndexBuffer():
        _id(0),
        _count(0)
    {
    }

    IndexBuffer::IndexBuffer(std::vector<uint32_t> indices):
        _count(indices.size())
    {
        glCreateBuffers(1, &_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetSize(), indices.data(), GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer() { Release(); }

    IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept:
        _id(other._id),
        _count(other._count)
    {
        other._id = 0;
        other._count = 0;
    }

    IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept
    {
        if(*this != other)
        {
            Release();
            _id = other._id;
            _count = other._count;

            other._id = 0;
            other._count = 0;
        }
        return *this;
    }
    
    size_t IndexBuffer::GetCount() const { return _count; }
    size_t IndexBuffer::GetSize() const { return _count * sizeof(uint32_t); }

    void IndexBuffer::Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id); }
    void IndexBuffer::Release()
    {
        glDeleteBuffers(1, &_id);
        _id = 0;
        _count = 0;
    }

    bool operator==(const IndexBuffer& left, const IndexBuffer& right) { return left._id == right._id; }
    bool operator!=(const IndexBuffer& left, const IndexBuffer& right) { return !(left == right); }
}
