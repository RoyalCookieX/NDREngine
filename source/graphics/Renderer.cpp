#include "ndrpch.h"
#include "Renderer.h"

#include "Primitives.h"

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

    Renderer::Renderer(const uint32_t maxQuads):
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

        _batch.Initialize(maxQuads);
    }

    Renderer::~Renderer() { }

    void Renderer::Clear() const { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

    void Renderer::DrawElements(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
    {
        va.Bind();
        ib.Bind();
        shader.Use();
        glDrawElements(GL_TRIANGLES, ib.GetSize(), GL_UNSIGNED_INT, nullptr);
    }

    void Renderer::SetViewProj(const glm::mat4& viewProj) { _viewProj = viewProj; }

    void Renderer::BindTexture(const Texture& texture, uint32_t slot)
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, texture.GetTextureID());
    }

    void Renderer::DrawQuad(const Transform& transform, const glm::vec4& color) { DrawQuad(transform, _batch.GetDefaultTexture(), color); }
    void Renderer::DrawQuad(const Transform& transform, Texture2D& texture, const glm::vec4& color)
    {
        if(_batch.IsFull())
        {
            Flush();
        }

        const glm::mat4 mvp = _viewProj * transform.GetMatrix();
        const std::array<float, 8> uvs
        {
           0.0f, 0.0f,
           1.0f, 0.0f,
           1.0f, 1.0f,
           0.0f, 1.0f,
        };
        const float texIndex = _batch.GetTextureIndex(texture);
        const std::vector<float> vertices = CreateQuad(mvp, uvs, color, texIndex);

        _batch.AddElement(vertices);
    }

    void Renderer::DrawQuad(const Transform& transform, Texture2DAtlas& textureAtlas, const int32_t x, const int32_t y, const glm::vec4& color)
    {
        if(_batch.IsFull())
        {
            Flush();
        }

        const glm::mat4 mvp = _viewProj * transform.GetMatrix();
        const std::array<float, 8> uvs = textureAtlas.GetUVs(x, y);
        const float texIndex = _batch.GetTextureIndex(textureAtlas);
        const std::vector<float> vertices = CreateQuad(mvp, uvs, color, texIndex);

        _batch.AddElement(vertices);
    }

    void Renderer::Flush()
    {
        if(_batch.GetIndicesCount() <= 0)
            return;
        
        for(size_t i = 0; i < _batch.GetBoundTextureCount(); i++)
            BindTexture(_batch.GetBoundTexture(i), (uint32_t)i);
                
        DrawElements(_batch.GetVertexArray(), _batch.GetIndexBuffer(), _batch.GetDefaultShader());
        _batch.Reset();
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
