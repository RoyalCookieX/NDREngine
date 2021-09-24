#pragma once
#include "Vertex.h"

namespace NDR
{
    class Mesh
    {
    public:
        Mesh();
        Mesh(const VertexData& vertexData, const IndexData& indexData, const VertexLayout& layout);
        ~Mesh();

        uint32_t GetVertexCount() const;
        uint32_t GetIndexCount() const;
        void Bind() const;

    private:
        GLuint _vao, _vbo, _ibo;
        
        VertexData _vertexData;
        IndexData _indexData;
        VertexLayout _layout;
    };
}
