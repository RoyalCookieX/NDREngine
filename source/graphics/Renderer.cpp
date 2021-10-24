#include "ndrpch.h"
#include "Renderer.h"

#include "Primitives.h"
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
        if(type == GL_DEBUG_TYPE_OTHER) return;
        fprintf( stderr, "[OpenGL%s]: %s\n",
            type == GL_DEBUG_TYPE_ERROR ? " Error" : "",
            message );
    }
#endif

    Renderer::Renderer():
        _viewProj(glm::mat4(1.0f))
    {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            printf("GLAD did not initialize!\n");
            glfwTerminate();
            return;
        }
#ifdef NDR_DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(MessageCallback, nullptr);
#endif
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        VertexLayout quadLayout;
        quadLayout.AddAttribute({4, false}); // position
        quadLayout.AddAttribute({4, false}); // color
        quadLayout.AddAttribute({2, false}); // texCoords
        quadLayout.AddAttribute({1, false}); // texIndex
        _quadBatch = RenderBatch(1024, 4, 6, quadLayout, Texture2D({1, 1, 1}), LoadShader("assets/shaders/Quad.shader", AssetRoot::ENGINE));
        
        VertexLayout lineLayout;
        lineLayout.AddAttribute({4, false}); // position
        lineLayout.AddAttribute({4, false}); // color
        VertexBuffer linevb(2 * lineLayout.GetAttributeComponentCount(), lineLayout);
        _lineVertexArray = VertexArray(std::move(linevb), IndexBuffer());
        _lineShader = LoadShader("assets/shaders/Line.shader", AssetRoot::ENGINE);
    }

    Renderer::~Renderer() { }

    void Renderer::Clear() const { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

    void Renderer::DrawElements(const VertexArray& va, const Shader& shader)
    {
        va.Bind();
        shader.Use();
        glDrawElements(GL_TRIANGLES, (GLsizei)va.GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr);
    }

    void Renderer::SetViewProj(const glm::mat4& viewProj) { _viewProj = viewProj; }

    void Renderer::DrawLine(const glm::vec3& start, const glm::vec3& end, const glm::vec4& color)
    {
        const glm::vec3 displacement = (end - start);
        const glm::vec3 dir = glm::normalize(displacement);
        const float scale = glm::length(displacement);
        const glm::quat rot = glm::rotation(VEC3_RIGHT, dir);
        
        const glm::mat4 mvp = _viewProj
            * glm::translate(start)
            * glm::toMat4(rot)
            * glm::scale(glm::vec3(scale))
        ;
        
        const std::vector<float> vertices = CreateLine(mvp, color);

        _lineVertexArray.GetVertexBuffer().SetData(0, vertices);
        _lineVertexArray.Bind();
        _lineShader.Use();
        
        glDrawArrays(GL_LINES, 0, (GLsizei)vertices.size());
    }

    void Renderer::DrawQuad(const Transform& transform, const glm::vec4& color) { DrawQuad(transform, _quadBatch.GetDefaultTexture(), color); }
    void Renderer::DrawQuad(const Transform& transform, Texture2D& texture, const glm::vec4& color)
    {
        if(_quadBatch.IsFull())
        {
            Flush();
        }
        
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
        {
            Flush();
        }
        
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

        _quadBatch.GetDefaultShader().Use();
        _quadBatch.GetDefaultShader().SetMat4("u_ViewProj", _viewProj);
                
        DrawElements(_quadBatch.GetVertexArray(), _quadBatch.GetDefaultShader());
        _quadBatch.Reset();
    }

    void Renderer::DrawBackground(const glm::vec4& color) const { glClearColor(color.r, color.g, color.b, color.a); }
    void Renderer::SetBlendMode(const BlendMode& blendMode) const
    {
        switch (blendMode)
        {
        case BlendMode::OPAQUE:
            {
                glDisable(GL_BLEND);
                break;
            }
        case BlendMode::TRANSPARENT:
            {
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                break;
            }
        default: break;
        }
    }
}
