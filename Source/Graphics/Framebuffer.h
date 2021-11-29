#pragma once
#include "Defines.h"

namespace NDR
{
    /*
     * TODO: Compose Framebuffer of Attachments
    */

    enum class FramebufferMode
    {
        SCREENSIZE, FIXED
    };
    
    class Framebuffer
    {
    public:
        Framebuffer();
        Framebuffer(const FramebufferMode& mode, Int32 width, Int32 height);
        ~Framebuffer();

        Framebuffer(const Framebuffer&) = delete;
        Framebuffer& operator=(const Framebuffer&) = delete;

        void Bind() const;
        void Unbind() const;

        UInt32 GetColorAttachmentID() const;
        UInt32 GetDepthAttachmentID() const;

    private:
        UInt32 _id, _colorAttachment, _depthAttachment;
        FramebufferMode _mode;
        Int32 _width, _height;
    };
}