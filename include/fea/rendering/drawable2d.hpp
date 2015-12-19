#pragma once
#include <fea/config.hpp>
#include <vector>
#include <unordered_map>
#include <glm/glm.hpp>
#include <fea/rendering/renderentity.hpp>
#include <fea/rendering/color.hpp>
#include <stdint.h>
#include <string>

namespace fea
{
    class FEA_API Drawable2D
    {
        public:
            Drawable2D();
            virtual ~Drawable2D() = default;
            const std::vector<float>& getVertices() const;
            void setPosition(const glm::vec2& position);
            const glm::vec2& getPosition() const;
            void translate(const glm::vec2& amount);
            void setOrigin(const glm::vec2& position);
            const glm::vec2& getOrigin() const;
            void setRotation(const float radians);
            float getRotation() const;
            void rotate(const float radians);
            void setScale(const glm::vec2& scale);
            const glm::vec2& getScale() const;
            void scale(const glm::vec2& amount);
            void setParallax(const glm::vec2& parallax);
            const glm::vec2& getParallax() const;
            void setColor(const Color& color);
            Color getColor() const;
            void setOpacity(float opacity);
            float getOpacity() const;

            const std::vector<RenderEntity>& getRenderInfo() const;
            virtual void updateRenderInfo(std::vector<RenderEntity>& renderInfo, bool updateVertices, bool updateUniforms) const;
        protected:
            std::vector<float> mVertices;
            std::vector<float> mTexCoords;
            std::vector<float> mVertexColors;
            GLenum mDrawMode;
            glm::vec2 mPosition;
            glm::vec2 mOrigin;
            float mRotation;
            glm::vec2 mScaling;
            glm::vec2 mParallax;
            Color mColor;

            //cache
            mutable bool mVerticesDirty;
            mutable bool mUniformsDirty;
            mutable std::vector<RenderEntity> mRenderInfo;
    };
    /** @addtogroup Render2D
     *@{
     *  @class Drawable2D
     *@}
     ***
     *  @class Drawable2D
     *  @brief Base class for an object which is possible to render using the Renderer2D class. 
     *
     *  This base class contains information which is vital to all rendered objects, such as position, scale, rotation, and so on. It does not contain specific information nor functionality on how a specific drawable should be drawn, that is up to the inheriting object.
     *
     *  An inheriting object describes how it should be drawn by implementing the Drawable2D::getRenderData function and filling the provided RenderData instance with the necessary information. For instance, a Quad will fill it with four vertices, while another shape might fill it with more.
     ***
     *  @fn const std::vector<float>& Drawable2D::getVertices() const
     *  @brief Get all the vertices of a drawable.
     *  @return Vector containing the vertices.
     ***
     *  @fn void Drawable2D::setPosition(const glm::vec2& position)
     *  @brief Set the position using a vector.
     *  @param position Vector with the position.
     ***
     *  @fn const glm::vec2& Drawable2D::getPosition() const
     *  @brief Get the current position.
     *  @return A vector containing the position.
     ***
     *  @fn void Drawable2D::translate(const glm::vec2& amount)
     *  @brief Move the Drawable2D using a vector.
     *  @param amount Vector containing the amount to move.
     ***
     *  @fn void Drawable2D::setOrigin(const glm::vec2& position)
     *  @brief Set the origin point of the Drawable2D, using a vector.
     *  
     *  The origin serves as the center point. This is where the object will be centered and all rotation and scaling will happen around this point. Also, if the position is set, the origin will be equivalent to that position. 
     *  @param position Position to set the origin to.
     ***
     *  @fn const glm::vec2& Drawable2D::getOrigin() const
     *  @brief Get the origin point of the Drawable2D.
     *  @return Vector containing the origin.
     ***
     *  @fn void Drawable2D::setRotation(const float radians)
     *  @brief Set the rotation.
     *  @param radians Rotation angle in radians.
     ***
     *  @fn float Drawable2D::getRotation() const
     *  @brief Get the current rotation.
     *  @return The rotation.
     ***
     *  @fn void Drawable2D::rotate(const float radians)
     *  @brief Rotate the Drawable2D a specific amount.
     *  @param radians Amount in radians to rotate the Drawable2D.
     ***
     *  @fn void Drawable2D::setScale(const glm::vec2& scale)
     *  @brief Set the scale factor using a vector.
     *  @param scale Vector containing the scale factor.
     ***
     *  @fn const glm::vec2& Drawable2D::getScale() const
     *  @brief Get the current scale.
     *  @return Vector containing the scale.
     ***
     *  @fn void Drawable2D::scale(const glm::vec2& amount)
     *  @brief Scale the Drawable2D using a vector.
     *  @param amount Scale factor.
     ***
     *  @fn void Drawable2D::setParallax(const glm::vec2& parallax)
     *  @brief Set the parallax factor for each x and y axis separately.
     *  
     *  The factor determines how much the drawable moves relative to the camera. 
     *  A value of 1.0f is neutral, 0.5f is twice as slowly and 2.0f is twice as fast.
     *  @param parallax Parallax factor.
     ***
     *  @fn glm::vec2 Drawable2D::getParallax() const
     *  @brief Get the parallax factors as a vector.
     *  @return Parallax factor.
     ***
     *  @fn void Drawable2D::setOpacity(float opacity)
     *  @brief Set the opacity.
     *
     *  Assert/undefined behavior if the values is not within the range of [0.0f,1.0f].
     *  @param opacity Opacity.
     ***
     *  @fn float Drawable2D::getOpacity() const
     *  @brief Get the opacity.
     *  @return Opacity.
     ***
     *  @fn Color Drawable2D::getColor() const
     *  @brief Get the color.
     *  @return The color of the drawable.
     ***
     *  @fn void Drawable2D::setColor(const Color& color)
     *  @brief Set the color.
     *  @param color Color to set to.
     ***
     *  @fn virtual RenderEntity Drawable2D::getRenderInfo() const
     *  @brief Returns data used for rendering.
     *
     *  The returned array contains RenderEntity instances which contain vertex information useful for rendering with OpenGL or similar. See RenderEntity for more information.
     *  @return Render information.
     ***
     *  @var Drawable2D::mVertices
     *  @brief List of all vertices.
     ***
     *  @var Drawable2D::mTexCoords
     *  @brief List of all texture coordinates.
     ***
     *  @var Drawable2D::mVertexColors
     *  @brief List of all vertex colors.
     ***
     *  @var Drawable2D::mDrawMode
     *  @brief Which GL drawmode to use to render this drawable. 
     *
     *  See OpenGL documentation for available draw modes. 
     ***
     *  @var Drawable2D::mPosition
     *  @brief Stores the position.
     ***
     *  @var Drawable2D::mOrigin
     *  @brief Stores the origin point.
     ***
     *  @var Drawable2D::mRotation
     *  @brief Rotation in radians.
     ***
     *  @var Drawable2D::mScaling
     *  @brief Stores the scale factor.
     ***
     *  @var Drawable2D::mParallax
     *  @brief Stores the parallax factor.
     ***
     *  @var Drawable2D::mColor
     *  @brief Stores the color.
     ***/
}
