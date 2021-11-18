#pragma once
#include "NDRTypes.h"
#include "Layout.h"

namespace NDR
{
    class VertexBuffer
    {
    public:
        VertexBuffer();
        VertexBuffer(uint32_t count, const VertexLayout& layout);
        VertexBuffer(const std::vector<float>& vertices, const VertexLayout& layout);
        ~VertexBuffer();

        VertexBuffer(const VertexBuffer&) = delete;
        VertexBuffer& operator=(const VertexBuffer&) = delete;

        VertexBuffer(VertexBuffer&& other) noexcept;
        VertexBuffer& operator=(VertexBuffer&& other) noexcept;

        bool operator==(const VertexBuffer& other) const;
        bool operator!=(const VertexBuffer& other) const;

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
        IndexBuffer();
        IndexBuffer(const std::vector<uint32_t>& indices);
        ~IndexBuffer();

        IndexBuffer(const IndexBuffer&) = delete;
        IndexBuffer& operator=(const IndexBuffer&) = delete;

        IndexBuffer(IndexBuffer&& other) noexcept;
        IndexBuffer& operator=(IndexBuffer&& other) noexcept;

        bool operator==(const IndexBuffer& other) const;
        bool operator!=(const IndexBuffer& other) const;

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
        UniformBuffer();
        UniformBuffer(size_t size, uint32_t binding);
        ~UniformBuffer();

        UniformBuffer(const UniformBuffer&) = delete;
        UniformBuffer& operator=(const UniformBuffer&) = delete;

        UniformBuffer(UniformBuffer&& other) noexcept;
        UniformBuffer& operator=(UniformBuffer&& other) noexcept;

        bool operator==(const UniformBuffer& other) const;
        bool operator!=(const UniformBuffer& other) const;

        void SetData(size_t offset, size_t size, const void* data);
    private:
        RendererID _rendererID;
        size_t _size;
    };
}
