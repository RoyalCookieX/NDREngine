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
    
    class Texture
    {
    public:
        virtual ~Texture() { }

        virtual void Bind(uint32_t slot = 0) const = 0;
        virtual uint32_t GetTextureID() const = 0;
    };

    class Texture2D : public Texture
    {
    public:
        Texture2D();
        Texture2D(const TextureProperties& properties);
        Texture2D(const TextureProperties& properties, unsigned char* buffer);
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

    extern bool operator==(const Texture& left, const Texture& right);
    extern bool operator!=(const Texture& left, const Texture& right);
}
