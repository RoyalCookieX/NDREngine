#include "ndrpch.h"
#include "Renderer.h"

#include "utility/AssetManager.h"

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
        maxIndices(maxQuads * 6),
        //TODO: Make maxTextureSlots dynamic
        maxTextureSlots(32)
    {
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

        whiteTexture = Texture({64, 64, 4});

        shader = AssetManager::LoadShader("assets/shaders/Quad.shader");
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

    void RenderBatch::Reset()
    {
        quadCount = 0;
        indicesCount = 0;
        boundTextures.clear();
        boundSlots.clear();
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

    void Renderer::DrawQuad(const Transform& t, const glm::vec4& color) { DrawQuad(t, _batch.whiteTexture, color); }
    void Renderer::DrawQuad(const Transform& t, Texture& texture, const glm::vec4& color)
    {
        if(_batch.IsBatchFull())
        {
            Flush();
        }

        const glm::vec4 v0 = _viewProj * t.GetMatrix() * glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
        const glm::vec4 v1 = _viewProj * t.GetMatrix() * glm::vec4( 0.5f, -0.5f, 0.0f, 1.0f);
        const glm::vec4 v2 = _viewProj * t.GetMatrix() * glm::vec4( 0.5f,  0.5f, 0.0f, 1.0f);
        const glm::vec4 v3 = _viewProj * t.GetMatrix() * glm::vec4(-0.5f,  0.5f, 0.0f, 1.0f);

        float texIndex;
        auto it = _batch.boundTextures.find(&texture);
        if(it != _batch.boundTextures.end())
        {
            _batch.boundSlots.push_back(it->second);
            texIndex = (float)it->second;
        }
        else
        {
            int32_t newIndex = (int32_t)_batch.boundTextures.size();
            _batch.boundTextures.insert(std::make_pair(&texture, newIndex));
            _batch.boundSlots.push_back(newIndex);
            texIndex = (float)newIndex;
        }
        
        const std::vector<float> vertices
        {
            v0.x, v0.y, v0.z, color.r, color.g, color.b, color.a, 0.0f, 0.0f, texIndex,
            v1.x, v1.y, v1.z, color.r, color.g, color.b, color.a, 1.0f, 0.0f, texIndex,
            v2.x, v2.y, v2.z, color.r, color.g, color.b, color.a, 1.0f, 1.0f, texIndex,
            v3.x, v3.y, v3.z, color.r, color.g, color.b, color.a, 0.0f, 1.0f, texIndex,
        };

        _batch.AddQuad(vertices);
    }

    void Renderer::Flush()
    {
        if(_batch.indicesCount <= 0)
            return;
        
        _batch.va.Bind();
        _batch.ib.Bind();
        _batch.shader.Use();

        std::memset(_batch.boundSlots.data(), 0, _batch.boundTextures.size());
        
        for(auto it = _batch.boundTextures.begin(); it != _batch.boundTextures.end(); ++it)
        {
            it->first->Bind(it->second);
            _batch.boundSlots.push_back(it->second);
        }
        _batch.shader.SetIntArray("u_Textures", _batch.boundSlots.data(), (uint32_t)_batch.boundSlots.size());

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
