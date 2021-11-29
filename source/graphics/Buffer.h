#pragma once
#include "NDRTypes.h"
#include "Layout.h"

namespace NDR
{
    class VertexBuffer
    {
    public:
        VertexBuffer(uint32_t count, const VertexLayout& layout);
        VertexBuffer(const std::vector<float>& vertices, const VertexLayout& layout);
        ~VertexBuffer();

        VertexBuffer(const VertexBuffer&) = delete;
        VertexBuffer& operator=(const VertexBuffer&) = delete;

        RendererID GetRendererID() const { return _rendererID; }
        uint32_t GetCount() const { return _count; }
        size_t GetSize() const { return _count * sizeof(float); }
        VertexLayout& GetLayout() { return _layout; }
        const VertexLayout& GetLayout() const { return _layout; }

        void SetData(uint32_t offset, std::vector<float> vertices);
    private:
        RendererID _rendererID;
        uint32_t _count;
        VertexLayout _layout;
    };

    class IndexBuffer
    {
    public:
        IndexBuffer(const std::vector<uint32_t>& indices);
        ~IndexBuffer();

        IndexBuffer(const IndexBuffer&) = delete;
        IndexBuffer& operator=(const IndexBuffer&) = delete;

        RendererID GetRendererID() const { return _rendererID; }
        uint32_t GetCount() const { return _count; }
        size_t GetSize() const { return _count * sizeof(uint32_t); }
    private:
        RendererID _rendererID;
        uint32_t _count;
    };

    class UniformBuffer
    {
    public:
        UniformBuffer(size_t size, uint32_t binding);
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
