#pragma once
#include "Vertex.h"

namespace NDR
{
    class Mesh
    {
    public:
        virtual ~Mesh() { }

        virtual uint32_t GetVertexCount() const = 0;
        virtual uint32_t GetIndexCount() const = 0;
        virtual void Bind() const = 0;

        static Mesh* Create(const VertexData& vertices, const IndexData& indices, const VertexLayout& layout);
    };
}
