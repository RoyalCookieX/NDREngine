#include "ndrpch.h"
#include "Renderer.h"

#include "Buffer.h"
#include "Material.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Vertex.h"
#include "Core/Log.h"
#include "Utility/AssetManager.h"

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

    struct CameraUBOData
    {
        glm::mat4 projection;
        glm::mat4 view;
    };
    
    struct RendererData
    {
    public:
        void Initalize()
        {
            initialized = true;
            vertexArray = CreateShared<VertexArray>();
            shader = LoadShader("Assets/Shaders/Line.shader", AssetRoot::ENGINE);
            
            cameraBuffer = CreateShared<UniformBuffer>(sizeof(CameraUBOData), 0);
        }

        void Shutdown()
        {
            initialized = false;
        }

        bool initialized;
        
        SPointer<VertexArray> vertexArray;
        SPointer<Shader> shader;
        SPointer<UniformBuffer> cameraBuffer;
    };
    static RendererData sRendererData;
    
    void BindVertexBuffer(const SPointer<VertexBuffer>& vertexBuffer) { glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->GetRendererID()); }
    void BindIndexBuffer(const SPointer<IndexBuffer>& indexBuffer) { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->GetRendererID()); }
    void BindVertexArray(const SPointer<VertexArray>& vertexArray)
    {
        glBindVertexArray(vertexArray->GetRendererID());
        for(UInt32 i = 0; i < vertexArray->GetVertexBufferCount(); i++)
            BindVertexBuffer(vertexArray->GetVertexBuffer(i));
    }
    void BindShader(const SPointer<Shader>& shader) { glUseProgram(shader->GetRendererID()); }
    void BindTexture(const SPointer<Texture>& texture, UInt32 slot = 0)
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, texture->GetRendererID());
    }
    void BindMaterial(const SPointer<Material>& material)
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
        if(sRendererData.initialized)
            return;
        
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            NDR_LOGFATAL("[Renderer]: GLAD did not initalize!");
            return;
        }
        NDR_LOGINFO("%s", glGetString(GL_VENDOR));
        NDR_LOGINFO("%s", glGetString(GL_VERSION));
        NDR_LOGINFO("%s", glGetString(GL_RENDERER));
#if NDR_DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(MessageCallback, nullptr);
#endif
        //TODO: Move to material flags
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        sRendererData.Initalize();
        VertexLayout lineLayout;
        lineLayout.AddAttribute({3, false}); // position
        lineLayout.AddAttribute({4, false}); // color
        SPointer<VertexBuffer> lineVertexBuffer = CreateShared<VertexBuffer>(lineLayout.GetAttributeComponentCount() * 2, lineLayout);
        sRendererData.vertexArray->AddVertexBuffer(std::move(lineVertexBuffer));
    }

    void Renderer::Shutdown()
    {
        if(!sRendererData.initialized)
            return;
        sRendererData.Shutdown();
    }

    void Renderer::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::SetViewProjection(const glm::mat4& view, const glm::mat4& projection)
    {
        CameraUBOData cameraUBO;
        cameraUBO.projection = projection;
        cameraUBO.view = view;
        sRendererData.cameraBuffer->SetData(0, sizeof(CameraUBOData), &cameraUBO);
    }

    void Renderer::DrawLine(const glm::vec3& start, const glm::vec3& end, const glm::vec4& color, const float width)
    {
        std::vector<float> vertices
        {
            start.x, start.y, start.z, color.r, color.g, color.b, color.a,
            end.x,   end.y,   end.z,   color.r, color.g, color.b, color.a,
        };
        BindVertexArray(sRendererData.vertexArray);
        BindShader(sRendererData.shader);
        sRendererData.vertexArray->GetVertexBuffer()->SetData(0, vertices);

        glLineWidth(width);
        glDrawArrays(GL_LINES, 0, sRendererData.vertexArray->GetVertexBuffer()->GetCount());
    }

    void Renderer::DrawTriangles(const SPointer<VertexArray>& vertexArray, const SPointer<Material>& material)
    {
        BindVertexArray(vertexArray);
        BindMaterial(material);

        glDrawArrays(GL_TRIANGLES, 0, vertexArray->GetVertexBuffer()->GetCount());
    }

    void Renderer::DrawTriangles(const SPointer<VertexArray>& vertexArray, const SPointer<IndexBuffer>& indexBuffer, const SPointer<Material>& material)
    {
        BindVertexArray(vertexArray);
        BindIndexBuffer(indexBuffer);
        BindMaterial(material);

        glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

    void Renderer::DrawMesh(const SPointer<Mesh>& mesh, const Transform& transform)
    {
        BindVertexArray(mesh->GetVertexArray());
        for(UInt32 i = 0; i < mesh->GetSubMeshCount(); i++)
        {
            mesh->GetMaterial(i)->GetShader()->SetMat4("u_Model", transform.GetMatrix());
            BindIndexBuffer(mesh->GetIndexBuffer(i));
            BindMaterial(mesh->GetMaterial(i));

            glDrawElements(GL_TRIANGLES, mesh->GetIndexBuffer(i)->GetCount(), GL_UNSIGNED_INT, nullptr);
        }
    }

    void Renderer::DrawBackground(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }
}
