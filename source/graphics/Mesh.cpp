#include "ndrpch.h"
#include "Mesh.h"

namespace NDR
{
    Mesh::Mesh()
    {
    }
    
    Mesh::Mesh(VertexArray&& vertexArray, IndexBuffer&& indexBuffer, Shader&& shader):
        _vertexArray(std::move(vertexArray)),
        _indexBuffer(std::move(indexBuffer)),
        _shader(std::move(shader))
    {
        _vertexArray.Bind();
        _indexBuffer.Bind();
    }

    Mesh::~Mesh()
    {
    }

    Mesh::Mesh(Mesh&& other) noexcept:
        _vertexArray(std::move(other._vertexArray)),
        _indexBuffer(std::move(other._indexBuffer)),
        _shader(std::move(other._shader))
    {
    }

    Mesh& Mesh::operator=(Mesh&& other) noexcept
    {
        if(*this != other)
        {
            _vertexArray = std::move(other._vertexArray);
            _indexBuffer = std::move(other._indexBuffer);
            _shader = std::move(other._shader);
        }
        return *this;
    }

    const VertexArray& Mesh::GetVertexArray() const { return _vertexArray; }
    const IndexBuffer& Mesh::GetIndexBuffer() const { return _indexBuffer; }
    const Shader& Mesh::GetShader() const { return _shader; }

    bool operator==(const Mesh& left, const Mesh& right)
    {
        return
            left.GetVertexArray() == right.GetVertexArray() &&
            left.GetIndexBuffer() == right.GetIndexBuffer() &&
            left.GetShader() == right.GetShader();
    }
    bool operator!=(const Mesh& left, const Mesh& right) { return !(left == right); }
}