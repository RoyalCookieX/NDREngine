#pragma once
#include "Vertex.h"
#include "Material.h"

namespace NDR
{
    struct SubMesh
    {
    public:
        SubMesh(IndexBuffer&& indexBuffer, Material&& mat);

        IndexBuffer& GetIndexBuffer();
        const IndexBuffer& GetIndexBuffer() const;
        Material& GetMaterial();
        const Material& GetMaterial() const;
    private:
        IndexBuffer _ib;
        Material _mat;
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

        const VertexArray& GetVertexArray() const;
        VertexBuffer& GetVertexBuffer();
        const VertexBuffer& GetVertexBuffer() const;
        SubMesh& GetSubMesh(int32_t index);
        const SubMesh& GetSubMesh(int32_t index) const;
        IndexBuffer& GetIndexBuffer(int32_t index);
        const IndexBuffer& GetIndexBuffer(int32_t index) const;
        Material& GetMaterial(int32_t index);
        const Material& GetMaterial(int32_t index) const;
        uint32_t GetSubMeshCount() const;
    private:
        VertexArray _va;
        std::vector<SubMesh> _subMeshes;
    };
}
