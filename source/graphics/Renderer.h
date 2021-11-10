#pragma once

#include "Material.h"
#include "Mesh.h"
#include "RenderBatch.h"
#include "Texture.h"
#include "math/Transform.h"

namespace NDR
{
    /*
     * TODO: Make Renderer class static
    */
    class Renderer
    {
    public:
        Renderer();
        ~Renderer();
        
        void SetViewProj(const glm::mat4& viewProj);
        void Clear() const;

        void DrawMesh(const Mesh& mesh);

        void DrawElements(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader);
        void DrawElements(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Material& material);

        void DrawLine(const glm::vec3& start, const glm::vec3& end, const glm::vec4& color = glm::vec4(1.0f));
        
        void DrawQuad(const Transform& transform, const glm::vec4& color = glm::vec4(1.0f));
        void DrawQuad(const Transform& transform, Texture2D& texture, const glm::vec4& color = glm::vec4(1.0f));
        void DrawQuad(const Transform& transform, Texture2DAtlas& textureAtlas, int32_t x, int32_t y, const glm::vec4& color = glm::vec4(1.0f));

        void Flush();
        
        void DrawBackground(const glm::vec4& color) const;
    private:
        glm::mat4 _viewProj;

        VertexArray _lineVertexArray;
        Shader _lineShader;

        RenderBatch _quadBatch;
    };
}
