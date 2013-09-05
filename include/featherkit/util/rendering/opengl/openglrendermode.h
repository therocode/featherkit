#pragma once
#include <featherkit/rendering/rendermode.h>
#include <featherkit/util/rendering/opengl/opengl.h>

namespace fea
{
    namespace util
    {
        class OpenGLRenderMode : public RenderMode
        {
            public:
                virtual void setup() override = 0;
                virtual void preRender() override = 0;
                virtual void postRender() override = 0;
                void cacheUniforms();
                void updateProjection(float* matrix) const;
          
                GLuint shaderProgram;
                GLint vertexLocation;
                GLint texCoordsLocation;
                GLint projectionLocation;
                GLint positionUniform;
                GLint zoomUniform;
                GLint rotationUniform;
                GLint halfSizeUniform;
                GLint constrainXUniform;
                GLint constrainYUniform;
                GLint textureScroll;
                GLint parallax;
                GLint colour;
                GLint opacity;
        };
    }
}
