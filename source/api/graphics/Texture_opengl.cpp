#include "ndrpch.h"
#include "Texture_opengl.h"

namespace NDR
{
    Texture* Texture::Create(const int32_t width, const int32_t height, const int32_t bitsPerPixel, unsigned char* buffer)
    {
        return new GraphicsAPI::Texture_opengl(width, height, bitsPerPixel, buffer);
    }

namespace GraphicsAPI
{
    Texture_opengl::Texture_opengl(int32_t width, int32_t height, int32_t bitsPerPixel, unsigned char* buffer)
        : _id(0),
          _width(width),
          _height(height),
          _bitsPerPixel(bitsPerPixel),
          _buffer(buffer)
    {
        glGenTextures(1, &_id);
        glBindTexture(GL_TEXTURE_2D, _id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _buffer);
    }

    Texture_opengl::~Texture_opengl()
    {
        glDeleteTextures(1, &_id);
    }

    void Texture_opengl::Bind(uint32_t slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, _id);
    }
}
}
