#pragma once
#include "graphics/Texture.h"


namespace NDR { namespace GraphicsAPI
{
    class Texture_opengl : public Texture
    {
    public:
        Texture_opengl(int32_t width, int32_t height, int32_t bitsPerPixel, unsigned char* buffer);
        virtual ~Texture_opengl() override;

        virtual void Bind(uint32_t slot) const override;
    private:
        uint32_t _id;
        int _width;
        int _height;
        int _bitsPerPixel;
        unsigned char* _buffer;
    };
}
}
