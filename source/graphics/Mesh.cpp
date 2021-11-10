#include "ndrpch.h"
#include "Mesh.h"

namespace NDR
{
    SubMesh::SubMesh(IndexBuffer&& indexBuffer, Material&& mat):
        _ib(std::move(indexBuffer)),
        _mat(std::move(mat))
    {
    }

    IndexBuffer& SubMesh::GetIndexBuffer() { return _ib; }
    const IndexBuffer& SubMesh::GetIndexBuffer() const { return _ib; }
    Material& SubMesh::GetMaterial() { return _mat; }
    const Material& SubMesh::GetMaterial() const { return _mat; }

    Mesh::Mesh()
    {
    }

    Mesh::Mesh(VertexBuffer&& vertexBuffer, std::vector<SubMesh>&& subMeshes):
        _va(std::move(vertexBuffer)),
        _subMeshes(std::move(subMeshes))
    {
    }

    Mesh::~Mesh()
    {
    }

    Mesh::Mesh(Mesh&& other) noexcept:
        _va(std::move(other._va)),
        _subMeshes(std::move(other._subMeshes))
    {
    }

    Mesh& Mesh::operator=(Mesh&& other) noexcept
    {
        if(*this != other)
        {
            _va = std::move(other._va);
            _subMeshes = std::move(other._subMeshes);
        }
        return *this;
    }

    bool Mesh::operator==(const Mesh& other) const { return GetVertexBuffer() == other.GetVertexBuffer(); }
    bool Mesh::operator!=(const Mesh& other) const { return !(*this == other); }

    const VertexArray& Mesh::GetVertexArray() const { return _va; }
    VertexBuffer& Mesh::GetVertexBuffer() { return _va.GetVertexBuffer(); }
    const VertexBuffer& Mesh::GetVertexBuffer() const { return _va.GetVertexBuffer(); }
    SubMesh& Mesh::GetSubMesh(int32_t index) { return _subMeshes[index]; }
    const SubMesh& Mesh::GetSubMesh(int32_t index) const { return _subMeshes[index]; }
    IndexBuffer& Mesh::GetIndexBuffer(int32_t index) { return GetSubMesh(index).GetIndexBuffer(); }
    const IndexBuffer& Mesh::GetIndexBuffer(int32_t index) const { return GetSubMesh(index).GetIndexBuffer(); }
    Material& Mesh::GetMaterial(int32_t index) { return GetSubMesh(index).GetMaterial(); }
    const Material& Mesh::GetMaterial(int32_t index) const { return GetSubMesh(index).GetMaterial(); }
    uint32_t Mesh::GetSubMeshCount() const { return _subMeshes.size(); }
}
