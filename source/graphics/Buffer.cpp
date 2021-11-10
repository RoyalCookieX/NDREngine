#include "ndrpch.h"
#include "Buffer.h"

namespace NDR
{
    VertexBuffer::VertexBuffer():
        _id(0),
        _count(0)
    {
    }

    VertexBuffer::VertexBuffer(const size_t count, const VertexLayout& layout):
        _count(count),
        _layout(layout)
    {
        glCreateBuffers(1, &_id);
        glBindBuffer(GL_ARRAY_BUFFER, _id);
        glBufferData(GL_ARRAY_BUFFER, GetSize(), nullptr, GL_DYNAMIC_DRAW);
    }

    VertexBuffer::VertexBuffer(std::vector<float> vertices, const VertexLayout& layout):
        _count(vertices.size()),
        _layout(layout)
    {
        glCreateBuffers(1, &_id);
        glBindBuffer(GL_ARRAY_BUFFER, _id);
        glBufferData(GL_ARRAY_BUFFER, GetSize(), vertices.data(), GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer() { Release(); }

    VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept:
        _id(other._id),
        _count(other._count),
        _layout(other._layout)
    {
        other._id = 0;
        other._count = 0;
        other._layout = {};
    }

    VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
    {
        if(*this != other)
        {
            Release();
            _id = other._id;
            _count = other._count;
            _layout = other._layout;

            other._id = 0;
            other._count = 0;
            other._layout = {};
        }
        return *this;
    }

    bool VertexBuffer::operator==(const VertexBuffer& other) const { return _id == other._id; }
    bool VertexBuffer::operator!=(const VertexBuffer& other) const { return !(*this == other); }
    
    size_t VertexBuffer::GetCount() const { return _count; }
    size_t VertexBuffer::GetSize() const { return _count * sizeof(float); }

    const VertexLayout& VertexBuffer::GetLayout() const { return _layout; }

    void VertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, _id); }

    void VertexBuffer::SetData(const uint64_t offset, std::vector<float> vertices)
    {
#ifdef NDR_DEBUG
        const size_t usedSize = (vertices.size() * sizeof(float)) + offset;
        assert(("[VertexBuffer Error]: Data and Offset are invalid!", usedSize <= GetSize()));
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

    bool IndexBuffer::operator==(const IndexBuffer& other) const { return _id == other._id; }
    bool IndexBuffer::operator!=(const IndexBuffer& other) const { return !(*this == other); }
    
    size_t IndexBuffer::GetCount() const { return _count; }
    size_t IndexBuffer::GetSize() const { return _count * sizeof(uint32_t); }

    void IndexBuffer::Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id); }
    void IndexBuffer::Release()
    {
        glDeleteBuffers(1, &_id);
        _id = 0;
        _count = 0;
    }
}
