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
                "uniform vec2 position;\n"
                "uniform vec2 zoom;\n"
                "uniform mat2 rotation;\n"
                "uniform vec2 halfViewSize;\n"
                "uniform float parallax;\n"
                "\n"
                "void main()\n"
                "{\n"
                "    vec2 transformedPoint = rotation * (zoom * (gl_Vertex.xy - position * parallax)) + halfViewSize;\n"
                "    gl_Position = vec4(transformedPoint.xy, gl_Vertex.zw);\n"
                "    gl_Position = gl_ProjectionMatrix * (gl_Position);\n"
                "    gl_TexCoord[0]  = gl_MultiTexCoord0;\n"
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
