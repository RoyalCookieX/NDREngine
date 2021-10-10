#include "ndrpch.h"
#include "Texture.h"

namespace NDR
{
    Texture2D::Texture2D():
        _id(0),
        _properties(0, 0, 0)
    {
    }

    Texture2D::Texture2D(const TextureProperties& properties):
        _id(0),
        _properties(properties)
    {
        const size_t bufferSize = _properties.width * _properties.height * _properties.bitsPerPixel;
        unsigned char* buffer = new unsigned char[bufferSize];
        for(size_t i = 0; i < bufferSize; i++)
            buffer[i] = 255;
        
        glCreateTextures(GL_TEXTURE_2D, 1, &_id);
        glBindTexture(GL_TEXTURE_2D, _id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _properties.width, _properties.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

        glBindTexture(GL_TEXTURE_2D, 0);
        delete buffer;
    }

    Texture2D::Texture2D(const TextureProperties& properties, unsigned char* buffer):   
        _id(0),
        _properties(properties)
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &_id);
        glBindTexture(GL_TEXTURE_2D, _id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _properties.width, _properties.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Texture2D::~Texture2D()
    {
        glDeleteTextures(1, &_id);
    }

    Texture2D::Texture2D(Texture2D&& other) noexcept:
        _id(other._id),
        _properties(other._properties)
    {
        other._id = 0;
    }

    Texture2D& Texture2D::operator=(Texture2D&& other) noexcept
    {
        if(*this != other)
        {
            _id = other._id;
            _properties = other._properties;

            other._id = 0;
        }
        return *this;
    }

    void Texture2D::Bind(const uint32_t slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, _id);
    }

    uint32_t Texture2D::GetTextureID() const { return _id; }

    bool operator==(const Texture& left, const Texture& right) { return left.GetTextureID() == right.GetTextureID(); }
    bool operator!=(const Texture& left, const Texture& right) { return !(left == right); }
}
