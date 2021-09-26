#include "ndrpch.h"
#include "Framebuffer_opengl.h"
#include "core/APICall.h"

namespace NDR
{
    Framebuffer* Framebuffer::Create(const FramebufferMode& mode, uint32_t width, uint32_t height)
    {
        return new GraphicsAPI::Framebuffer_opengl(mode, width, height);
    }
    
namespace GraphicsAPI
{
    Framebuffer_opengl::Framebuffer_opengl(const FramebufferMode& mode, uint32_t width, uint32_t height):
        _fbo(0),
        _colorTextureId(0),
        mode(mode),
        _width(width),
        _height(height)
    {
        glCreateFramebuffers(1, &_fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

        glCreateTextures(GL_TEXTURE, 1, &_colorTextureId);
        glBindTexture(GL_TEXTURE_2D, _colorTextureId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _colorTextureId, 0);
        
        glCreateTextures(GL_TEXTURE, 1, &_depthTextureId);
        glBindTexture(GL_TEXTURE_2D, _depthTextureId);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, _width, _height);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH24_STENCIL8, GL_TEXTURE_2D, _depthTextureId, 0);

        //assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    Framebuffer_opengl::~Framebuffer_opengl() { glDeleteFramebuffers(1, &_fbo); }
    void Framebuffer_opengl::Bind() const { glBindFramebuffer(GL_FRAMEBUFFER, _fbo); }
    void Framebuffer_opengl::Unbind() const { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

}
}
