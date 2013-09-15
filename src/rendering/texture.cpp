#include <featherkit/rendering/texture.h>
#include <utility>

namespace fea
{
    Texture::Texture() : id(0)
    {
    }
    
    Texture::Texture(Texture&& other) : id(other.id)
    {
        other.id = 0;
    }
    
    Texture& Texture::operator=(Texture&& other)
    {
        std::swap(id, other.id);
        return *this;
    }

    GLuint Texture::getId() const
    {
        return id;
    }
    
    void Texture::create(uint32_t w, uint32_t h, const uint8_t* imageData, bool smooth)
    {
        glGenTextures(1, &id);
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
    
    Texture::~Texture()
    {
        glDeleteTextures(1, &id);
    }
}
