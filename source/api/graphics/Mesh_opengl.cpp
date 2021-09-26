#include "ndrpch.h"
#include "Mesh_opengl.h"

namespace NDR
{
    Mesh* Mesh::Create(const VertexData& vertices, const IndexData& indices, const VertexLayout& layout)
    {
        return new GraphicsAPI::Mesh_opengl(vertices, indices, layout);
    }
namespace GraphicsAPI
{
    Mesh_opengl::Mesh_opengl(const VertexData& vertices, const IndexData& indices, const VertexLayout& layout):
        _vao(0),
        _vbo(0),
        _ibo(0),
        _vertexData(vertices),
        _indexData(indices),
        _layout(layout)
    {
        // create vertex array object
        glCreateVertexArrays(1, &_vao);
        glBindVertexArray(_vao);

        // create vertex buffer object
        glCreateBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, _vertexData.GetBufferSize(), _vertexData.GetBuffer(), GL_STATIC_DRAW);

        // setup vertex attributes
        auto offset = 0;
        for(uint32_t attributeIndex = 0; attributeIndex < _layout.GetAttributeCount(); attributeIndex++)
        {
            VertexAttribute attribute = _layout[attributeIndex];
            glEnableVertexAttribArray(attributeIndex);
            glVertexAttribPointer(
                attributeIndex,
                attribute.GetCount(),
                GL_FLOAT,
                attribute.IsNormalized(),
                _layout.GetStride(),
                (const void*)offset);
            offset += attribute.GetStride();
        }

        // create index buffer object
        glCreateBuffers(1, &_ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexData.GetBufferSize(), _indexData.GetBuffer(), GL_STATIC_DRAW);
    }

    Mesh_opengl::~Mesh_opengl()
    {
        glDeleteBuffers(1, &_ibo);
        glDeleteBuffers(1, &_vbo);
        glDeleteVertexArrays(1, &_vao);
    }

    uint32_t Mesh_opengl::GetVertexCount() const { return _vertexData.GetCount(); }
    uint32_t Mesh_opengl::GetIndexCount() const { return _indexData.GetCount(); }
    void Mesh_opengl::Bind() const
    {
        glBindVertexArray(_vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
    }
}
}
