#include <featherkit/rendering/texture.h>
#include <featherkit/assert.h>
#include <utility>


namespace fea
{
    Texture::Texture() : id(0), mWidth(0), mHeight(0), mInteractive(false), pixelData(nullptr)
    {
    }

    Texture::Texture(Texture&& other) : id(0), mWidth(0), mHeight(0), mInteractive(false), pixelData(nullptr)
    {
        std::swap(id, other.id);
        std::swap(mWidth, other.mWidth);
        std::swap(mHeight, other.mHeight);
        std::swap(mInteractive, other.mInteractive);
        pixelData = std::move(other.pixelData);
    }
    
    Texture& Texture::operator=(Texture&& other)
    {
        std::swap(id, other.id);
        std::swap(mWidth, other.mWidth);
        std::swap(mHeight, other.mHeight);
        std::swap(mInteractive, other.mInteractive);
        pixelData = std::move(other.pixelData);
        return *this;
    }

    GLuint Texture::getId() const
    {
        return id;
    }

    void Texture::create(uint32_t width, uint32_t height, const uint8_t* imageData, bool smooth, bool interactive)
    {
        mInteractive = interactive;
        FEA_ASSERT(width > 0 && height > 0, "Cannot create a texture with a width or height smaller than zero! Given dimensions are " + std::to_string(width) + " " + std::to_string(height));
        mWidth = width;
        mHeight = height;

        if(id)
        {
            destroy();
        }
        
        glGenTextures(1, &id);
        FEA_ASSERT(id != 0, "Failed to create texture. Make sure there is a valid OpenGL context available!");
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)w, (GLsizei)h, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

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

    void Texture::create(uint32_t width, uint32_t height, const Colour& colour, bool smooth, bool interactive)
    {
        std::unique_ptr<uint8_t[]> pixels = std::unique_ptr<uint8_t[]>(new uint8_t[weight * height * 4]);

        for(uint32_t x = 0; x < width; x++)
        {
            for(uint32_t y = 0; y < height; y++)
            {
                pixels[(x + y * width) * 4 + 0] = colour.rAsByte();
                pixels[(x + y * width) * 4 + 1] = colour.gAsByte();
                pixels[(x + y * width) * 4 + 2] = colour.bAsByte();
                pixels[(x + y * width) * 4 + 3] = colour.aAsByte();
            }
        }
        create(width, height, pixels.get(), smooth, interactive);
    }

    void Texture::destroy()
    {
        if(id)
        {
            glDeleteTextures(1, &id);
            id = 0;
            mWidth = 0;
            mHeight = 0;
            pixelData.release();
        }
    }
    
    void Texture::setPixel(uint32_t x, uint32_t y, const Colour& colour)
    {
        FEA_ASSERT(x >= 0 && y >= 0 && x < mWidth && y < mHeight, "Trying to access pixel outside of the bounds of the texture. Accessing at " + std::to_string(x) + " " + std::to_string(y));
        uint32_t pixelIndex = (x + y * mWidth) * 4;
        pixelData[pixelIndex    ] = colour.rAsByte();
        pixelData[pixelIndex + 1] = colour.gAsByte();
        pixelData[pixelIndex + 2] = colour.bAsByte();
        pixelData[pixelIndex + 3] = colour.aAsByte();
    }

    Colour Texture::getPixel(uint32_t x, uint32_t y) const
    {
        FEA_ASSERT(x >= 0 && y >= 0 && x < mWidth && y < mHeight, "Trying to access pixel outside of the bounds of the texture. Accessing at " + std::to_string(x) + " " + std::to_string(y));
        uint32_t pixelIndex = (x + y * mWidth) * 4;
        return Colour(pixelData[pixelIndex],
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
        glBindTexture(GL_TEXTURE_2D, id);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mWidth, mHeight, GL_RGBA, GL_UNSIGNED_BYTE, pixelData.get());
    }
    
    Texture::~Texture()
    {
        if(id)
        {
            destroy();
        }
    }
}
