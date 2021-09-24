#pragma once

namespace NDR
{
    class Texture
    {
    public:
        Texture(int width, int height, int bitsPerPixel, unsigned char* buffer);
        ~Texture();

        void Bind(GLuint slot = 0) const;

    private:
        GLuint _id;
        int _width = 0;
        int _height = 0;
        int _bitsPerPixel = 0;
        unsigned char* _buffer = nullptr;
    };
}
