#pragma once
#include <fea/config.hpp>
#include <stdint.h>
#include <fea/rendering/opengl.hpp>
#include <fea/rendering/color.hpp>
#include <glm/glm.hpp>
#include <functional>
#include <vector>

namespace fea
{
    class FEA_API Texture
    {
        public:
            Texture();
            Texture(const Texture& other) = delete;
            Texture& operator=(const Texture& other) = delete;
            Texture(Texture&& other);
            Texture& operator=(Texture&& other);
            GLuint getId() const;
            void create(const glm::ivec2& size, const uint8_t* imageData, bool smooth = false);
            void create(const glm::ivec2& size, const Color& color, bool smooth = false);
            const glm::ivec2& getSize() const;
            void resize(const glm::ivec2& newSize);
            void destroy();
            void setPixel(const glm::ivec2& pixel, const Color& color);
            Color getPixel(const glm::ivec2& pixel) const;
            uint8_t* getPixelData();
            const uint8_t* getPixelData() const;
            void update();
            ~Texture();
        private:
            GLuint mId;
            glm::ivec2 mSize;
            bool mSmooth;
            std::vector<uint8_t> mPixelData;
    };
    /** @addtogroup Render2D
     *@{
     *  @class Texture
     *@}
     ***
     *  @class Texture
     *  @brief Container class for a texture resource that can be used by Drawable2D instances.
     *
     *  To use a texture, it needs to be created using the create function. Because Textures represents internal textures of the rendering system, they cannot be copied. Pixels can be accessed and updated at any time.
     *
     *  A Texture instance has to be kept alive as long as there are drawables using it, otherwise they will be rendered with an invalid Texture.
     ***
     *  @fn Texture::Texture()
     *  @brief Construct an uninitialized Texture.
     ***
     *  @fn Texture::Texture(Texture&& other)
     *  @brief Move constructor.
     *  @param other Other instance.
     ***
     *  @fn Texture::Texture(const Texture& other) = delete
     *  @brief Deleted copy constructor.
     *  @param other Instance to copy.
     ***
     *  @fn Texture& Texture::operator=(Texture&& other)
     *  @brief Move assignment operator.
     *  @param other Other instance.
     ***
     *  @fn Texture& Texture::operator=(const Texture& other)
     *  @brief Deleted assignment operator.
     *  @param other Other instance.
     ***
     *  @fn int32_t Texture::getId() const
     *  @brief Get the ID of the internal texture.
     ***
     *  @fn void Texture::create(const glm::ivec2 size, const uint8_t* imageData, bool smooth = false)
     *  @brief Create a texture from an image.
     *  
     *  When the texture is successfully created, it can be used by drawables. Keep in mind that the texture must be kept alive as long as it is in use by any drawable.
     *  Assert/undefined behavior when width or height is zero or less.
     *
     *  @param size of the texture in pixels.
     *  @param imageData Image to create the texture from. Must be in 32-bit RGBA format.
     *  @param smooth If this is true, the texture will be smoothed using nearest neighbor interpolation.
     ***
     *  @fn void Texture::create(const glm::ivec2 size, const Color& color, bool smooth = false)
     *  @brief Create a texture filled with a color.
     *  
     *  When the texture is successfully created, it can be used by drawables. Keep in mind that the texture must be kept alive as long as it is in use by any drawable
     *  Assert/undefined behavior when width or height is zero or less.
     *
     *  @param size of the texture in pixels.
     *  @param color Color to fill the texture with.
     *  @param smooth If this is true, the texture will be smoothed using nearest neighbor interpolation.
     ***
     *  @fn const glm::ivec2& Texture::getSize() const
     *  @brief Return the size of the texture.
     *  @return Texture size.
     ***
     *  @fn void Texture::resize(const glm::ivec2& newSize)
     *  @brief Resize the image while keeping image data
     *
     *  Reducing the size of the texture will crop the data from the top left corner. New space will be transparent.
     *  Assert/undefined behavior if size is zero or less in any dimension.
     *  @param newSize New size.
     ***
     *  @fn void Texture::destroy()
     *  @brief Release the resources used by the texture. The texture will be invalid afterwards.
     ***
     *  @fn void Texture::setPixel(const glm::ivec2 pixel, const Color& color)
     *  @brief Set the color of a particular pixel.
     *
     *  Setting a pixel using this method does not change the Texture until the Texture::update method has been called.
     *  Assert/undefined behavior when setting a pixel outside of the dimensions of the texture.
     *  @param pixel Pixel to set.
     *  @param color Color to set the pixel to.
     ***
     *  @fn Color Texture::getPixel(const glm::ivec2 pixel) const
     *  @brief Access the color value of a pixel.
     *
     *  Assert/undefined behavior when getting a pixel outside of the dimensions of the texture.
     *
     *  @param pixel Pixel to get.
     *  @return The color value of the pixel.
     ***
     *  @fn uint8_t* Texture::getPixelData()
     *  @brief Get internal pixel data.
     *
     *  Accessing the internal data can be important for intense manipulation of many pixels where performance is crucial. To be used with caution.
     *  Undefined behavior when data outside the texture dimensions are accessed.
     *  @return Data.
     ***
     *  @fn const uint8_t* Texture::getPixelData() const
     *  @brief Get internal pixel data.
     *
     *  Accessing the internal data can be important for intense accessing of pixels. To be used with caution.
     *  Undefined behavior when data outside the texture dimensions are accessed.
     *  @return Data.
     ***
     *  @fn void Texture::update()
     *  @brief Update the texture with any changes made using any of the Texture::setPixel methods.
     ***
     *  @fn Texture::~Texture()
     *  @brief Destruct a texture.
     **/
}
