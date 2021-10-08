#pragma once

namespace NDR
{
    enum class FramebufferMode
    {
        SCREENSIZE,
        FIXED
    };
    
    class Framebuffer
    {
    public:
        Framebuffer();
        Framebuffer(const FramebufferMode& mode, int32_t width, int32_t height);
        ~Framebuffer();

        Framebuffer(const Framebuffer&) = delete;
        Framebuffer& operator=(const Framebuffer&) = delete;

        Framebuffer(Framebuffer&& other) noexcept;
        Framebuffer& operator=(Framebuffer&& other) noexcept;

        void Bind() const;
        void Unbind() const;

        uint32_t GetColorAttachmentID() const;
        uint32_t GetDepthAttachmentID() const;

        friend bool operator==(const Framebuffer& left, const Framebuffer& right);
    private:
        uint32_t _id, _colorAttachment, _depthAttachment;
        FramebufferMode _mode;
        int32_t _width, _height;
    };

    extern bool operator==(const Framebuffer& left, const Framebuffer& right);
    extern bool operator!=(const Framebuffer& left, const Framebuffer& right);
}