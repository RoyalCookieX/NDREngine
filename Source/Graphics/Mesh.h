#pragma once
#include "Defines.h"
#include "Vertex.h"

namespace NDR
{
    class VertexBuffer;
    class IndexBuffer;
    class VertexArray;
    class Material;
    
    struct SubMesh
    {
    public:
        SubMesh(SPointer<IndexBuffer>&& indexBuffer, SPointer<Material>&& mat);

        SPointer<IndexBuffer>& GetIndexBuffer() { return _indexBuffer; }
        const SPointer<IndexBuffer>& GetIndexBuffer() const { return _indexBuffer; }
        SPointer<Material>& GetMaterial() { return _material; }
        const SPointer<Material>& GetMaterial() const { return  _material; }
    private:
        SPointer<IndexBuffer> _indexBuffer;
        SPointer<Material> _material;
    };
    
    class Mesh
    {
    public:
        Mesh(SPointer<VertexBuffer>&& vertexBuffer, std::vector<SubMesh>&& subMeshes);
        ~Mesh();

        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;

        SPointer<VertexArray>& GetVertexArray() { return _vertexArray; }
        const SPointer<VertexArray>& GetVertexArray() const { return _vertexArray; }
        SPointer<VertexBuffer>& GetVertexBuffer() { return _vertexArray->GetVertexBuffer(0); }
        const SPointer<VertexBuffer>& GetVertexBuffer() const { return _vertexArray->GetVertexBuffer(0); }
        SubMesh& GetSubMesh(Int32 index) { return _subMeshes[index]; }
        const SubMesh& GetSubMesh(Int32 index) const { return _subMeshes[index]; }
        SPointer<IndexBuffer>& GetIndexBuffer(Int32 index) { return GetSubMesh(index).GetIndexBuffer(); }
        const SPointer<IndexBuffer>& GetIndexBuffer(Int32 index) const { return GetSubMesh(index).GetIndexBuffer(); }
        SPointer<Material>& GetMaterial(Int32 index) { return GetSubMesh(index).GetMaterial(); }
        const SPointer<Material>& GetMaterial(Int32 index) const { return GetSubMesh(index).GetMaterial(); }
        UInt32 GetSubMeshCount() const { return (UInt32)_subMeshes.size(); }
    private:
        SPointer<VertexArray> _vertexArray;
        std::vector<SubMesh> _subMeshes;
    };
}
