#pragma once

namespace NDR
{    
    struct TextureProperties
    {
    public:
        int32_t width, height, bitsPerPixel;
    };
    
    class Texture
    {
    public:
        Texture();
        Texture(const TextureProperties& properties, unsigned char* buffer);
        ~Texture();

        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;

        Texture(Texture&& other) noexcept;
        Texture& operator=(Texture&& other) noexcept;

        void Bind(uint32_t slot = 0) const;

        uint32_t GetTextureID() const;

        friend bool operator==(const Texture& left, const Texture& right);
    private:
        uint32_t _id;
        unsigned char* _buffer;
        TextureProperties _properties;
    };

    extern bool operator==(const Texture& left, const Texture& right);
    extern bool operator!=(const Texture& left, const Texture& right);
}
