#include "ndrpch.h"
#include "Vertex.h"

namespace NDR
{
    VertexArray::VertexArray():
        _rendererID(0)
    {
    }

    VertexArray::VertexArray(VertexBuffer&& vertexBuffer):
        _vertexBuffer(std::move(vertexBuffer))
    {
        // create vertex array object
        glCreateVertexArrays(1, &_rendererID);
        glBindVertexArray(_rendererID);
        glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer.GetRendererID());

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

    VertexArray::~VertexArray() { glDeleteVertexArrays(1, &_rendererID); }

    VertexArray::VertexArray(VertexArray&& other) noexcept:
        _rendererID(other._rendererID),
        _vertexBuffer(std::move(other._vertexBuffer))
    {
        other._rendererID = 0;
    }

    VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
    {
        if(*this != other)
        {
            _rendererID = other._rendererID;
            _vertexBuffer = std::move(other._vertexBuffer);

            other._rendererID = 0;
        }
        return *this;
    }

    bool VertexArray::operator==(const VertexArray& other) const { return _rendererID == other._rendererID; }
    bool VertexArray::operator!=(const VertexArray& other) const { return !(*this == other); }
}
