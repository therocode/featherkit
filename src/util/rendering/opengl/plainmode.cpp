#include <featherkit/util/rendering/opengl/plainmode.h>
#include <featherkit/util/rendering/opengl/glslloader.h>
#include <string>

namespace fea
{
    namespace util
    {
        void PlainMode::setup()
        {

            std::string vertexShaderSource = "#version 120\n"
                "\n"
                "attribute vec4 vertex;\n"
                "attribute vec2 texCoords;\n"
                "uniform mat4 projection;\n"
                "uniform vec2 position;\n"
                "uniform vec2 zoom;\n"
                "uniform mat2 rotation;\n"
                "uniform vec2 halfViewSize;\n"
                "uniform float parallax;\n"
                "\n"
                "void main()\n"
                "{\n"
                "    vec2 transformedPoint = rotation * (zoom * (vertex.xy - position * parallax)) + halfViewSize;\n"
                "    gl_Position = vec4(transformedPoint.xy, vertex.zw);\n"
                "    gl_Position = projection * (gl_Position);\n"
                "}\n"
                "";

            std::string fragmentShaderSource = "#version 120\n"
                "\n"
                "uniform vec2 constrainX;\n"
                "uniform vec2 constrainY;\n"
                "uniform vec2 textureScroll;\n"
                "uniform vec3 colour;\n"
                "uniform float opacity;\n"
                "\n"
                "void main()\n"
                "{\n"
                "\n"
                "    gl_FragColor = vec4(colour, opacity);\n"
                "}\n"
                "";

            GLSLLoader loader;
            shaderProgram = loader.createShader(vertexShaderSource, fragmentShaderSource);
            vertexLocation = glGetAttribLocation(shaderProgram, "vertex");
            texCoordsLocation = glGetAttribLocation(shaderProgram, "texCoords");
        }

        void PlainMode::preRender()
        {
            glUseProgram(shaderProgram);
        }

        void PlainMode::postRender()
        {
            glUseProgram(0);
        }
    }
}
