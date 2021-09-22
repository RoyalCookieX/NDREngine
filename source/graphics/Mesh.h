#pragma once
#include "Vertex.h"

namespace NDR
{
    class Mesh
    {
    public:
        Mesh(const VertexArray& vertices, const IndexBuffer& indices) noexcept;
        ~Mesh();
        
        const VertexArray& GetVertexData() const;
        const IndexBuffer& GetIndexData() const;
        void Bind() const;
    private:
        VertexArray _vertexArray;
        IndexBuffer _indexBuffer;
    };
}
