#include <fea/rendering/texture.hpp>
#include <fea/assert.hpp>
#include <utility>
#include <string>

namespace fea
{
    Texture::Texture() : mId(0), mSize(0, 0), mInteractive(false), pixelData(nullptr)
    {
    }

    Texture::Texture(Texture&& other) : mId(0), mSize(0, 0), mInteractive(false), pixelData(nullptr)
    {
        std::swap(mId, other.mId);
        std::swap(mSize, other.mSize);
        std::swap(mInteractive, other.mInteractive);
        pixelData = std::move(other.pixelData);
    }
    
    Texture& Texture::operator=(Texture&& other)
    {
        std::swap(mId, other.mId);
        std::swap(mSize, other.mSize);
        std::swap(mInteractive, other.mInteractive);
        pixelData = std::move(other.pixelData);
        return *this;
    }

    GLuint Texture::getId() const
    {
        return mId;
    }

    void Texture::create(const glm::ivec2& size, const uint8_t* imageData, bool smooth, bool interactive)
    {
        FEA_ASSERT(size.x > 0 && size.y > 0, "Cannot create a texture with a width or height smaller than zero! Given dimensions are " + std::to_string(size.x) + " " + std::to_string(size.y));

        if(mId)
        {
            destroy();
        }

        mInteractive = interactive;
        mSize = size;
        
        glGenTextures(1, &mId);
        FEA_ASSERT(mId != 0, "Failed to create texture. Make sure there is a valid OpenGL context available!");
        glBindTexture(GL_TEXTURE_2D, mId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)size.x, (GLsizei)size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, smooth ? GL_LINEAR : GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, smooth ? GL_LINEAR : GL_NEAREST);

        glBindTexture(GL_TEXTURE_2D, 0);

        if(mInteractive)
        {
            uint32_t byteAmount = mSize.x * mSize.y * 4;
            pixelData = std::unique_ptr<uint8_t[]>(new uint8_t[byteAmount]);

            if(imageData)
                std::copy(imageData, imageData + byteAmount, pixelData.get());
        }
    }

    void Texture::create(const glm::ivec2& size, const Color& color, bool smooth, bool interactive)
    {
        FEA_ASSERT(size.x > 0 && size.y > 0, "Cannot create a texture with a width or height smaller than zero! Given dimensions are " + std::to_string(size.x) + " " + std::to_string(size.y));
        std::unique_ptr<uint8_t[]> pixels = std::unique_ptr<uint8_t[]>(new uint8_t[size.x * size.y * 4]);

        for(uint32_t x = 0; x < size.x; x++)
        {
            for(uint32_t y = 0; y < size.y; y++)
            {
                pixels[(x + y * size.x) * 4 + 0] = color.r();
                pixels[(x + y * size.x) * 4 + 1] = color.g();
                pixels[(x + y * size.x) * 4 + 2] = color.b();
                pixels[(x + y * size.x) * 4 + 3] = color.a();
            }
        }
        create(size, pixels.get(), smooth, interactive);
    }
    
    const glm::ivec2& Texture::getSize() const
    {
        return mSize;
    }

    void Texture::destroy()
    {
        if(mId)
        {
            glDeleteTextures(1, &mId);
            mId = 0;
            mSize = {0, 0};
            pixelData.release();
        }
    }
    
    void Texture::setPixel(const glm::ivec2& pixel, const Color& color)
    {
        FEA_ASSERT(pixel.x >= 0 && pixel.y >= 0 && pixel.x < mSize.x && pixel.y < mSize.y, "Trying to set pixel outside of the bounds of the texture. Accessing at " + std::to_string(pixel.x) + " " + std::to_string(pixel.y) + " and texture dimensions are " + std::to_string(mSize.x) + " " + std::to_string(mSize.y));
        uint32_t pixelIndex = (pixel.x + pixel.y * mSize.x) * 4;
        pixelData[pixelIndex    ] = color.r();
        pixelData[pixelIndex + 1] = color.g();
        pixelData[pixelIndex + 2] = color.b();
        pixelData[pixelIndex + 3] = color.a();
    }

    Color Texture::getPixel(const glm::ivec2& pixel) const
    {
        FEA_ASSERT(pixel.x >= 0 && pixel.y >= 0 && pixel.x < mSize.x && pixel.y < mSize.y, "Trying to get pixel outside of the bounds of the texture. Accessing at " + std::to_string(pixel.x) + " " + std::to_string(pixel.y) + " and texture dimensions are " + std::to_string(mSize.x) + " " + std::to_string(mSize.y));
        uint32_t pixelIndex = (pixel.x + pixel.y * mSize.x) * 4;
        return Color(pixelData[pixelIndex],
                         pixelData[pixelIndex + 1],
                         pixelData[pixelIndex + 2],
                         pixelData[pixelIndex + 3]);
    }

    uint8_t* Texture::getPixelData()
    {
        return pixelData.get();
    }

    const uint8_t* Texture::getPixelData() const
    {
        return pixelData.get();
    }


    void Texture::update()
    {
        FEA_ASSERT(mInteractive, "Cannot modify a non-interactive texture!");
        glBindTexture(GL_TEXTURE_2D, mId);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mSize.x, mSize.y, GL_RGBA, GL_UNSIGNED_BYTE, pixelData.get());
    }
    
    Texture::~Texture()
    {
        if(mId)
        {
            destroy();
        }
    }
}
