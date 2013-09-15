#include <featherkit/rendering/texture.h>
#include <utility>
#include <iostream>

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
    
    void Texture::create(uint32_t w, uint32_t h, const uint8_t* imageData, bool smooth)
    {
        width = w;
        height = h;

        if(id)
        {
            destroy();
        }
        
        std::cout << "creating a texture, the id is now " << id << "\n";
        glGenTextures(1, &id);
        std::cout << "now it is" << id << "\n";
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)w, (GLsizei)h, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, smooth ? GL_LINEAR : GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, smooth ? GL_LINEAR : GL_NEAREST);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::create(uint32_t w, uint32_t h, const glm::vec3& colour, bool smooth)
    {
        create(w, h, colour.r, colour.g, colour.b, smooth);
    }

    void Texture::create(uint32_t w, uint32_t h, float r, float g, float b, bool smooth)
    {
        uint8_t* pixels = new uint8_t[w * h * 4];
        uint8_t red = 255 * r;
        uint8_t green = 255 * g;
        uint8_t blue = 255 * b;

        for(uint32_t x = 0; x < w; x++)
        {
            for(uint32_t y = 0; y < h; y++)
            {
                pixels[(x + y * w) * 4 + 0] = red;
                pixels[(x + y * w) * 4 + 1] = green;
                pixels[(x + y * w) * 4 + 2] = blue;
                pixels[(x + y * w) * 4 + 3] = 255;
            }
        }
        create(w, h, pixels, smooth);
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

    void Texture::setInteractive(bool interactive)
    {
        if(interactive && !pixelData)
        {
            pixelData = new uint8_t[width * height * 4];
            glBindTexture(GL_TEXTURE_2D, id);
            glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);
        }
        else if(!interactive && pixelData)
        {
            delete [] pixelData;
            pixelData = nullptr;
        }
    }
    
    void Texture::setPixel(uint32_t x, uint32_t y, float r, float g, float b, float a)
    {
        setPixelAsByte(x, y, r * 255, g * 255, b * 255, a * 255);
    }
    
    void Texture::setPixelAsByte(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        uint32_t pixelIndex = (x + y * width) * 4;
        pixelData[pixelIndex    ] = r;
        pixelData[pixelIndex + 1] = g;
        pixelData[pixelIndex + 2] = b;
        pixelData[pixelIndex + 3] = a;
    }
    
    void Texture::setPixels(std::function<void(uint32_t x, uint32_t y, uint8_t* pixels)> f)
    {
        f(width, height, pixelData);
    }

    glm::vec4 Texture::getPixel(uint32_t x, uint32_t y) const
    {
        return ((glm::vec4)getPixelAsByte(x, y)) / 255.0f;
    }

    glm::uvec4 Texture::getPixelAsByte(uint32_t x, uint32_t y) const
    {
        uint32_t pixelIndex = (x + y * width) * 4;
        return glm::uvec4(pixelData[pixelIndex],
                         pixelData[pixelIndex + 1],
                         pixelData[pixelIndex + 2],
                         pixelData[pixelIndex + 3]);
    }

    void Texture::update()
    {
        if(pixelData)
        {
            std::cout << "HEJ " << width << " " << height << "\n";
            glBindTexture(GL_TEXTURE_2D, id);
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);
        }
    }
    
    Texture::~Texture()
    {
        if(id)
        {
            std::cout << "id was " << id << " so i'll delete it!\n";
            destroy();
        }
    }
}
