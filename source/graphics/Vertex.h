#pragma once
#include "Buffer.h"

namespace NDR
{
    class VertexArray
    {
    public:
        VertexArray();
        VertexArray(VertexBuffer&& vertexBuffer, IndexBuffer&& indexBuffer);
        ~VertexArray();

        VertexArray(const VertexArray&) = delete;
        VertexArray& operator=(const VertexArray&) = delete;

        VertexArray(VertexArray&& other) noexcept;
        VertexArray& operator=(VertexArray&& other) noexcept;

        VertexBuffer& GetVertexBuffer();
        const VertexBuffer& GetVertexBuffer() const;
        IndexBuffer& GetIndexBuffer();
        const IndexBuffer& GetIndexBuffer() const;
        
        void Bind() const;

        bool operator==(const VertexArray& other) const;
        bool operator!=(const VertexArray& other) const;
    private:
        uint32_t _id;
        
        VertexBuffer _vertexBuffer;
        IndexBuffer _indexBuffer;
    };
}
