#include "Mesh.h"

#include "core/Error.h"

namespace NDR
{
    Mesh::Mesh():
        _vao(0),
        _vbo(0),
        _ibo(0),
        _layout()
    {
    }

    Mesh::Mesh(const VertexData& vertexData, const IndexData& indexData, const VertexLayout& layout):
        _vao(0),
        _vbo(0),
        _ibo(0),
        _vertexData(vertexData),
        _indexData(indexData),
        _layout(layout)
    {
        // create vertex array object
        GLCall(glCreateVertexArrays(1, &_vao));
        GLCall(glBindVertexArray(_vao));

        // create vertex buffer object
        GLCall(glCreateBuffers(1, &_vbo));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, _vbo));
        GLCall(glBufferData(GL_ARRAY_BUFFER, _vertexData.GetBufferSize(), _vertexData.GetBuffer(), GL_STATIC_DRAW));

        // setup vertex attributes
        auto offset = 0;
        for(uint32_t attributeIndex = 0; attributeIndex < _layout.GetAttributeCount(); attributeIndex++)
        {
            VertexAttribute attribute = _layout[attributeIndex];
            GLCall(glEnableVertexAttribArray(attributeIndex));
            GLCall(glVertexAttribPointer(
                attributeIndex,
                attribute.GetCount(),
                GL_FLOAT,
                attribute.IsNormalized(),
                _layout.GetStride(),
                (const void*)offset));
            offset += attribute.GetStride();
        }

        // create index buffer object
        GLCall(glCreateBuffers(1, &_ibo));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexData.GetBufferSize(), _indexData.GetBuffer(), GL_STATIC_DRAW));
    }

    Mesh::~Mesh()
    {
        GLCall(glDeleteBuffers(1, &_ibo));
        GLCall(glDeleteBuffers(1, &_vbo));
        GLCall(glDeleteVertexArrays(1, &_vao));
    }

    uint32_t Mesh::GetIndexCount() const { return _indexData.GetCount(); }
    void Mesh::Bind() const
    {
        GLCall(glBindVertexArray(_vao));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo));
    }
}
