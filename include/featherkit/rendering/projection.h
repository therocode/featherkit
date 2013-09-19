#pragma once
#include <featherkit/rendering/opengl.h>

namespace fea
{
    class Projection
    {
        public:
            void createOrthoProjection(GLfloat left, GLfloat right, GLfloat top, GLfloat bottom, GLfloat near, GLfloat far, GLfloat* matrix) const;
    };
}
