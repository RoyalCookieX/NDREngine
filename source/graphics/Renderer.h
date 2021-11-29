#pragma once
#include "Buffer.h"
#include "Material.h"
#include "Mesh.h"
#include "Vertex.h"
#include "math/Transform.h"

namespace NDR
{
    class Renderer
    {
    public:
        static void Initialize();
        static void Shutdown();
        
        static void Clear();
        static void SetViewProjection(const glm::mat4& view, const glm::mat4& projection);
        static void DrawLine(const glm::vec3& start, const glm::vec3& end, const glm::vec4& color = glm::vec4(1.0f), float width = 1.0f);
        static void DrawTriangles(const SharedPtr<VertexArray>& vertexArray, const SharedPtr<Material>& material);
        static void DrawTriangles(const SharedPtr<VertexArray>& vertexArray, const SharedPtr<IndexBuffer>& indexBuffer, const SharedPtr<Material>& material);
        static void DrawMesh(const SharedPtr<Mesh>& mesh, const Transform& transform);
        static void DrawBackground(const glm::vec4& color);
    };
}
