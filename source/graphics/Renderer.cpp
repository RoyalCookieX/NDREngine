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
        //TODO: make maxTextureSlots dynamic
        maxTextureSlots(32)
    {
        layout.AddAttribute({2, false});
        layout.AddAttribute({2, false});

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

        shader = AssetManager::LoadShader("assets/shaders/Quad.shader");
        shader.Use();
        shader.SetInt("u_Texture", 0);
    }

    void RenderBatch::AddQuad(std::vector<float> vertices)
    {
        va.GetVertexBuffer().SetData(quadCount * 4 * layout.GetStride(), vertices);
        quadCount++;
        indicesCount += 6;
    }

    bool RenderBatch::IsBatchFull() const { return quadCount >= maxQuads; }
    
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
        fprintf( stderr, "GL CALLBACK: %s message = %s\n",
                 ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
                  message );
    }
#endif

    Renderer::Renderer(const uint32_t maxQuads):
        _viewProj(glm::mat4(1.0f)),
        _isActive(false)
    {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            printf("GLAD did not initalize!\n");
            glfwTerminate();
            return;
        }
#ifdef NDR_DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(MessageCallback, nullptr);
#endif
        glEnable(GL_DEPTH_TEST);

        _batch = RenderBatch(maxQuads);
    }

    Renderer::~Renderer() { }

    void Renderer::Clear() const { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

    void Renderer::DrawQuad(const Transform& transform)
    {
        if(_batch.IsBatchFull())
        {
            printf("batch full\n");
            Flush();
        }
        
        const glm::vec3 pos = transform.GetPosition();
        const float xPos = pos.x;
        const float yPos = pos.y;

        const glm::vec3 scale = transform.GetScale();
        const float xHalfScale = glm::abs(scale.x / 2.0f);
        const float yHalfScale = glm::abs(scale.y / 2.0f);
        
        const std::vector vertices
        {
            xPos - xHalfScale, yPos - yHalfScale, 0.0f, 0.0f,
            xPos + xHalfScale, yPos - yHalfScale, 1.0f, 0.0f,
            xPos + xHalfScale, yPos + yHalfScale, 1.0f, 1.0f,
            xPos - xHalfScale, yPos + yHalfScale, 0.0f, 1.0f,
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

        glDrawElements(GL_TRIANGLES, _batch.indicesCount, GL_UNSIGNED_INT, nullptr);
        printf("batch count: %d\n", _batch.quadCount);
        _batch.quadCount = 0;
        _batch.indicesCount = 0;
    }

    void Renderer::DrawBackground(const float r, const float g, const float b, const float a) const { glClearColor(r, g, b, a); }
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
        }
    }
}
