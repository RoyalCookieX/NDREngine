#include "ndrpch.h"
#include "Mesh.h"

namespace NDR
{
    SubMesh::SubMesh(SharedPtr<IndexBuffer>&& indexBuffer, SharedPtr<Material>&& mat):
        _indexBuffer(std::move(indexBuffer)),
        _material(std::move(mat))
    {
    }

    Mesh::Mesh(SharedPtr<VertexBuffer>&& vertexBuffer, std::vector<SubMesh>&& subMeshes):
        _subMeshes(std::move(subMeshes))
    {
        _vertexArray = CreateSharedPtr<VertexArray>();
        _vertexArray->AddVertexBuffer(std::move(vertexBuffer));
    }

    Mesh::~Mesh()
    {
    }
}
