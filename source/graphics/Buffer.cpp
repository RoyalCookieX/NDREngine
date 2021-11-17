#include "ndrpch.h"
#include "Buffer.h"

#include "core/Log.h"

namespace NDR
{
    VertexBuffer::VertexBuffer():
        _rendererID(0),
        _count(0)
    {
    }

    VertexBuffer::VertexBuffer(const uint32_t count, const VertexLayout& layout):
        _count(count),
        _layout(layout)
    {
        glCreateBuffers(1, &_rendererID);
        glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
        glBufferData(GL_ARRAY_BUFFER, GetSize(), nullptr, GL_DYNAMIC_DRAW);
    }

    VertexBuffer::VertexBuffer(std::vector<float> vertices, const VertexLayout& layout):
        _count((uint32_t)vertices.size()),
        _layout(layout)
    {
        glCreateBuffers(1, &_rendererID);
        glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
        glBufferData(GL_ARRAY_BUFFER, GetSize(), vertices.data(), GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &_rendererID);
        _rendererID = 0;
        _count = 0;
    }

    VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept:
        _rendererID(other._rendererID),
        _count(other._count),
        _layout(other._layout)
    {
        other._rendererID = 0;
        other._count = 0;
        other._layout = {};
    }

    VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
    {
        if(*this != other)
        {
            _rendererID = other._rendererID;
            _count = other._count;
            _layout = other._layout;

            other._rendererID = 0;
            other._count = 0;
            other._layout = {};
        }
        return *this;
    }

    bool VertexBuffer::operator==(const VertexBuffer& other) const { return _rendererID == other._rendererID; }
    bool VertexBuffer::operator!=(const VertexBuffer& other) const { return !(*this == other); }

    void VertexBuffer::SetData(const uint32_t offset, std::vector<float> vertices)
    {
#ifdef NDR_DEBUG
        const size_t usedSize = (vertices.size() * sizeof(float)) + offset;
        if(usedSize > GetSize())
            NDR_LOGERROR("[VertexBuffer]: Data and Offset are invalid!\n  Data + Offset: %llu\n  Buffer Size: %llu", usedSize, GetSize());
#endif
        glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
        glBufferSubData(GL_ARRAY_BUFFER, (uint64_t)offset, vertices.size() * sizeof(float), vertices.data());
    }

    IndexBuffer::IndexBuffer():
        _rendererID(0),
        _count(0)
    {
    }

    IndexBuffer::IndexBuffer(std::vector<uint32_t> indices):
        _count((uint32_t)indices.size())
    {
        glCreateBuffers(1, &_rendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetSize(), indices.data(), GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &_rendererID);
        _rendererID = 0;
        _count = 0;
    }

    IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept:
        _rendererID(other._rendererID),
        _count(other._count)
    {
        other._rendererID = 0;
        other._count = 0;
    }

    IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept
    {
        if(*this != other)
        {
            _rendererID = other._rendererID;
            _count = other._count;

            other._rendererID = 0;
            other._count = 0;
        }
        return *this;
    }

    bool IndexBuffer::operator==(const IndexBuffer& other) const { return _rendererID == other._rendererID; }
    bool IndexBuffer::operator!=(const IndexBuffer& other) const { return !(*this == other); }
}
