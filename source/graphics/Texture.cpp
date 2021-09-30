#include "ndrpch.h"
#include "Texture.h"

namespace NDR
{
    Texture::Texture():
        _id(0),
        _buffer(nullptr),
        _width(0),
        _height(0),
        _bitsPerPixel(0)
    {
    }

    Texture::Texture(const int32_t width, const int32_t height, const int32_t bitsPerPixel, unsigned char* buffer):
        _id(0),
        _buffer(buffer),
        _width(width),
        _height(height),
        _bitsPerPixel(bitsPerPixel)
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &_id);
        glBindTexture(GL_TEXTURE_2D, _id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _buffer);
    }

    Texture::~Texture() { glDeleteTextures(1, &_id); }

    Texture::Texture(Texture&& other) noexcept:
        _id(other._id),
        _buffer(other._buffer),
        _width(other._width),
        _height(other._height),
        _bitsPerPixel(other._bitsPerPixel)
    {
        other._id = 0;
        other._buffer = nullptr;
        other._width = 0;
        other._height = 0;
        other._bitsPerPixel = 0;
    }

    Texture& Texture::operator=(Texture&& other) noexcept
    {
        if(*this != other)
        {
            _id = other._id;
            _buffer = other._buffer;
            _width = other._width;
            _height = other._height;
            _bitsPerPixel = other._bitsPerPixel;

            other._id = 0;
            other._buffer = nullptr;
            other._width = 0;
            other._height = 0;
            other._bitsPerPixel = 0;
        }
        return *this;
    }

    void Texture::Bind(const uint32_t slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, _id);
    }

    uint32_t Texture::GetTextureID() const { return _id; }

    bool operator==(const Texture& left, const Texture& right) { return left._id == right._id; }
    bool operator!=(const Texture& left, const Texture& right) { return !(left == right); }
}
