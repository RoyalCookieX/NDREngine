#include "ndrpch.h"
#include "Renderer.h"

#include "Primitives.h"
#include "core/Log.h"
#include "utility/AssetManager.h"

namespace NDR
{   
#ifdef NDR_DEBUG
    // from https://www.khronos.org/opengl/wiki/OpenGL_Error
    inline void
    MessageCallback( GLenum source,
                     GLenum type,
                     GLuint id,
                     GLenum severity,
                     GLsizei length,
                     const GLchar* message,
                     const void* userParam )
    {
        switch (type)
        {
            case GL_DEBUG_TYPE_OTHER: break;
            case GL_DEBUG_TYPE_ERROR: NDR_LOGERROR("[Renderer]: %s", message); break;
            default: NDR_LOGINFO("[Renderer]: %s", message); break;
        }
    }
#endif

    Renderer::Renderer():
        _viewProj(glm::mat4(1.0f))
    {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            NDR_LOGFATAL("[GLAD] GLAD did not initialize!\n");
            return;
        }
#ifdef NDR_DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(MessageCallback, nullptr);
#endif
        // Depth Testing
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        VertexLayout quadLayout;
        quadLayout.AddAttribute({3, false}); // position
        quadLayout.AddAttribute({4, false}); // color
        quadLayout.AddAttribute({2, false}); // texCoords
        quadLayout.AddAttribute({1, false}); // texIndex
        _quadBatch = RenderBatch(1024, 4, 6, quadLayout, Texture2D({1, 1, 1}), LoadShader("assets/shaders/Quad.shader", AssetRoot::ENGINE));
        
        VertexLayout lineLayout;
        lineLayout.AddAttribute({3, false}); // position
        lineLayout.AddAttribute({4, false}); // color
        VertexBuffer linevb(2 * lineLayout.GetAttributeComponentCount(), lineLayout);
        _lineVertexArray = VertexArray(std::move(linevb));
        _lineShader = LoadShader("assets/shaders/Line.shader", AssetRoot::ENGINE);
    }

    Renderer::~Renderer() { }

    void Renderer::Clear() const { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

    void Renderer::DrawMesh(const Mesh& mesh)
    {
        mesh.GetVertexArray().Bind();
        for(uint32_t i = 0; i < mesh.GetSubMeshCount(); i++)
        {
            mesh.GetIndexBuffer(i).Bind();
            mesh.GetMaterial(i).Use();
            glDrawElements(GL_TRIANGLES, (GLsizei)mesh.GetIndexBuffer(i).GetCount(), GL_UNSIGNED_INT, nullptr);
        }
    }

    void Renderer::DrawElements(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader)
    {
        vertexArray.Bind();
        indexBuffer.Bind();
        shader.Use();
        glDrawElements(GL_TRIANGLES, (GLsizei)indexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr);
    }

    void Renderer::DrawElements(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Material& material)
    {
        DrawElements(vertexArray, indexBuffer, material.GetShader());
    }

    void Renderer::SetViewProj(const glm::mat4& viewProj)
    {
        _viewProj = viewProj;
        //TODO: Create Uniform Buffer Class
        _quadBatch.GetDefaultShader().Use();
        _quadBatch.GetDefaultShader().SetMat4("u_ViewProj", _viewProj);
        _lineShader.Use();
        _lineShader.SetMat4("u_ViewProj", _viewProj);
    }

    void Renderer::DrawLine(const glm::vec3& start, const glm::vec3& end, const glm::vec4& color)
    {        
        const std::vector<float> vertices = CreateLine(start, end, color);

        _lineVertexArray.GetVertexBuffer().SetData(0, vertices);
        _lineVertexArray.Bind();
        _lineShader.Use();
        
        glDrawArrays(GL_LINES, 0, (GLsizei)vertices.size());
    }

    void Renderer::DrawQuad(const Transform& transform, const glm::vec4& color) { DrawQuad(transform, _quadBatch.GetDefaultTexture(), color); }
    void Renderer::DrawQuad(const Transform& transform, Texture2D& texture, const glm::vec4& color)
    {
        if(_quadBatch.IsFull())
            Flush();
        
        const std::array<float, 8> uvs
        {
           0.0f, 0.0f,
           1.0f, 0.0f,
           1.0f, 1.0f,
           0.0f, 1.0f,
        };
        const float texIndex = _quadBatch.GetTextureIndex(texture);
        const std::vector<float> vertices = CreateQuad(transform.GetMatrix(), uvs, color, texIndex);

        _quadBatch.AddElement(vertices);
    }

    void Renderer::DrawQuad(const Transform& transform, Texture2DAtlas& textureAtlas, const int32_t x, const int32_t y, const glm::vec4& color)
    {
        if(_quadBatch.IsFull())
            Flush();
        
        const std::array<float, 8> uvs = textureAtlas.GetUVs(x, y);
        const float texIndex = _quadBatch.GetTextureIndex(textureAtlas);
        const std::vector<float> vertices = CreateQuad(transform.GetMatrix(), uvs, color, texIndex);

        _quadBatch.AddElement(vertices);
    }

    void Renderer::Flush()
    {
        if(_quadBatch.GetIndicesCount() <= 0)
            return;
        
        for(uint32_t i = 0; i < _quadBatch.GetBoundTextureCount(); i++)
            _quadBatch.GetBoundTexture(i).Bind(i);
    
        DrawElements(_quadBatch.GetVertexArray(), _quadBatch.GetIndexBuffer(), _quadBatch.GetDefaultShader());
        _quadBatch.Reset();
    }

    void Renderer::DrawBackground(const glm::vec4& color) const { glClearColor(color.r, color.g, color.b, color.a); }
}
