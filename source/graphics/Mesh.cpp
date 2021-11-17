#include "ndrpch.h"
#include "Mesh.h"

namespace NDR
{
    SubMesh::SubMesh(IndexBuffer&& indexBuffer, Material&& mat):
        _indexBuffer(std::move(indexBuffer)),
        _material(std::move(mat))
    {
    }

    Mesh::Mesh()
    {
    }

    Mesh::Mesh(VertexBuffer&& vertexBuffer, std::vector<SubMesh>&& subMeshes):
        _vertexArray(std::move(vertexBuffer)),
        _subMeshes(std::move(subMeshes))
    {
    }

    Mesh::~Mesh()
    {
    }

    Mesh::Mesh(Mesh&& other) noexcept:
        _vertexArray(std::move(other._vertexArray)),
        _subMeshes(std::move(other._subMeshes))
    {
    }

    Mesh& Mesh::operator=(Mesh&& other) noexcept
    {
        if(*this != other)
        {
            _vertexArray = std::move(other._vertexArray);
            _subMeshes = std::move(other._subMeshes);
        }
        return *this;
    }

    bool Mesh::operator==(const Mesh& other) const { return GetVertexBuffer() == other.GetVertexBuffer(); }
    bool Mesh::operator!=(const Mesh& other) const { return !(*this == other); }
}
