#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <featherkit/rendering/renderinfo.h>
#include <featherkit/rendering/colour.h>
#include <stdint.h>
#include <string>

namespace fea
{
    class Drawable2D
    {
        public:
            Drawable2D();
            const std::vector<float>& getVertices() const;
            void setPosition(const float x, const float y);
            void setPosition(const glm::vec2& p);
            const glm::vec2& getPosition() const;
            void translate(const float x, const float y);
            void translate(const glm::vec2& p);
            void setOrigin(const float x, const float y);
            void setOrigin(const glm::vec2& p);
            const glm::vec2& getOrigin() const;
            void setRotation(const float radians);
            float getRotation() const;
            void rotate(const float radians);
            void setScale(const float x, const float y);
            void setScale(const glm::vec2& s);
            const glm::vec2& getScale() const;
            void scale(const float x, const float y);
            void scale(const glm::vec2& s);
            void setParallax(float p);
            float getParallax() const;
            void setColour(const Colour& c);
            Colour getColour() const;
            void setOpacity(float o);
            float getOpacity() const;

            virtual RenderInfo getRenderInfo() const;
        protected:
            std::vector<float> vertices;
            std::vector<float> texCoords;
            std::vector<float> vertexColours;
            GLenum drawMode;
            glm::vec2 position;
            glm::vec2 origin;
            float rotation;
            glm::vec2 scaling;
            float parallax;
            Colour colour;
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
     *  @fn void Drawable2D::setPosition(const float x, const float y)
     *  @brief Set the position.
     *  @param x X position.
     *  @param y Y position.
     ***
     *  @fn void Drawable2D::setPosition(const glm::vec2& p)
     *  @brief Set the position using a vector.
     *  @param p Vector with the position.
     ***
     *  @fn const glm::vec2& Drawable2D::getPosition() const
     *  @brief Get the current position.
     *  @return A vector containing the position.
     ***
     *  @fn void Drawable2D::translate(const float x, const float y)
     *  @brief Move the Drawable2D.
     *  @param x Amount to move along the X axis.
     *  @param y Amount to move along the Y axis.
     ***
     *  @fn void Drawable2D::translate(const glm::vec2& p)
     *  @brief Move the Drawable2D using a vector.
     *  @param p Vector containing the amount to move.
     ***
     *  @fn void Drawable2D::setOrigin(const float x, const float y)
     *  @brief Set the origin point of the Drawable2D.
     *  
     *  The origin serves as the centre point. This is where the object will be centered and all rotation and scaling will happen around this point. Also, if the position is set, the origin will be equivalent to that position. 
     *  @param x X coordinate for the origin.
     *  @param y Y coordinate for the origin.
     ***
     *  @fn void Drawable2D::setOrigin(const glm::vec2& p)
     *  @brief Set the origin point of the Drawable2D, using a vector.
     *  
     *  The origin serves as the centre point. This is where the object will be centered and all rotation and scaling will happen around this point. Also, if the position is set, the origin will be equivalent to that position. 
     *  @param p Position to set the origin to.
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
     *  @fn void Drawable2D::setScale(const float x, const float y)
     *  @brief Set the scale factor.
     *  @param x Scale factor in the X axis.
     *  @param y Scale factor in the Y axis.
     ***
     *  @fn void Drawable2D::setScale(const glm::vec2& s)
     *  @brief Set the scale factor using a vector.
     *  @param s Vector containing the scale factor.
     ***
     *  @fn const glm::vec2& Drawable2D::getScale() const
     *  @brief Get the current scale.
     *  @return Vector containing the scale.
     ***
     *  @fn void Drawable2D::scale(const float x, const float y)
     *  @brief Scale the Drawable2D.
     *  @param x X scale factor.
     *  @param y Y scale factor.
     ***
     *  @fn void Drawable2D::scale(const glm::vec2& s)
     *  @brief Scale the Drawable2D using a vector.
     *  @param s Scale factor.
     ***
     *  @fn void Drawable2D::setParallax(float p)
     *  @brief Set the parallax.
     *  @param p Parallax factor.
     ***
     *  @fn float Drawable2D::getParallax() const
     *  @brief Get the parallax.
     *  @return Parallax factor.
     ***
     *  @fn void Drawable2D::setOpacity(float o)
     *  @brief Set the opacity.
     *  @param o Opacity.
     ***
     *  @fn float Drawable2D::getOpacity() const
     *  @brief Get the opacity.
     *  @return Opacity.
     ***
     *  @fn Colour Drawable2D::getColour() const
     *  @brief Get the colour.
     *  @return The colour of the drawable.
     ***
     ***
     *  @fn void Drawable2D::setColour(const glm::vec3& c)
     *  @brief Set the colour.
     *  @param Colour to set to.
     ***
     *  @fn virtual RenderInfo Drawable2D::getRenderInfo() const
     *  @brief Returns data used for rendering.
     *
     *  The returned RenderInfo struct contains vertex information useful for rendering with OpenGL or similar. See RenderInfo for more information.
     *  @return Render information.
     ***
     *  @var Drawable2D::vertices
     *  @brief List of all vertices.
     ***
     *  @var Drawable2D::texCoords
     *  @brief List of all texture coordinates.
     ***
     *  @var Drawable2D::vertexColours
     *  @brief List of all vertex colours.
     ***
     *  @var Drawable2D::drawMode
     *  @brief Which GL drawmode to use to render this drawable. 
     *
     *  See OpenGL documentation for available draw modes. 
     ***
     *  @var Drawable2D::position
     *  @brief Stores the position.
     ***
     *  @var Drawable2D::origin
     *  @brief Stores the origin point.
     ***
     *  @var Drawable2D::rotation
     *  @brief Rotation in radians.
     ***
     *  @var Drawable2D::scaling
     *  @brief Stores the scale factor.
     ***
     *  @var Drawable2D::parallax
     *  @brief Stores the parallax factor.
     ***
     *  @var Drawable2D::colour
     *  @brief Stores the colour.
     ***/
}
