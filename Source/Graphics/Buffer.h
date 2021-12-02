#pragma once
#include "Defines.h"
#include "Layout.h"

namespace NDR
{
    class VertexBuffer
    {
    public:
        VertexBuffer(UInt32 count, const VertexLayout& layout);
        VertexBuffer(const std::vector<float>& vertices, const VertexLayout& layout);
        ~VertexBuffer();

        VertexBuffer(const VertexBuffer&) = delete;
        VertexBuffer& operator=(const VertexBuffer&) = delete;

        RendererID GetRendererID() const { return _rendererID; }
        UInt32 GetCount() const { return _count; }
        size_t GetSize() const { return _count * sizeof(float); }
        VertexLayout& GetLayout() { return _layout; }
        const VertexLayout& GetLayout() const { return _layout; }

        void SetData(UInt32 offset, std::vector<float> vertices);
    private:
        RendererID _rendererID;
        UInt32 _count;
        VertexLayout _layout;
    };

    class IndexBuffer
    {
    public:
        IndexBuffer(const std::vector<UInt32>& indices);
        ~IndexBuffer();

        IndexBuffer(const IndexBuffer&) = delete;
        IndexBuffer& operator=(const IndexBuffer&) = delete;

        RendererID GetRendererID() const { return _rendererID; }
        UInt32 GetCount() const { return _count; }
        size_t GetSize() const { return _count * sizeof(UInt32); }
    private:
        RendererID _rendererID;
        UInt32 _count;
    };

    class UniformBuffer
    {
    public:
        UniformBuffer(size_t size, UInt32 binding);
        ~UniformBuffer();

        UniformBuffer(const UniformBuffer&) = delete;
        UniformBuffer& operator=(const UniformBuffer&) = delete;

        RendererID GetRendererID() const { return _rendererID; }
        size_t GetSize() const { return _size; }
        
        void SetData(size_t offset, size_t size, const void* data);
    private:
        RendererID _rendererID;
        size_t _size;
    };
}
