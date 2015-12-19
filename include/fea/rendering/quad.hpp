#pragma once
#include <fea/config.hpp>
#include <fea/rendering/drawable2d.hpp>
#include <fea/rendering/texture.hpp>

namespace fea
{
    class FEA_API Quad : public Drawable2D
    {
        public:
            Quad();
            virtual ~Quad() = default;
            Quad(const glm::vec2& size);
            virtual void setSize(const glm::vec2& size);
            const glm::vec2& getSize() const;
            virtual void setTexture(const Texture& texture);
            const Texture& getTexture() const;
            void setHFlip(bool enabled);
            void setVFlip(bool enabled);

            virtual void updateRenderInfo(std::vector<RenderEntity>& renderInfo, bool updateVertices, bool updateUniforms) const override;
        protected:
            float mHFlip;
            float mVFlip;
            const Texture* mTexture;
            glm::vec4 mConstraints;
            glm::vec2 mSize;
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
     *  @fn Quad::Quad(const glm::vec2& size)
     *  @brief Construct a quad with the given size.
     *
     *  Assert/undefined behavior if size is zero or less in any dimension.
     *  @param size Size.
     ***
     *  @fn void Quad::setSize(glm::vec2 size)
     *  @brief Resize the quad.
     *
     *  Assert/undefined behavior if size is zero or less in any dimension.
     *  @param size Vector with the new size.
     ***
     *  @fn const glm::vec2& Quad::getSize() const
     *  @brief Get the size.
     *  @return Size as a vector.
     ***
     *  @fn void Quad::setTexture(const Texture& texture)
     *  @brief Set the texture.
     *  @param texture Texture to set.
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
     *  @var Quad::mHFlip
     *  @brief Internal variable representing if the Quad will be drawn mirrored horizontally or not.
     ***
     *  @var Quad::mVFlip
     *  @brief Internal variable representing if the Quad will be drawn mirrored vertically or not.
     ***
     *  @var Quad::mTexture
     *  @brief Pointer to the current texture in use.
     ***
     *  @var Quad::mConstraints
     *  @brief Vector describing the texture constraints.
     *
     *  Texture constraints are used to "lock" the texture displayed on the quad to a certain region of the texture. This can be used for instance to create animations or wrapping type of effects. The first two ints define the starting point of the constraint rectangle and the second two ints define the end point. In percent
     ***
     *  @var Quad::mSize
     *  @brief Vector describing the size of the quad
     ***/
}
