#include "ndrpch.h"
#include "Renderer.h"

#include "core/Log.h"
#include "utility/AssetManager.h"

namespace NDR
{
#if NDR_DEBUG
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

    struct LineRendererData
    {
    public:
        void Initalize()
        {
            vertexArray = CreateSharedPtr<VertexArray>();
            shader = LoadShader("assets/shaders/Line.shader", AssetRoot::ENGINE);
        }
        
        SharedPtr<VertexArray> vertexArray;
        SharedPtr<Shader> shader;
    };

    static LineRendererData sLineRendererData;
    
    static void BindVertexBuffer(const SharedPtr<VertexBuffer>& vertexBuffer) { glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->GetRendererID()); }
    static void BindIndexBuffer(const SharedPtr<IndexBuffer>& indexBuffer) { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->GetRendererID()); }
    static void BindVertexArray(const SharedPtr<VertexArray>& vertexArray)
    {
        glBindVertexArray(vertexArray->GetRendererID());
        BindVertexBuffer(vertexArray->GetVertexBuffer(0));
    }
    static void BindShader(const SharedPtr<Shader>& shader) { glUseProgram(shader->GetRendererID()); }
    static void BindTexture(const SharedPtr<Texture>& texture, uint32_t slot = 0)
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, texture->GetRendererID());
    }
    static void BindMaterial(const SharedPtr<Material>& material)
    {
        // bind textures
        auto it = material->GetBoundTextures().begin();
        for(size_t i = 0; i < material->GetBoundTextures().size(); i++)
        {
            BindTexture(it->second, i);
            material->SetTexture(it->first, it->second);
            ++it;
        }
        
        // set material flags
        // cull face
        if(material->HasFlags(ENABLECULLING))
        {
            glEnable(GL_CULL_FACE);
            if(material->HasFlags(CULLBACK))
                glCullFace(GL_BACK);
            else if(material->HasFlags(CULLFRONT))
                glCullFace(GL_FRONT);
        }
        else glDisable(GL_CULL_FACE);

        // blending
        if(material->HasFlags(ENABLEBLENDING))
        {
            glEnable(GL_BLEND);
            if(material->HasFlags(OPAQUE))
                glDisable(GL_BLEND);
            else if(material->HasFlags(TRANSPARENT))
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
        else glDisable(GL_BLEND);

        BindShader(material->GetShader());
    }

    void Renderer::Initialize()
    {
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            NDR_LOGFATAL("[Renderer]: GLAD did not initalize!");
            return;
        }
#if NDR_DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(MessageCallback, nullptr);

        //TODO: Move to material flags
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        sLineRendererData.Initalize();
        VertexLayout lineLayout;
        lineLayout.AddAttribute({3, false}); // position
        lineLayout.AddAttribute({4, false}); // color
        SharedPtr<VertexBuffer> lineVertexBuffer = CreateSharedPtr<VertexBuffer>(lineLayout.GetAttributeComponentCount() * 2, lineLayout);
        sLineRendererData.vertexArray->AddVertexBuffer(std::move(lineVertexBuffer));
#endif
    }

    void Renderer::Shutdown()
    {
        
    }

    void Renderer::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::DrawLine(const glm::vec3& start, const glm::vec3& end, const glm::vec4& color)
    {
        std::vector<float> vertices
        {
            start.x, start.y, start.z, color.r, color.g, color.b, color.a,
            end.x,   end.y,   end.z,   color.r, color.g, color.b, color.a,
        };
        BindVertexArray(sLineRendererData.vertexArray);
        BindShader(sLineRendererData.shader);
        sLineRendererData.vertexArray->GetVertexBuffer()->SetData(0, vertices);

        glDrawArrays(GL_LINES, 0, sLineRendererData.vertexArray->GetVertexBuffer()->GetCount());
    }

    void Renderer::DrawTriangles(const SharedPtr<VertexArray>& vertexArray, const SharedPtr<Material>& material)
    {
        BindVertexArray(vertexArray);
        BindMaterial(material);

        glDrawArrays(GL_TRIANGLES, 0, vertexArray->GetVertexBuffer()->GetCount());
    }

    void Renderer::DrawTriangles(const SharedPtr<VertexArray>& vertexArray, const SharedPtr<IndexBuffer>& indexBuffer, const SharedPtr<Material>& material)
    {
        BindVertexArray(vertexArray);
        BindIndexBuffer(indexBuffer);
        BindMaterial(material);

        glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

    void Renderer::DrawBackground(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }
}
