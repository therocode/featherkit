#include <fea/rendering/texture.hpp>
#include <fea/assert.hpp>
#include <utility>
#include <string>

namespace fea
{
    Texture::Texture() : mId(0), mSize(0, 0), mSmooth(false)
    {
    }

    Texture::Texture(Texture&& other) : mId(0), mSize(0, 0), mSmooth(false)
    {
        std::swap(mId, other.mId);
        std::swap(mSize, other.mSize);
        std::swap(mSmooth, other.mSmooth);
        mPixelData = std::move(other.mPixelData);
    }
    
    Texture& Texture::operator=(Texture&& other)
    {
        std::swap(mId, other.mId);
        std::swap(mSize, other.mSize);
        std::swap(mSmooth, other.mSmooth);
        mPixelData = std::move(other.mPixelData);
        return *this;
    }

    GLuint Texture::getId() const
    {
        return mId;
    }

    void Texture::create(const glm::ivec2& size, const uint8_t* imageData, bool smooth)
    {
        FEA_ASSERT(size.x > 0 && size.y > 0, "Cannot create a texture with a width or height smaller than zero! Given dimensions are " + std::to_string(size.x) + " " + std::to_string(size.y));

        if(mId)
        {
            destroy();
        }

        mSize = size;
        mSmooth = smooth;
        
        glGenTextures(1, &mId);
        FEA_ASSERT(mId != 0, "Failed to create texture. Make sure there is a valid OpenGL context available!");
        glBindTexture(GL_TEXTURE_2D, mId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)size.x, (GLsizei)size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, smooth ? GL_LINEAR : GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, smooth ? GL_LINEAR : GL_NEAREST);

        glBindTexture(GL_TEXTURE_2D, 0);

        uint32_t byteAmount = mSize.x * mSize.y * 4;
        mPixelData = std::vector<uint8_t>(byteAmount);

        if(imageData)
            std::copy(imageData, imageData + byteAmount, mPixelData.data());
    }

    void Texture::create(const glm::ivec2& size, const Color& color, bool smooth)
    {
        FEA_ASSERT(size.x > 0 && size.y > 0, "Cannot create a texture with a width or height smaller than zero! Given dimensions are " + std::to_string(size.x) + " " + std::to_string(size.y));
        std::vector<uint8_t> pixels(size.x * size.y * 4);

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
        create(size, pixels.data(), smooth);
    }
    
    const glm::ivec2& Texture::getSize() const
    {
        return mSize;
    }

    void Texture::resize(const glm::ivec2& newSize)
    {
        FEA_ASSERT(newSize.x > 0 && newSize.y > 0, "Size must be bigger than zero in both dimensions! Given size is " << newSize.x << " " << newSize.y);

        std::vector<uint8_t> newPixels(newSize.x * newSize.y * 4, 0);

        int32_t newWidth = newSize.x;
        int32_t currentWidth = mSize.x;

        for(uint32_t x = 0; x < mSize.x && x < newSize.x; x++)
        {   
            for(uint32_t y = 0; y < mSize.y < newSize.y; y++)
            {   
                newPixels[(x + y * newWidth) * 4 + 0] = mPixelData[(x + y * currentWidth) * 4 + 0]; 
                newPixels[(x + y * newWidth) * 4 + 1] = mPixelData[(x + y * currentWidth) * 4 + 1]; 
                newPixels[(x + y * newWidth) * 4 + 2] = mPixelData[(x + y * currentWidth) * 4 + 2]; 
                newPixels[(x + y * newWidth) * 4 + 3] = mPixelData[(x + y * currentWidth) * 4 + 3]; 
            }   
        }   

        create(newSize, newPixels.data(), mSmooth);
    }

    void Texture::destroy()
    {
        if(mId)
        {
            glDeleteTextures(1, &mId);
            mId = 0;
            mSize = {0, 0};
            mSmooth = false;
            mPixelData = std::vector<uint8_t>();
        }
    }
    
    void Texture::setPixel(const glm::ivec2& pixel, const Color& color)
    {
        FEA_ASSERT(pixel.x >= 0 && pixel.y >= 0 && pixel.x < mSize.x && pixel.y < mSize.y, "Trying to set pixel outside of the bounds of the texture. Accessing at " + std::to_string(pixel.x) + " " + std::to_string(pixel.y) + " and texture dimensions are " + std::to_string(mSize.x) + " " + std::to_string(mSize.y));
        uint32_t pixelIndex = (pixel.x + pixel.y * mSize.x) * 4;
        mPixelData[pixelIndex    ] = color.r();
        mPixelData[pixelIndex + 1] = color.g();
        mPixelData[pixelIndex + 2] = color.b();
        mPixelData[pixelIndex + 3] = color.a();
    }

    Color Texture::getPixel(const glm::ivec2& pixel) const
    {
        FEA_ASSERT(pixel.x >= 0 && pixel.y >= 0 && pixel.x < mSize.x && pixel.y < mSize.y, "Trying to get pixel outside of the bounds of the texture. Accessing at " + std::to_string(pixel.x) + " " + std::to_string(pixel.y) + " and texture dimensions are " + std::to_string(mSize.x) + " " + std::to_string(mSize.y));
        uint32_t pixelIndex = (pixel.x + pixel.y * mSize.x) * 4;
        return Color(mPixelData[pixelIndex],
                         mPixelData[pixelIndex + 1],
                         mPixelData[pixelIndex + 2],
                         mPixelData[pixelIndex + 3]);
    }

    uint8_t* Texture::getPixelData()
    {
        return mPixelData.data();
    }

    const uint8_t* Texture::getPixelData() const
    {
        return mPixelData.data();
    }


    void Texture::update()
    {
        glBindTexture(GL_TEXTURE_2D, mId);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mSize.x, mSize.y, GL_RGBA, GL_UNSIGNED_BYTE, mPixelData.data());
    }
    
    Texture::~Texture()
    {
        if(mId)
        {
            destroy();
        }
    }
}
