#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

namespace NDR
{
    struct VertexAttribute
    {
    public:
        GLuint count;
        GLenum type;
        bool normalized;

        VertexAttribute() = default;
        VertexAttribute(GLuint count, GLenum type, bool normalized)
            : count(count),
              type(type),
              normalized(normalized)
        {
        }

        GLsizei GetStride() const;
    };

    struct VertexLayout
    {
    public:
        VertexLayout();
        ~VertexLayout();
        
        GLsizei Size() const;
        GLuint AttributeCount() const;
        VertexAttribute& operator[](GLuint index);
        VertexAttribute operator[](GLsizei index) const;
        void AddAttribute(const VertexAttribute& attribute);

    private:
        std::vector<VertexAttribute> _attributes;
        GLsizei _size = 0;
        GLuint _attributeCount = 0;
    };

    class VertexArray
    {
    public:
        //TODO: VertexArray(const char* file)
        VertexArray(const std::vector<GLfloat>& verts, const VertexLayout& layout);
        ~VertexArray();

        void Bind() const;
    private:
        GLuint _vao = 0;
        GLuint _vbo = 0;
    };

    class IndexBuffer
    {
    public:
        IndexBuffer(const std::vector<GLuint>& indices);
        ~IndexBuffer();

        GLsizei Count() const;
        void Bind() const;
    private:
        GLuint _ibo = 0;
        GLuint _count = 0;
    };
}