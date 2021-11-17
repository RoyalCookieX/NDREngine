#include "ndrpch.h"
#include "Texture.h"

namespace NDR
{
    bool Texture::operator==(const Texture& other) const { return GetRendererID() == other.GetRendererID(); }
    bool Texture::operator!=(const Texture& other) const { return !(*this == other); }

    static void InitalizeTexture(uint32_t& id, const TextureProperties* properties, uint8_t* buffer)
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        int32_t filter = 0, wrap = 0;
        switch(properties->filter)
        {
            case TextureFilter::NEAREST: filter = GL_NEAREST; break;
            case TextureFilter::LINEAR: filter = GL_LINEAR; break;
        }
        switch(properties->wrap)
        {
            case TextureWrap::REPEAT: wrap = GL_REPEAT; break;
            case TextureWrap::CLAMPTOEDGE: wrap = GL_CLAMP_TO_EDGE; break;
        }
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, properties->width, properties->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Texture2D::Texture2D():
        _rendererID(0),
        _properties(0, 0, 0)
    {
    }

    Texture2D::Texture2D(const TextureProperties& properties):
        _rendererID(0),
        _properties(properties)
    {
        const size_t bufferSize = _properties.width * _properties.height * _properties.bitsPerPixel;
        uint8_t* buffer = new uint8_t[bufferSize];
        for(size_t i = 0; i < bufferSize; i++)
            buffer[i] = 255;

        InitalizeTexture(_rendererID, &_properties, buffer);
        delete[] buffer;
    }

    Texture2D::Texture2D(const TextureProperties& properties, uint8_t* buffer):   
        _rendererID(0),
        _properties(properties)
    {
        InitalizeTexture(_rendererID, &_properties, buffer);
    }

    Texture2D::~Texture2D() { glDeleteTextures(1, &_rendererID); }

    Texture2D::Texture2D(Texture2D&& other) noexcept:
        _rendererID(other._rendererID),
        _properties(other._properties)
    {
        other._rendererID = 0;
    }

    Texture2D& Texture2D::operator=(Texture2D&& other) noexcept
    {
        if(*this != other)
        {
            _rendererID = other._rendererID;
            _properties = other._properties;

            other._rendererID = 0;
        }
        return *this;
    }
    
    Texture2DAtlas::Texture2DAtlas():
        _rendererID(0),
        _properties(0, 0, 0, 0, 0)
    {
    }

    Texture2DAtlas::Texture2DAtlas(const TextureAtlasProperties& properties):
        _rendererID(0),
        _properties(properties)
    {
        const size_t bufferSize = _properties.width * _properties.height * _properties.bitsPerPixel;
        uint8_t* buffer = new uint8_t[bufferSize];
        for(size_t i = 0; i < bufferSize; i++)
            buffer[i] = 255;
        
        InitalizeTexture(_rendererID, &_properties, buffer);
        delete[] buffer;
    }

    Texture2DAtlas::Texture2DAtlas(const TextureAtlasProperties& properties, uint8_t* buffer):
        _rendererID(0),
        _properties(properties)
    {
        InitalizeTexture(_rendererID, &_properties, buffer);
    }

    Texture2DAtlas::Texture2DAtlas(Texture2DAtlas&& other) noexcept:
        _rendererID(other._rendererID),
        _properties(other._properties)
    {
        other._rendererID = 0;
    }

    Texture2DAtlas& Texture2DAtlas::operator=(Texture2DAtlas&& other) noexcept
    {
        if(*this != other)
        {
            _rendererID = other._rendererID;
            _properties = other._properties;

            other._rendererID = 0;
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
}
