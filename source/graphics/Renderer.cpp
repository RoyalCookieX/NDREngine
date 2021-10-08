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
        layout.AddAttribute({3, false});
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
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        _batch = RenderBatch(maxQuads);
    }

    Renderer::~Renderer() { }

    void Renderer::Clear() const { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

    // void Renderer::DrawQuad(const Transform& transform)
    // {
    //     if(_batch.IsBatchFull())
    //     {
    //         //printf("batch full\n");
    //         Flush();
    //     }
    //
    //     const glm::vec3 v0(0.0f);
    //     const glm::vec3 v1(0.0f);
    //     const glm::vec3 v2(0.0f);
    //     const glm::vec3 v3(0.0f);
    //     
    //     const std::vector vertices
    //     {
    //         v0.x, v0.y, v0.z, 0.0f, 0.0f,
    //         v1.x, v1.y, v1.z, 1.0f, 0.0f,
    //         v2.x, v2.y, v2.z, 1.0f, 1.0f,
    //         v3.x, v3.y, v3.z, 0.0f, 1.0f,
    //     };
    //     _batch.AddQuad(vertices);
    // }

    void Renderer::DrawQuad(const glm::vec3& position, const glm::vec3& euler, const glm::vec3& scale)
    {
        if(_batch.IsBatchFull())
            Flush();

        const glm::mat4 proj(glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, 0.01f, 10.0f));
        const glm::quat rotation(glm::radians(euler));
        const glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::toMat4(rotation)
            * glm::scale(glm::mat4(1.0f), scale);


        const glm::vec4 v0 = proj * transform * glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
        const glm::vec4 v1 = proj * transform * glm::vec4( 0.5f, -0.5f, 0.0f, 1.0f);
        const glm::vec4 v2 = proj * transform * glm::vec4( 0.5f,  0.5f, 0.0f, 1.0f);
        const glm::vec4 v3 = proj * transform * glm::vec4(-0.5f,  0.5f, 0.0f, 1.0f);

        const std::vector<float> vertices
        {
            v0.x, v0.y, 0.0f, 0.0f, 0.0f,
            v1.x, v1.y, 0.0f, 1.0f, 0.0f,
            v2.x, v2.y, 0.0f, 1.0f, 1.0f,
            v3.x, v3.y, 0.0f, 0.0f, 1.0f,
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
        //printf("batch count: %d\n", _batch.quadCount);
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
