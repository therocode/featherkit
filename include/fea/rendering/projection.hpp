#pragma once
#include <fea/rendering/opengl.hpp>
#include <glm/glm.hpp>

namespace fea
{
    class Projection
    {
        public:
            glm::mat4x4 createOrthoProjection(GLfloat left, GLfloat right, GLfloat top, GLfloat bottom, GLfloat near, GLfloat far) const;
    };
}
