#include "ndrpch.h"
#include "Mesh.h"

namespace NDR
{
    Mesh::Mesh()
    {
    }
    
    Mesh::Mesh(VertexArray&& vertexArray, Shader&& shader):
        _vertexArray(std::move(vertexArray)),
        _shader(std::move(shader))
    {
    }

    Mesh::~Mesh()
    {
    }

    Mesh::Mesh(Mesh&& other) noexcept:
        _vertexArray(std::move(other._vertexArray)),
        _shader(std::move(other._shader))
    {
    }

    Mesh& Mesh::operator=(Mesh&& other) noexcept
    {
        if(*this != other)
        {
            _vertexArray = std::move(other._vertexArray);
            _shader = std::move(other._shader);
        }
        return *this;
    }

    bool Mesh::operator==(const Mesh& other) const
    {
        return
            GetVertexArray() == other.GetVertexArray() &&
            GetShader() == other.GetShader();
    }
    bool Mesh::operator!=(const Mesh& other) const { return !(*this == other); }

    const VertexArray& Mesh::GetVertexArray() const { return _vertexArray; }
    const Shader& Mesh::GetShader() const { return _shader; }
}