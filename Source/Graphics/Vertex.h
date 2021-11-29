#pragma once
#include "Defines.h"
#include "Buffer.h"

namespace NDR
{
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        VertexArray(const VertexArray&) = delete;
        VertexArray& operator=(const VertexArray&) = delete;

        RendererID GetRendererID() const { return _rendererID; }
        SPointer<VertexBuffer>& GetVertexBuffer(Int32 index = 0) { return _vertexBuffers[index]; }
        const SPointer<VertexBuffer>& GetVertexBuffer(Int32 index = 0) const { return _vertexBuffers[index]; }
        UInt32 GetVertexBufferCount() const { return (UInt32)_vertexBuffers.size(); }

        void AddVertexBuffer(SPointer<VertexBuffer>&& vertexBuffer);
    private:
        RendererID _rendererID;
        std::vector<SPointer<VertexBuffer>> _vertexBuffers;
    };
}
