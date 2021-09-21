#include "Mesh.h"

#include "core/Error.h"

namespace NDR
{
    Mesh::Mesh(VertexArray* vertices, IndexBuffer* indices) noexcept
        : _vertexArray(vertices),
          _indexBuffer(indices)
    {
        Bind();
    }
    
    Mesh::~Mesh()
    {

    }

    const VertexArray& Mesh::GetVertexData() const { return *_vertexArray; }
    const IndexBuffer& Mesh::GetIndexData() const { return *_indexBuffer; }

    void Mesh::Bind() const
    {
        _vertexArray->Bind();
        _indexBuffer->Bind();
    }

    void Mesh::Draw() const
    {
        Bind();
        GLCall(glDrawElements(GL_TRIANGLES, _indexBuffer->Count(), GL_UNSIGNED_INT, nullptr));
    }
}
