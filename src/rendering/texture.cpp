#include <featherkit/rendering/texture.h>
#include <utility>
#include <cstring>

namespace fea
{
    Texture::Texture() : id(0), width(0), height(0), pixelData(nullptr)
    {
    }
    
    Texture::Texture(Texture&& other) : id(0), width(0), height(0), pixelData(nullptr)
    {
        std::swap(id, other.id);
        std::swap(width, other.width);
        std::swap(height, other.height);
        std::swap(pixelData, other.pixelData);
    }
    
    Texture& Texture::operator=(Texture&& other)
    {
        std::swap(id, other.id);
        std::swap(width, other.width);
        std::swap(height, other.height);
        std::swap(pixelData, other.pixelData);
        return *this;
    }

    GLuint Texture::getId() const
    {
        return id;
    }
    
    void Texture::create(uint32_t w, uint32_t h, const uint8_t* imageData, bool smooth, bool interactive)
    {
        width = w;
        height = h;

        if(id)
        {
            destroy();
        }
        
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)w, (GLsizei)h, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, smooth ? GL_LINEAR : GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, smooth ? GL_LINEAR : GL_NEAREST);

        glBindTexture(GL_TEXTURE_2D, 0);

        if(interactive)
        {
            uint32_t byteAmount = width * height * 4;
            pixelData = new uint8_t[byteAmount];
            memcpy(pixelData, imageData, byteAmount);
        }
    }

    void Texture::create(uint32_t w, uint32_t h, const Colour& colour, bool smooth, bool interactive)
    {
        uint8_t* pixels = new uint8_t[w * h * 4];

        for(uint32_t x = 0; x < w; x++)
        {
            for(uint32_t y = 0; y < h; y++)
            {
                pixels[(x + y * w) * 4 + 0] = colour.rAsByte();
                pixels[(x + y * w) * 4 + 1] = colour.gAsByte();
                pixels[(x + y * w) * 4 + 2] = colour.bAsByte();
                pixels[(x + y * w) * 4 + 3] = colour.aAsByte();
            }
        }
        create(w, h, pixels, smooth, interactive);
        delete [] pixels;
    }

    void Texture::destroy()
    {
        if(id)
        {
            glDeleteTextures(1, &id);
            id = 0;
            width = 0;
            height = 0;
            delete [] pixelData;
            pixelData = nullptr;
        }
    }
    
    void Texture::setPixel(uint32_t x, uint32_t y, const Colour& colour)
    {
        uint32_t pixelIndex = (x + y * width) * 4;
        pixelData[pixelIndex    ] = colour.rAsByte();
        pixelData[pixelIndex + 1] = colour.gAsByte();
        pixelData[pixelIndex + 2] = colour.bAsByte();
        pixelData[pixelIndex + 3] = colour.aAsByte();
    }
    
    void Texture::setPixels(std::function<void(uint32_t x, uint32_t y, uint8_t* pixels)> f)
    {
        f(width, height, pixelData);
    }

    Colour Texture::getPixel(uint32_t x, uint32_t y) const
    {
        uint32_t pixelIndex = (x + y * width) * 4;
        return Colour(pixelData[pixelIndex],
                         pixelData[pixelIndex + 1],
                         pixelData[pixelIndex + 2],
                         pixelData[pixelIndex + 3]);
    }

    void Texture::update()
    {
        if(pixelData)
        {
            glBindTexture(GL_TEXTURE_2D, id);
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);
        }
    }
    
    Texture::~Texture()
    {
        if(id)
        {
            destroy();
        }
    }
}
