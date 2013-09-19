#include <featherkit/rendering/projection.h>
#include <glm/gtc/type_ptr.hpp>

namespace fea
{
    glm::mat4x4 Projection::createOrthoProjection(GLfloat left, GLfloat right, GLfloat top, GLfloat bottom, GLfloat near, GLfloat far) const
    {
        GLfloat r_l = right - left;
        GLfloat t_b = top - bottom;
        GLfloat f_n = far - near;
        GLfloat tx = -(right + left) / (right - left);
        GLfloat ty = -(top + bottom) / (top - bottom);
        GLfloat tz = -(far + near) / (far - near);

        float matrix[16];

        matrix[0] = 2.0f / r_l;
        matrix[4] = 0.0f;
        matrix[8] = 0.0f;
        matrix[12] = tx;

        matrix[1] = 0.0f;
        matrix[5] = 2.0f / t_b;
        matrix[9] = 0.0f;
        matrix[13] = ty;

        matrix[2] = 0.0f;
        matrix[6] = 0.0f;
        matrix[10] = 2.0f / f_n;
        matrix[14] = tz;

        matrix[3] = 0.0f;
        matrix[7] = 0.0f;
        matrix[11] = 0.0f;
        matrix[15] = 1.0f;

        glm::mat4x4 glmMat = glm::make_mat4(matrix);

        return glmMat;
    }
}
