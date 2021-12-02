#pragma once
#include "Defines.h"
#include "Math/Transform.h"

namespace NDR
{
    class VertexArray;
    class IndexBuffer;
    class Material;
    class Mesh;
    
    class Renderer
    {
    public:
        static void Initialize();
        static void Shutdown();
        
        static void Clear();
        static void SetViewProjection(const glm::mat4& view, const glm::mat4& projection);
        static void DrawLine(const glm::vec3& start, const glm::vec3& end, const glm::vec4& color = glm::vec4(1.0f), float width = 1.0f);
        static void DrawTriangles(const SPointer<VertexArray>& vertexArray, const SPointer<Material>& material);
        static void DrawTriangles(const SPointer<VertexArray>& vertexArray, const SPointer<IndexBuffer>& indexBuffer, const SPointer<Material>& material);
        static void DrawMesh(const SPointer<Mesh>& mesh, const Transform& transform);
        static void DrawBackground(const glm::vec4& color);
    };
}
