#pragma once
#include <framework/rendering/drawable2d.h>

namespace windbreeze
{
    class Quad : public Drawable2D
    {
        public:
            Quad();
            Quad(float w, float h);
            void setSize(float w, float h);
            void setSize(glm::vec2 size);
            glm::vec2 getSize() const;
            void setTexture(const std::string& tex);
            const std::string& getTexture() const;
            void setHFlip(bool enabled);
            void setVFlip(bool enabled);
            virtual void getRenderData(RenderData& renderData, uint32_t time) const override;
        protected:
            std::string textureId;
            float hFlip = 1.0f;
            float vFlip = 1.0f;
    };
    /** @addtogroup Render2D
     *@{
     *  @class Quad
     *@}
     ***
     *  @class Quad
     *  @brief A simple quad that can be drawn using the Renderer2D.
     *
     *  This Drawable2D always has four vertices aligned in a rectangle shape. It might still be scaled, rotated or transformed like any other Drawable2D. Supports texturing, with options for flipping them along both axes. Additionally to the scale, this Drawable2D also has a size which defines the distance between the vertices when scale is 1.0f.
     ***
     *  @fn Quad::Quad()
     *  @brief Construct a quad.
     *
     *  The size will be 1.0f * 1.0f.
     ***
     *  @fn Quad::Quad(float w, float h)
     *  @brief Construct a quad with the given size.
     *  @param w Width.
     *  @param h Height.
     ***
     *  @fn Quad::void Quad::setSize(float w, float h)
     *  @brief Resize the Quad.
     *  @param w New width.
     *  @param h New height.
     ***
     *  @fn void Quad::setSize(glm::vec2 size)
     *  @brief Resize the quad.
     *  @param size Vector with the new size.
     ***
     *  @fn glm::vec2 Quad::getSize() const
     *  @brief Get the size.
     *  @return Size as a vector.
     ***
     *  @fn void Quad::setTexture(const std::string& tex)
     *  @brief Set the texture.
     *  @param tex Name of the texture to set.
     ***
     *  @fn const std::string& Quad::getTexture() const
     *  @brief Get the texture.
     *  @return The texture.
     ***
     *  @fn void Quad::setHFlip(bool enabled)
     *  @brief Flips the texture horizontally. 
     *  
     *  For instance, a texture of a face pointing left would turn into a face pointing right.
     *  @param enabled If true, horizontal flip will be enabled.
     ***
     *  @fn void Quad::setVFlip(bool enabled)
     *  @brief Flips the texture vertically. 
     *  
     *  For instance, a texture of a tree would turn into an upside down tree.
     *  @param enabled If true, vertical flip will be enabled.
     ***
     *  @fn virtual void Quad::getRenderData(RenderData& renderData, uint32_t time) const override
     *  @brief Overrides Drawable2D::getRenderData.
     *  @param renderData See Drawable2D::getRenderData.
     *  @param time See Drawable2D::getRenderData.
     ***
     *  @var Quad::textureId
     *  @brief Name of the texture that the Quad will use when being rendered.
     ***
     *  @var Quad::hFlip
     *  @brief Internal variable representing if the Quad will be drawn mirrored horizontally or not.
     ***
     *  @var Quad::vFlip
     *  @brief Internal variable representing if the Quad will be drawn mirrored vertically or not.
     ***/
}
