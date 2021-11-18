#include "ndrpch.h"
#include "Vertex.h"

namespace NDR
{
    VertexArray::VertexArray()
    {
        glCreateVertexArrays(1, &_rendererID);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &_rendererID);
    }

    void VertexArray::AddVertexBuffer(SharedPtr<VertexBuffer>&& vertexBuffer)
    {
        glBindVertexArray(_rendererID);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->GetRendererID());

        // setup vertex attributes
        auto offset = 0;
        VertexLayout layout = vertexBuffer->GetLayout();
        for(uint32_t attributeIndex = 0; attributeIndex < vertexBuffer->GetLayout().GetAttributeCount(); attributeIndex++)
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

        _vertexBuffers.push_back(std::move(vertexBuffer));
    }
}
