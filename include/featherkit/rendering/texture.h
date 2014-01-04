#pragma once
#include <stdint.h>
#include <featherkit/rendering/opengl.h>
#include <glm/glm.hpp>
#include <functional>

namespace fea
{
    class Texture
    {
        public:
            Texture();
            Texture(Texture&& other);
            Texture(const Texture& other) = delete;
            Texture& operator=(Texture&& other);
            GLuint getId() const;
            void create(uint32_t w, uint32_t h, const uint8_t* imageData, bool smooth = false, bool interactive = false);
            void create(uint32_t w, uint32_t h, const glm::vec3& colour, bool smooth = false, bool interactive = false);
            void create(uint32_t w, uint32_t h, float r, float g, float b, bool smooth = false, bool interactive = false);
            void destroy();
            void setPixel(uint32_t x, uint32_t y, float r, float g, float b, float a = 1.0f);
            void setPixelAsByte(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
            void setPixels(std::function<void(uint32_t x, uint32_t y, uint8_t* pixels)> f);
            glm::vec4 getPixel(uint32_t x, uint32_t y) const;
            glm::uvec4 getPixelAsByte(uint32_t x, uint32_t y) const;
            void update();
            ~Texture();
        private:
            GLuint id;
            uint32_t width;
            uint32_t height;
            uint8_t* pixelData;
    };
    /** @addtogroup Render2D
     *@{
     *  @class Texture
     *@}
     ***
     *  @class Texture
     *  @brief Container class for a texture resource that can be used by Drawable2D instances.
     *
     *  Textures are tied to the rendering system and cannot be created properly on its own. Textures created using the standard constructor will not be valid. To properly create a Texture, use the Renderer2D::createTexture function. Because Textures represents internal textures of the rendering system, they cannot be copied. 
     *
     *  A Texture instance has to be kept alive as long as there are drawables using it, otherwise they will try to render with an invalid Texture.
     ***
     *  @fn Texture::Texture()
     *  @brief Construct an uninitialised Texture.
     *
     *  Textures created this way need to be set to a valid Texture returned by the Renderer2D::createTexture function.
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
     *  @fn int32_t Texture::getId() const
     *  @brief Get the ID of the internal texture.
     ***
     *  @fn Texture::~Texture()
     *  @brief Destruct a texture.
     **/
}
