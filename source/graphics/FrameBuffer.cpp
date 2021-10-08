#include "ndrpch.h"
#include "Framebuffer.h"

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

    Framebuffer::Framebuffer(const FramebufferMode& mode, int32_t width, int32_t height):
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

        assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    Framebuffer::~Framebuffer() { glDeleteFramebuffers(1, &_id); }

    Framebuffer::Framebuffer(Framebuffer&& other) noexcept:
        _id(other._id),
        _colorAttachment(other._colorAttachment),
        _depthAttachment(other._depthAttachment),
        _mode(other._mode),
        _width(other._width),
        _height(other._height)
    {
        other._id = 0;
        other._colorAttachment = 0;
        other._depthAttachment = 0;
        other._width = 0;
        other._height = 0;
    }

    Framebuffer& Framebuffer::operator=(Framebuffer&& other) noexcept
    {
        if(*this != other)
        {
            _id = other._id;
            _colorAttachment = other._colorAttachment;
            _depthAttachment = other._depthAttachment;
            _mode = other._mode;
            _width = other._width;
            _height = other._height;

            other._id = 0;
            other._colorAttachment = 0;
            other._depthAttachment = 0;
            other._width = 0;
            other._height = 0;
        }
        return *this;
    }

    void Framebuffer::Bind() const { glBindFramebuffer(GL_FRAMEBUFFER, _id); }
    void Framebuffer::Unbind() const { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

    uint32_t Framebuffer::GetColorAttachmentID() const { return _colorAttachment; }
    uint32_t Framebuffer::GetDepthAttachmentID() const { return _depthAttachment; }

    bool operator==(const Framebuffer& left, const Framebuffer& right) { return left._id == right._id; }
    bool operator!=(const Framebuffer& left, const Framebuffer& right) { return !(left == right); }
}
