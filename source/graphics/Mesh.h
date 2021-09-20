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

    class Vertex
    {
    public:
        glm::vec3 position;
        glm::vec4 color;

        Vertex(const glm::vec3& position);
        Vertex(const glm::vec3& position, const glm::vec4& color);
    };

    class Mesh
    {
    public:
        Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices);
        ~Mesh();
        
        const std::vector<Vertex>& GetVertexData() const;
        const std::vector<GLuint>& GetIndexData() const;
        void Bind() const;
        void Draw() const;
    private:
        GLuint  _vao;
        GLuint* _vbo = nullptr;
        GLuint  _ibo;

        std::vector<Vertex> _vertices;
        std::vector<GLuint> _indices;
    };
}