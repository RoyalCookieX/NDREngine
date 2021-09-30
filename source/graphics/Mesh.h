#pragma once
#include "Buffer.h"
#include "Shader.h"
#include "Vertex.h"

namespace NDR
{
    class Mesh
    {
    public:
        Mesh();
        Mesh(VertexArray&& vertexArray, IndexBuffer&& indexBuffer, Shader&& shader);
        ~Mesh();

        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;

        Mesh(Mesh&& other) noexcept;
        Mesh& operator=(Mesh&& other) noexcept;

        const VertexArray& GetVertexArray() const;
        const IndexBuffer& GetIndexBuffer() const;
        const Shader& GetShader() const;

    private:
        VertexArray _vertexArray;
        IndexBuffer _indexBuffer;
        Shader _shader;
    };

    extern bool operator==(const Mesh& left, const Mesh& right);
    extern bool operator!=(const Mesh& left, const Mesh& right);
}
