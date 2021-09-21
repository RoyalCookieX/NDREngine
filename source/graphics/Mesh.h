#pragma once
#include "Vertex.h"

namespace NDR
{
    class Mesh
    {
    public:
        Mesh(VertexArray* vertices, IndexBuffer* indices) noexcept;
        ~Mesh();
        
        const VertexArray& GetVertexData() const;
        const IndexBuffer& GetIndexData() const;
        void Bind() const;
        void Draw() const;
    private:
        VertexArray* _vertexArray;
        IndexBuffer* _indexBuffer;
    };
}
