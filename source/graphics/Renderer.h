#pragma once
#include "Buffer.h"
#include "Material.h"
#include "Vertex.h"

namespace NDR
{
    class Renderer
    {
    public:
        static void Initialize();
        static void Shutdown();
        
        static void Clear();
        static void DrawLine(const glm::vec3& start, const glm::vec3& end, const glm::vec4& color);
        static void DrawTriangles(const VertexArray& vertexArray, const Material& material);
        static void DrawTriangles(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Material& material);
        static void DrawBackground(const glm::vec4& color);
    };
}
