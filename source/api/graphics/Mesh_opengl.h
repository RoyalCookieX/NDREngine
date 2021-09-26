#pragma once
#include "graphics/Mesh.h"

namespace NDR { namespace GraphicsAPI
{
    class Mesh_opengl : public Mesh
    {
    public:
        Mesh_opengl(const VertexData& vertices, const IndexData& indices, const VertexLayout& layout);
        virtual ~Mesh_opengl() override;
        
        virtual uint32_t GetVertexCount() const override;
        virtual uint32_t GetIndexCount() const override;
        virtual void Bind() const override;
    private:
        uint32_t _vao, _vbo, _ibo;
        
        VertexData _vertexData;
        IndexData _indexData;
        VertexLayout _layout;
    };
}
}
