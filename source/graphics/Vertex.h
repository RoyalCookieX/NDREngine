#pragma once
#include "NDRTypes.h"
#include "Buffer.h"

namespace NDR
{
    class VertexArray
    {
    public:
        VertexArray();
        VertexArray(VertexBuffer&& vertexBuffer);
        ~VertexArray();

        VertexArray(const VertexArray&) = delete;
        VertexArray& operator=(const VertexArray&) = delete;

        VertexArray(VertexArray&& other) noexcept;
        VertexArray& operator=(VertexArray&& other) noexcept;

        bool operator==(const VertexArray& other) const;
        bool operator!=(const VertexArray& other) const;

        RendererID GetRendererID() const { return _rendererID; }
        VertexBuffer& GetVertexBuffer() { return _vertexBuffer; }
        const VertexBuffer& GetVertexBuffer() const { return  _vertexBuffer; }
    private:
        RendererID _rendererID;
        VertexBuffer _vertexBuffer;
    };
}
