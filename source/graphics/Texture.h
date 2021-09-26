#pragma once

namespace NDR
{
    class Texture
    {
    public:
        virtual ~Texture() { }

        virtual void Bind(uint32_t slot = 0) const = 0;

        static Texture* Create(int32_t width, int32_t height, int32_t bitsPerPixel, unsigned char* buffer);
    };
}
