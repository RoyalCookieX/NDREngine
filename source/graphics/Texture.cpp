#include "ndrpch.h"
#include "Texture.h"

namespace NDR
{
    bool Texture::operator==(const Texture& other) const { return GetTextureID() == other.GetTextureID(); }
    bool Texture::operator!=(const Texture& other) const { return !(*this == other); }
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
        uint8_t* buffer = new uint8_t[bufferSize];
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

    Texture2D::Texture2D(const TextureProperties& properties, uint8_t* buffer):   
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

    Texture2DAtlas::Texture2DAtlas():
        _id(0),
        _properties(0, 0, 0, 0, 0)
    {
    }

    Texture2DAtlas::Texture2DAtlas(const TextureAtlasProperties& properties):
        _id(0),
        _properties(properties)
    {
        const size_t bufferSize = _properties.width * _properties.height * _properties.bitsPerPixel;
        uint8_t* buffer = new uint8_t[bufferSize];
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

    Texture2DAtlas::Texture2DAtlas(const TextureAtlasProperties& properties, uint8_t* buffer):
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

    Texture2DAtlas::Texture2DAtlas(Texture2DAtlas&& other) noexcept:
        _id(other._id),
        _properties(other._properties)
    {
        other._id = 0;
    }

    Texture2DAtlas& Texture2DAtlas::operator=(Texture2DAtlas&& other) noexcept
    {
        if(*this != other)
        {
            _id = other._id;
            _properties = other._properties;

            other._id = 0;
        }
        return *this;
    }

    std::array<float, 8> Texture2DAtlas::GetUVs(uint32_t x, uint32_t y) const
    {
        const float uOffset = ((float)_properties.cellWidth / (float)_properties.width);
        const float vOffset = ((float)_properties.cellHeight / (float)_properties.height);
        
        return
        {
            uOffset * x + 0.0f,     vOffset * y + 0.0f,
            uOffset * x + uOffset,  vOffset * y + 0.0f,
            uOffset * x + uOffset,  vOffset * y + vOffset,
            uOffset * x + 0.0f,     vOffset * y + vOffset,
        };
    }

    void Texture2DAtlas::Bind(uint32_t slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, _id);
    }

    uint32_t Texture2DAtlas::GetTextureID() const { return _id; }
}
