#pragma once
#include "NDRTypes.h"
#include "Buffer.h"
#include "utility/Memory.h"

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
        SharedPtr<VertexBuffer>& GetVertexBuffer(int32_t index = 0) { return _vertexBuffers[index]; }
        const SharedPtr<VertexBuffer>& GetVertexBuffer(int32_t index = 0) const { return _vertexBuffers[index]; }
        uint32_t GetVertexBufferCount() const { return (uint32_t)_vertexBuffers.size(); }

        void AddVertexBuffer(SharedPtr<VertexBuffer>&& vertexBuffer);
    private:
        RendererID _rendererID;
        std::vector<SharedPtr<VertexBuffer>> _vertexBuffers;
    };
}
