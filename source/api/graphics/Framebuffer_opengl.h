#pragma once
#include "graphics/Framebuffer.h"

namespace NDR { namespace GraphicsAPI
{
    class Framebuffer_opengl : public Framebuffer
    {
    public:
        Framebuffer_opengl(const FramebufferMode& mode, uint32_t width, uint32_t height);
        virtual ~Framebuffer_opengl() override;

        virtual void Bind() const override;
        virtual void Unbind() const override;
    private:
        uint32_t _fbo, _colorTextureId, _depthTextureId;
        FramebufferMode mode;
        uint32_t _width, _height; 
    };    
}
}
