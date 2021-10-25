#pragma once
#include "Vertex.h"
#include "Shader.h"

namespace NDR
{
    class Mesh
    {
    public:
        Mesh();
        Mesh(VertexArray&& vertexArray, Shader&& shader);
        ~Mesh();

        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;

        Mesh(Mesh&& other) noexcept;
        Mesh& operator=(Mesh&& other) noexcept;

        bool operator==(const Mesh& other) const;
        bool operator!=(const Mesh& other) const;

        const VertexArray& GetVertexArray() const;
        const Shader& GetShader() const;

    private:
        VertexArray _vertexArray;
        Shader _shader;
    };
}
