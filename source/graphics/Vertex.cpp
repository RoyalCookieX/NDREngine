#include "ndrpch.h"
#include "Vertex.h"

namespace NDR
{
    VertexArray::VertexArray():
        _id(0)
    {
    }

    VertexArray::VertexArray(VertexBuffer&& vertexBuffer, IndexBuffer&& indexBuffer):
        _id(0),
        _vertexBuffer(std::move(vertexBuffer)),
        _indexBuffer(std::move(indexBuffer))
    {
        // create vertex array object
        glCreateVertexArrays(1, &_id);
        glBindVertexArray(_id);

        _vertexBuffer.Bind();

        // setup vertex attributes
        auto offset = 0;
        VertexLayout layout = _vertexBuffer.GetLayout();
        for(uint32_t attributeIndex = 0; attributeIndex < _vertexBuffer.GetLayout().GetAttributeCount(); attributeIndex++)
        {
            VertexAttribute attribute = layout[attributeIndex];
            glEnableVertexAttribArray(attributeIndex);
            glVertexAttribPointer(
                attributeIndex,
                attribute.GetCount(),
                GL_FLOAT,
                attribute.IsNormalized(),
                layout.GetVertexSize(),
                (const void*)offset);
            offset += attribute.GetStride();
        }
    }

    VertexArray::~VertexArray() { glDeleteVertexArrays(1, &_id); }

    VertexArray::VertexArray(VertexArray&& other) noexcept:
        _id(other._id),
        _vertexBuffer(std::move(other._vertexBuffer)),
        _indexBuffer(std::move(other._indexBuffer))
    {
        other._id = 0;
    }

    VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
    {
        if(*this != other)
        {
            _id = other._id;
            _vertexBuffer = std::move(other._vertexBuffer);
            _indexBuffer = std::move(other._indexBuffer);

            other._id = 0;
        }
        return *this;
    }

    VertexBuffer& VertexArray::GetVertexBuffer() { return _vertexBuffer; }
    const VertexBuffer& VertexArray::GetVertexBuffer() const { return _vertexBuffer; }
    IndexBuffer& VertexArray::GetIndexBuffer() { return _indexBuffer; }
    const IndexBuffer& VertexArray::GetIndexBuffer() const { return _indexBuffer; }

    void VertexArray::Bind() const
    {
        glBindVertexArray(_id);
        _vertexBuffer.Bind();
        _indexBuffer.Bind();
    }

    bool VertexArray::operator==(const VertexArray& other) const { return _id == other._id; }
    bool VertexArray::operator!=(const VertexArray& other) const { return !(*this == other); }
}
