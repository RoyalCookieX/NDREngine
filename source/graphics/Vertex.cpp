#include "Vertex.h"

#include "core/Error.h"

namespace NDR
{
    GLuint VertexAttribute::GetCount() const { return _count; }
    GLenum VertexAttribute::GetType() const { return _type; }
    bool VertexAttribute::IsNormalized() const { return _normalized; }
    GLsizei VertexAttribute::GetStride() const { return GetTypeSize() * _count; }

    GLuint VertexAttribute::GetTypeSize() const
    {
        switch (_type)
        {
            case GL_FLOAT:          return sizeof(GLfloat);
            case GL_INT:            return sizeof(GLint); 
            case GL_UNSIGNED_INT:   return sizeof(GLuint);
            case GL_BYTE:           return sizeof(GLbyte);
            default:                return 0;
        }
    }

    IndexBuffer::IndexBuffer(const std::vector<GLuint>& indices)
    {
        _count = (GLuint)indices.size();
        
        GLCall(glGenBuffers(1, &_ibo));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW));
    }

    IndexBuffer::~IndexBuffer() { GLCall(glDeleteBuffers(1, &_ibo)); }
    GLsizei IndexBuffer::Count() const { return _count; }
    void IndexBuffer::Bind() const { GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo)); }

    VertexLayout::VertexLayout() { }
    VertexLayout::~VertexLayout() { }
    GLsizei VertexLayout::Size() const { return _size; }
    GLuint VertexLayout::AttributeCount() const { return _attributeCount; }
    VertexAttribute& VertexLayout::operator[](GLuint index) { return _attributes[index]; }
    VertexAttribute VertexLayout::operator[](GLsizei index) const { return _attributes[index]; }
    void VertexLayout::AddAttribute(const VertexAttribute& attribute)
    {
        _attributes.push_back(attribute);
        _size += attribute.GetStride();
        _attributeCount++;
    }

    VertexArray::VertexArray(const std::vector<GLfloat>& verts, const VertexLayout& layout)
    {
        // generate vertex array object
        GLCall(glGenVertexArrays(1, &_vao));
        GLCall(glBindVertexArray(_vao));

        // generate vertex buffer object
        GLCall(glGenBuffers(1, &_vbo));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, _vbo));
        GLCall(glBufferData(GL_ARRAY_BUFFER, verts.size() * layout.Size(), verts.data(), GL_STATIC_DRAW));

        // setup vertex array attributes
        GLuint offset = 0;
        for(GLuint i = 0; i < layout.AttributeCount(); i++)
        {
            const VertexAttribute attribute = layout[i];
            GLCall(glEnableVertexAttribArray(i));
            GLCall(glVertexAttribPointer(i, attribute.GetCount(), attribute.GetType(), attribute.IsNormalized(), layout.Size(), (const void*)(offset)));
            offset += attribute.GetStride();
        }
    }

    VertexArray::~VertexArray()
    {
        GLCall(glDeleteBuffers(1, &_vbo));
        GLCall(glDeleteVertexArrays(1, &_vao));
    }

    void VertexArray::Bind() const
    {
        GLCall(glBindVertexArray(_vao));
    }
}
