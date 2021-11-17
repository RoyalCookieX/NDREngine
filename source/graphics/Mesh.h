#pragma once
#include "Vertex.h"
#include "Material.h"

namespace NDR
{
    struct SubMesh
    {
    public:
        SubMesh(IndexBuffer&& indexBuffer, Material&& mat);

        IndexBuffer& GetIndexBuffer() { return _indexBuffer; }
        const IndexBuffer& GetIndexBuffer() const { return _indexBuffer; }
        Material& GetMaterial() { return _material; }
        const Material& GetMaterial() const { return  _material; }
    private:
        IndexBuffer _indexBuffer;
        Material _material;
    };
    
    class Mesh
    {
    public:
        Mesh();
        Mesh(VertexBuffer&& vertexBuffer, std::vector<SubMesh>&& subMeshes);
        ~Mesh();

        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;

        Mesh(Mesh&& other) noexcept;
        Mesh& operator=(Mesh&& other) noexcept;

        bool operator==(const Mesh& other) const;
        bool operator!=(const Mesh& other) const;

        VertexArray& GetVertexArray() { return _vertexArray; }
        const VertexArray& GetVertexArray() const { return _vertexArray; }
        VertexBuffer& GetVertexBuffer() { return _vertexArray.GetVertexBuffer(); }
        const VertexBuffer& GetVertexBuffer() const { return _vertexArray.GetVertexBuffer(); }
        SubMesh& GetSubMesh(int32_t index) { return _subMeshes[index]; }
        const SubMesh& GetSubMesh(int32_t index) const { return _subMeshes[index]; }
        IndexBuffer& GetIndexBuffer(int32_t index) { return GetSubMesh(index).GetIndexBuffer(); }
        const IndexBuffer& GetIndexBuffer(int32_t index) const { return GetSubMesh(index).GetIndexBuffer(); }
        Material& GetMaterial(int32_t index) { return GetSubMesh(index).GetMaterial(); }
        const Material& GetMaterial(int32_t index) const { return GetSubMesh(index).GetMaterial(); }
        uint32_t GetSubMeshCount() const { return (uint32_t)_subMeshes.size(); }
    private:
        VertexArray _vertexArray;
        std::vector<SubMesh> _subMeshes;
    };
}
