#include "Mesh.h"

namespace NDR
{
    GLsizei VertexAttribute::GetStride() const
    {
        switch (type)
        {
            case GL_FLOAT: return           sizeof(GLfloat) * count;
            case GL_INT:   return           sizeof(GLint) * count;
            case GL_UNSIGNED_INT: return    sizeof(GLuint) * count;
            case GL_BYTE:  return           sizeof(GLbyte) * count;
            default: return 0;
        }
    }

    Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices)
        : _vertices(vertices),
          _indices(indices)
    {
        // std::vector<GLfloat> vertexData;
        // const size_t vertexDataSize = vertices.size() * sizeof(Vertex);
        // vertexData.reserve(vertexDataSize);
        // for (Vertex vertex : vertices)
        // {
        //     vertexData.push_back(vertex.position.x);
        //     vertexData.push_back(vertex.position.y);
        //     vertexData.push_back(vertex.position.z);
        //
        //     vertexData.push_back(vertex.color.r);
        //     vertexData.push_back(vertex.color.g);
        //     vertexData.push_back(vertex.color.b);
        //     vertexData.push_back(vertex.color.a);
        // }

        std::vector<GLfloat> vertPos;
        const size_t vertPosSize = vertices.size() * sizeof(float) * 3;
        vertPos.reserve(vertPosSize);
        
        std::vector<GLfloat> vertCol;
        const size_t vertColSize = vertices.size() * sizeof(float) * 4;
        vertCol.reserve(vertColSize);

        for(Vertex v : vertices)
        {
            vertPos.push_back(v.position.x);
            vertPos.push_back(v.position.y);
            vertPos.push_back(v.position.z);

            vertCol.push_back(v.color.r);
            vertCol.push_back(v.color.g);
            vertCol.push_back(v.color.b);
            vertCol.push_back(v.color.a);
        }

        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);

        _vbo = (GLuint*)alloca(2 * sizeof(GLuint));
        glGenBuffers(2, _vbo);
        
        glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, vertPosSize, vertPos.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, 0);

        glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
        glBufferData(GL_ARRAY_BUFFER, vertColSize, vertCol.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, 0);
        
        glGenBuffers(1, &_ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(GLuint), _indices.data(), GL_STATIC_DRAW);
    }

    Vertex::Vertex(const glm::vec3& position)
        : position(position),
          color(1.0f, 1.0f, 1.0f, 1.0f )
    {
    }

    Vertex::Vertex(const glm::vec3& position, const glm::vec4& color)
        : position(position),
          color(color)
    {
    }

    Mesh::~Mesh()
    {
        glDeleteBuffers(2, _vbo);
        glDeleteBuffers(1, &_ibo);
        glDeleteVertexArrays(1, &_vao);
    }

    const std::vector<Vertex>& Mesh::GetVertexData() const { return _vertices; }
    const std::vector<GLuint>& Mesh::GetIndexData() const { return _indices; }

    void Mesh::Bind() const
    {
        glBindVertexArray(_vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
    }

    void Mesh::Draw() const
    {
        Bind();
        glDrawElements(GL_TRIANGLES, (GLsizei)_indices.size(), GL_UNSIGNED_INT, nullptr);
    }
}
