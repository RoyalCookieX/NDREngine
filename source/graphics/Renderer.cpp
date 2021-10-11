#include "ndrpch.h"
#include "Renderer.h"

#include "utility/AssetManager.h"
#include "Primitives.h"

namespace NDR
{   
    RenderBatch::RenderBatch():
        quadCount(0),
        indicesCount(0),
        maxQuads(0),
        maxVertices(0),
        maxIndices(0),
        maxTextureSlots(0)
    {
    }

    RenderBatch::RenderBatch(uint32_t maxQuads):
        quadCount(0),
        indicesCount(0),
        maxQuads(maxQuads),
        maxVertices(maxQuads * 4),
        maxIndices(maxQuads * 6)
    {
        Reset();
        
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureSlots);
        for(int32_t i = 0; i < maxTextureSlots; i++)
            textureIndexes.push_back(i);
        
        layout.AddAttribute({3, false}); // position
        layout.AddAttribute({4, false}); // color
        layout.AddAttribute({2, false}); // texCoords
        layout.AddAttribute({1, false}); // texIndex

        VertexBuffer vb(maxVertices * layout.GetStride());

        va = VertexArray(std::move(vb), layout);

        std::vector<uint32_t> indices;
        indices.reserve(maxIndices);
        uint32_t index = 0;
        for (uint32_t i = 0; i < maxIndices; i += 6)
        {
            indices.push_back(index + 0);
            indices.push_back(index + 1);
            indices.push_back(index + 2);
            indices.push_back(index + 0);
            indices.push_back(index + 2);
            indices.push_back(index + 3);
            index += 4;
        }
        ib = IndexBuffer(indices);

        whiteTexture = Texture2D({4, 4, 4, TextureFilter::NEAREST});

        shader = LoadShader("assets/shaders/Quad.shader");
    }

    void RenderBatch::AddQuad(std::vector<float> vertices)
    {
        va.GetVertexBuffer().SetData(quadCount * 4 * layout.GetStride(), vertices);
        quadCount++;
        indicesCount += 6;
    }

    bool RenderBatch::IsBatchFull() const
    {
        return quadCount >= maxQuads || boundTextures.size() >= maxTextureSlots;
    }

    float RenderBatch::GetTextureIndex(const Texture& texture)
    {
        float texIndex = -1.0f;
        for(size_t i = 0; i < boundTextures.size(); i++)
        {
            if(boundTextures[i]->GetTextureID() == texture.GetTextureID())
            {
                texIndex = (float)i;
                break;
            }
        }
        if(texIndex == -1.0f)
        {
            const int32_t newIndex = (int32_t)boundTextures.size();
            boundTextures.push_back(&texture);
            texIndex = (float)newIndex;
        }
        return texIndex;
    }

    void RenderBatch::Reset()
    {
        quadCount = 0;
        indicesCount = 0;
        boundTextures.clear();

        textureIndexes.reserve(maxTextureSlots);
    }

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
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        _batch = RenderBatch(maxQuads);
    }

    Renderer::~Renderer() { }

    void Renderer::Clear() const { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

    void Renderer::SetViewProj(const glm::mat4& viewProj) { _viewProj = viewProj; }

    void Renderer::BindTexture(const Texture& texture, uint32_t slot)
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, texture.GetTextureID());
    }

    void Renderer::DrawQuad(const Transform& transform, const glm::vec4& color) { DrawQuad(transform, _batch.whiteTexture, color); }
    void Renderer::DrawQuad(const Transform& transform, Texture2D& texture, const glm::vec4& color)
    {
        if(_batch.IsBatchFull())
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

        _batch.AddQuad(vertices);
    }

    void Renderer::DrawQuad(const Transform& transform, Texture2DAtlas& textureAtlas, const int32_t x, const int32_t y, const glm::vec4& color)
    {
        if(_batch.IsBatchFull())
        {
            Flush();
        }

        const glm::mat4 mvp = _viewProj * transform.GetMatrix();
        const std::array<float, 8> uvs = textureAtlas.GetUVs(x, y);
        const float texIndex = _batch.GetTextureIndex(textureAtlas);
        const std::vector<float> vertices = CreateQuad(mvp, uvs, color, texIndex);

        _batch.AddQuad(vertices);
    }

    void Renderer::Flush()
    {
        if(_batch.indicesCount <= 0)
            return;
        
        _batch.va.Bind();
        _batch.ib.Bind();
        _batch.shader.Use();
        
        for(size_t i = 0; i < _batch.boundTextures.size(); i++)
            BindTexture(*_batch.boundTextures[i], (uint32_t)i);
        
        _batch.shader.SetIntArray("u_Textures", _batch.textureIndexes.data(), (uint32_t)_batch.textureIndexes.size());
        
        glDrawElements(GL_TRIANGLES, _batch.indicesCount, GL_UNSIGNED_INT, nullptr);
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
