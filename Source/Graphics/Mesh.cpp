#include "ndrpch.h"
#include "Mesh.h"

#include "Vertex.h"

namespace NDR
{
    SubMesh::SubMesh(SPointer<IndexBuffer>&& indexBuffer, SPointer<Material>&& mat):
        _indexBuffer(std::move(indexBuffer)),
        _material(std::move(mat))
    {
    }

    Mesh::Mesh(SPointer<VertexBuffer>&& vertexBuffer, std::vector<SubMesh>&& subMeshes):
        _subMeshes(std::move(subMeshes))
    {
        _vertexArray = CreateShared<VertexArray>();
        _vertexArray->AddVertexBuffer(std::move(vertexBuffer));
    }

    Mesh::~Mesh()
    {
    }
}
