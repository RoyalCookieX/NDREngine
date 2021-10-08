#pragma once

namespace NDR
{
    class Texture
    {
    public:
        Texture();
        Texture(int32_t width, int32_t height, int32_t bitsPerPixel, unsigned char* buffer);
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
        int32_t _width, _height, _bitsPerPixel;
    };

    extern bool operator==(const Texture& left, const Texture& right);
    extern bool operator!=(const Texture& left, const Texture& right);
}
