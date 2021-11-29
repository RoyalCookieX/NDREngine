#pragma once
#include "Vertex.h"
#include "Material.h"

namespace NDR
{
    struct SubMesh
    {
    public:
        SubMesh(SharedPtr<IndexBuffer>&& indexBuffer, SharedPtr<Material>&& mat);

        SharedPtr<IndexBuffer>& GetIndexBuffer() { return _indexBuffer; }
        const SharedPtr<IndexBuffer>& GetIndexBuffer() const { return _indexBuffer; }
        SharedPtr<Material>& GetMaterial() { return _material; }
        const SharedPtr<Material>& GetMaterial() const { return  _material; }
    private:
        SharedPtr<IndexBuffer> _indexBuffer;
        SharedPtr<Material> _material;
    };
    
    class Mesh
    {
    public:
        Mesh(SharedPtr<VertexBuffer>&& vertexBuffer, std::vector<SubMesh>&& subMeshes);
        ~Mesh();

        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;

        SharedPtr<VertexArray>& GetVertexArray() { return _vertexArray; }
        const SharedPtr<VertexArray>& GetVertexArray() const { return _vertexArray; }
        SharedPtr<VertexBuffer>& GetVertexBuffer() { return _vertexArray->GetVertexBuffer(0); }
        const SharedPtr<VertexBuffer>& GetVertexBuffer() const { return _vertexArray->GetVertexBuffer(0); }
        SubMesh& GetSubMesh(int32_t index) { return _subMeshes[index]; }
        const SubMesh& GetSubMesh(int32_t index) const { return _subMeshes[index]; }
        SharedPtr<IndexBuffer>& GetIndexBuffer(int32_t index) { return GetSubMesh(index).GetIndexBuffer(); }
        const SharedPtr<IndexBuffer>& GetIndexBuffer(int32_t index) const { return GetSubMesh(index).GetIndexBuffer(); }
        SharedPtr<Material>& GetMaterial(int32_t index) { return GetSubMesh(index).GetMaterial(); }
        const SharedPtr<Material>& GetMaterial(int32_t index) const { return GetSubMesh(index).GetMaterial(); }
        uint32_t GetSubMeshCount() const { return (uint32_t)_subMeshes.size(); }
    private:
        SharedPtr<VertexArray> _vertexArray;
        std::vector<SubMesh> _subMeshes;
    };
}
