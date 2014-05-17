#include <fea/rendering/texture.hpp>
#include <fea/assert.hpp>
#include <utility>
#include <string>

namespace fea
{
    Texture::Texture() : mId(0), mWidth(0), mHeight(0), mInteractive(false), pixelData(nullptr)
    {
    }

    Texture::Texture(Texture&& other) : mId(0), mWidth(0), mHeight(0), mInteractive(false), pixelData(nullptr)
    {
        std::swap(mId, other.mId);
        std::swap(mWidth, other.mWidth);
        std::swap(mHeight, other.mHeight);
        std::swap(mInteractive, other.mInteractive);
        pixelData = std::move(other.pixelData);
    }
    
    Texture& Texture::operator=(Texture&& other)
    {
        std::swap(mId, other.mId);
        std::swap(mWidth, other.mWidth);
        std::swap(mHeight, other.mHeight);
        std::swap(mInteractive, other.mInteractive);
        pixelData = std::move(other.pixelData);
        return *this;
    }

    GLuint Texture::getId() const
    {
        return mId;
    }

    void Texture::create(uint32_t width, uint32_t height, const uint8_t* imageData, bool smooth, bool interactive)
    {
        mInteractive = interactive;
        FEA_ASSERT(width > 0 && height > 0, "Cannot create a texture with a width or height smaller than zero! Given dimensions are " + std::to_string(width) + " " + std::to_string(height));
        mWidth = width;
        mHeight = height;

        if(mId)
        {
            destroy();
        }
        
        glGenTextures(1, &mId);
        FEA_ASSERT(mId != 0, "Failed to create texture. Make sure there is a valid OpenGL context available!");
        glBindTexture(GL_TEXTURE_2D, mId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)width, (GLsizei)height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, smooth ? GL_LINEAR : GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, smooth ? GL_LINEAR : GL_NEAREST);

        glBindTexture(GL_TEXTURE_2D, 0);

        if(mInteractive)
        {
            uint32_t byteAmount = mWidth * mHeight * 4;
            pixelData = std::unique_ptr<uint8_t[]>(new uint8_t[byteAmount]);

            if(imageData)
                std::copy(imageData, imageData + byteAmount, pixelData.get());
        }
    }

    void Texture::create(uint32_t width, uint32_t height, const Color& color, bool smooth, bool interactive)
    {
        std::unique_ptr<uint8_t[]> pixels = std::unique_ptr<uint8_t[]>(new uint8_t[width * height * 4]);

        for(uint32_t x = 0; x < width; x++)
        {
            for(uint32_t y = 0; y < height; y++)
            {
                pixels[(x + y * width) * 4 + 0] = color.rAsByte();
                pixels[(x + y * width) * 4 + 1] = color.gAsByte();
                pixels[(x + y * width) * 4 + 2] = color.bAsByte();
                pixels[(x + y * width) * 4 + 3] = color.aAsByte();
            }
        }
        create(width, height, pixels.get(), smooth, interactive);
    }
    
    glm::uvec2 Texture::getSize() const
    {
        return glm::uvec2(mWidth, mHeight);
    }

    void Texture::destroy()
    {
        if(mId)
        {
            glDeleteTextures(1, &mId);
            mId = 0;
            mWidth = 0;
            mHeight = 0;
            pixelData.release();
        }
    }
    
    void Texture::setPixel(uint32_t x, uint32_t y, const Color& color)
    {
        FEA_ASSERT(x >= 0 && y >= 0 && x < mWidth && y < mHeight, "Trying to set pixel outside of the bounds of the texture. Accessing at " + std::to_string(x) + " " + std::to_string(y) + " and texture dimensions are " + std::to_string(mWidth) + " " + std::to_string(mHeight));
        uint32_t pixelIndex = (x + y * mWidth) * 4;
        pixelData[pixelIndex    ] = color.rAsByte();
        pixelData[pixelIndex + 1] = color.gAsByte();
        pixelData[pixelIndex + 2] = color.bAsByte();
        pixelData[pixelIndex + 3] = color.aAsByte();
    }

    Color Texture::getPixel(uint32_t x, uint32_t y) const
    {
        FEA_ASSERT(x >= 0 && y >= 0 && x < mWidth && y < mHeight, "Trying to get pixel outside of the bounds of the texture. Accessing at " + std::to_string(x) + " " + std::to_string(y) + " and texture dimensions are " + std::to_string(mWidth) + " " + std::to_string(mHeight));
        uint32_t pixelIndex = (x + y * mWidth) * 4;
        return Color(pixelData[pixelIndex],
                         pixelData[pixelIndex + 1],
                         pixelData[pixelIndex + 2],
                         pixelData[pixelIndex + 3]);
    }

    uint8_t* Texture::getPixelData()
    {
        return pixelData.get();
    }


    void Texture::update()
    {
        FEA_ASSERT(mInteractive, "Cannot modify a non-interactive texture!");
        glBindTexture(GL_TEXTURE_2D, mId);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mWidth, mHeight, GL_RGBA, GL_UNSIGNED_BYTE, pixelData.get());
    }
    
    Texture::~Texture()
    {
        if(mId)
        {
            destroy();
        }
    }
}
