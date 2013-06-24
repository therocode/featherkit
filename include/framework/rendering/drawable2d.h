#pragma once
#include <vector>
#include <framework/glm/glm.hpp>
#include <framework/rendering/renderdata.h>
#include <stdint.h>
#include <string>

namespace windbreeze
{
    class Drawable2D
    {
        public:
            const std::vector<float>& getVertices() const;
            std::vector<float> getVerticesTransformed() const;
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
            void addTransformation(const glm::mat2x2& t);
            const glm::mat2x2& getTransformation(uint32_t index) const;
            uint32_t getTransformationCount() const;
            void clearTransformations();
            virtual void getRenderData(RenderData& renderData, uint32_t time) const;
            AABB getAABB() const;

            bool isText = false; //OJOJOJOJOJOJ ugly hack
        protected:
            std::vector<float> vertices;
            glm::vec2 position;
            glm::vec2 origin;
            float rotation = 0.0f;
            glm::vec2 scaling = glm::vec2(1.0f, 1.0f);
            float parallax = 1.0f;

            std::vector<glm::mat2x2> transformations;
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
     *  An ingeriting object describes how it should be drawn by implementing the Drawable2D::getRenderData function and filling the provided RenderData instance with the necessary information. For instance, a Quad will fill it with four vertices, while another shape might fill it with more.
     ***
     *  @fn const std::vector<float>& Drawable2D::getVertices() const
     *  @brief Get all the vertices of a drawable.
     *  @return Vector containing the vertices.
     ***
     *  @fn std::vector<float> Drawable2D::getVerticesTransformed() const
     *  @brief Get all the vertices with the objects' transformation applied. The resulting vertices are described in world space.
     *  @return Vector containing the transformed vertices.
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
     ***/
}
