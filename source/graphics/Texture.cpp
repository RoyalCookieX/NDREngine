#include "ndrpch.h"
#include "Texture.h"

namespace NDR
{
    Texture::Texture(int width, int height, int bitsPerPixel, unsigned char* buffer)
        : _id(0),
          _width(width),
          _height(height),
          _bitsPerPixel(bitsPerPixel),
          _buffer(buffer)
    {
        GLCall(glGenTextures(1, &_id));
        GLCall(glBindTexture(GL_TEXTURE_2D, _id));

        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _buffer));
    }

    Texture::~Texture()
    {
        GLCall(glDeleteTextures(1, &_id));
    }

    void Texture::Bind(const GLuint slot) const
    {
        GLCall(glActiveTexture(GL_TEXTURE0 + slot));
        GLCall(glBindTexture(GL_TEXTURE_2D, _id));
    }
}
