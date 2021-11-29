#include "ndrpch.h"
#include "Framebuffer.h"
#include "core/Assert.h"

namespace NDR
{
    Framebuffer::Framebuffer():
        _id(0),
        _colorAttachment(0),
        _depthAttachment(0),
        _mode(),
        _width(0),
        _height(0)
    {
    }

    Framebuffer::Framebuffer(const FramebufferMode& mode, Int32 width, Int32 height):
        _id(0),
        _colorAttachment(0),
        _depthAttachment(0),
        _mode(mode),
        _width(width),
        _height(height)
    {
        glCreateFramebuffers(1, &_id);
        glBindFramebuffer(GL_FRAMEBUFFER, _id);

        glCreateTextures(GL_TEXTURE_2D, 1, &_colorAttachment);
        glBindTexture(GL_TEXTURE_2D, _colorAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _colorAttachment, 0);
        
        glCreateTextures(GL_TEXTURE_2D, 1, &_depthAttachment);
        glBindTexture(GL_TEXTURE_2D, _depthAttachment);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, _width, _height);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthAttachment, 0);

        NDR_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    Framebuffer::~Framebuffer() { glDeleteFramebuffers(1, &_id); }

    void Framebuffer::Bind() const { glBindFramebuffer(GL_FRAMEBUFFER, _id); }
    void Framebuffer::Unbind() const { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

    UInt32 Framebuffer::GetColorAttachmentID() const { return _colorAttachment; }
    UInt32 Framebuffer::GetDepthAttachmentID() const { return _depthAttachment; }
}
