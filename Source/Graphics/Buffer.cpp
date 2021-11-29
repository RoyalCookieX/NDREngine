#include "ndrpch.h"
#include "Buffer.h"

#include "core/Log.h"

namespace NDR
{
    // VertexBuffer
    VertexBuffer::VertexBuffer(const uint32_t count, const VertexLayout& layout):
        _count(count),
        _layout(layout)
    {
        glCreateBuffers(1, &_rendererID);
        glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
        glBufferData(GL_ARRAY_BUFFER, GetSize(), nullptr, GL_DYNAMIC_DRAW);
    }

    VertexBuffer::VertexBuffer(const std::vector<float>& vertices, const VertexLayout& layout):
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

    // IndexBuffer
    IndexBuffer::IndexBuffer(const std::vector<uint32_t>& indices):
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

    // UniformBuffer
    UniformBuffer::UniformBuffer(size_t size, uint32_t binding):
        _size(size)
    {
        glCreateBuffers(1, &_rendererID);
        glBindBuffer(GL_UNIFORM_BUFFER, _rendererID);
        glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
        glBindBufferRange(GL_UNIFORM_BUFFER, binding, _rendererID, 0, size);
    }

    UniformBuffer::~UniformBuffer()
    {
        glDeleteBuffers(1, &_rendererID);
        _rendererID = 0;
        _size = 0;
    }

    void UniformBuffer::SetData(size_t offset, size_t size, const void* data)
    {
        glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
    }
}
