#pragma once
#include "Defines.h"

namespace NDR
{
    enum class TextureFilter { NEAREST, LINEAR };
    enum class TextureWrap { REPEAT, CLAMPTOEDGE };
    
    struct TextureProperties
    {
    public:
        TextureProperties(Int32 width, Int32 height, Int32 bitsPerPixel,
            TextureFilter filter = TextureFilter::NEAREST, TextureWrap wrap = TextureWrap::CLAMPTOEDGE):

            width(width),
            height(height),
            bitsPerPixel(bitsPerPixel),
            filter(filter),
            wrap(wrap)
        {
        }
        
        Int32 width, height, bitsPerPixel;
        TextureFilter filter;
        TextureWrap wrap;
    };

    struct TextureAtlasProperties : TextureProperties
    {
    public:
        TextureAtlasProperties(Int32 width, Int32 height,
            UInt32 cellWidth, UInt32 cellHeight, Int32 bitsPerPixel,
            TextureFilter filter = TextureFilter::NEAREST, TextureWrap wrap = TextureWrap::CLAMPTOEDGE):

            TextureProperties(width, height, bitsPerPixel, filter, wrap),
            cellWidth(cellWidth),
            cellHeight(cellHeight)
        {
        }

        UInt32 cellWidth, cellHeight;
    };
    
    class Texture
    {
    public:
        virtual ~Texture() = default;

        virtual RendererID GetRendererID() const = 0;
    };

    class Texture2D : public Texture
    {
    public:
        Texture2D(const TextureProperties& properties);
        Texture2D(const TextureProperties& properties, uint8_t* buffer);
        virtual ~Texture2D() override;

        Texture2D(const Texture2D&) = delete;
        Texture2D& operator=(const Texture2D&) = delete;

        virtual UInt32 GetRendererID() const override { return _rendererID; }

    private:
        RendererID _rendererID;
        TextureProperties _properties;
    };

    class Texture2DAtlas : public Texture
    {
    public:
        Texture2DAtlas(const TextureAtlasProperties& properties);
        Texture2DAtlas(const TextureAtlasProperties& properties, uint8_t* buffer);
        virtual ~Texture2DAtlas() override; 

        Texture2DAtlas(const Texture&) = delete;
        Texture2DAtlas& operator=(const Texture2DAtlas&) = delete;

        virtual UInt32 GetRendererID() const override { return _rendererID; }
        virtual std::array<float, 8> GetUVs(UInt32 x, UInt32 y) const;

    private:
        RendererID _rendererID;
        TextureAtlasProperties _properties;
    };
}
