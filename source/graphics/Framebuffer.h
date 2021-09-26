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
        virtual ~Framebuffer() { }

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        static Framebuffer* Create(const FramebufferMode& mode, uint32_t width, uint32_t height);
    };
}