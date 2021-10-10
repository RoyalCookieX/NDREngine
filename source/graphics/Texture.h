#pragma once

namespace NDR
{    
    struct TextureProperties
    {
    public:
        TextureProperties(int32_t width, int32_t height, int32_t bitsPerPixel):
            width(width),
            height(height),
            bitsPerPixel(bitsPerPixel)
        {
        }
        
        int32_t width, height, bitsPerPixel;
    };

    struct TextureAtlasProperties
    {
    public:
        TextureAtlasProperties(int32_t width, int32_t height, uint32_t cellWidth, uint32_t cellHeight, int32_t bitsPerPixel):
            width(width),
            height(height),
            cellWidth(cellWidth),
            cellHeight(cellHeight),
            bitsPerPixel(bitsPerPixel)
        {
        }

        int32_t width, height, bitsPerPixel;
        uint32_t cellWidth, cellHeight;
    };
    
    class Texture
    {
    public:
        virtual ~Texture() { }

        virtual void Bind(uint32_t slot = 0) const = 0;
        virtual uint32_t GetTextureID() const = 0;

        bool operator==(const Texture& other) const;
        bool operator!=(const Texture& other) const;
    };

    class Texture2D : public Texture
    {
    public:
        Texture2D();
        Texture2D(const TextureProperties& properties);
        Texture2D(const TextureProperties& properties, uint8_t* buffer);
        virtual ~Texture2D() override;

        Texture2D(const Texture&) = delete;
        Texture2D& operator=(const Texture2D&) = delete;

        Texture2D(Texture2D&& other) noexcept;
        Texture2D& operator=(Texture2D&& other) noexcept;

        virtual void Bind(uint32_t slot) const override;
        virtual uint32_t GetTextureID() const override;

    private:
        uint32_t _id;
        TextureProperties _properties;
    };

    class Texture2DAtlas : public Texture
    {
    public:
        Texture2DAtlas();
        Texture2DAtlas(const TextureAtlasProperties& properties);
        Texture2DAtlas(const TextureAtlasProperties& properties, uint8_t* buffer);

        Texture2DAtlas(const Texture&) = delete;
        Texture2DAtlas& operator=(const Texture2DAtlas&) = delete;

        Texture2DAtlas(Texture2DAtlas&& other) noexcept;
        Texture2DAtlas& operator=(Texture2DAtlas&& other) noexcept;

        virtual std::array<float, 8> GetUVs(uint32_t x, uint32_t y) const;
        virtual void Bind(uint32_t slot) const override;
        virtual uint32_t GetTextureID() const override;

    private:
        uint32_t _id;
        TextureAtlasProperties _properties;
    };
}
