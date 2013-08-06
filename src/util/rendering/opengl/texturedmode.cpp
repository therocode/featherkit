#include <featherkit/util/rendering/opengl/texturedmode.h>
#include <featherkit/util/rendering/opengl/glslloader.h>
#include <string>

namespace fea
{
    namespace util
    {
        void TexturedMode::setup()
        {

            std::string vertexShaderSource = "#version 120\n"
                "\n"
                "uniform vec2 position;\n"
                "uniform vec2 zoom;\n"
                "uniform mat2 rotation;\n"
                "uniform vec2 halfViewSize;\n"
                "uniform float parallax;"
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
                "uniform sampler2D texture;\n"
                "uniform vec2 constrainX;\n"
                "uniform vec2 constrainY;\n"
                "uniform vec2 textureScroll;"
                "\n"
                "float boundBetween(float val, float lowerBound, float upperBound)\n"
                "{\n"
                "    if(lowerBound > upperBound)\n"
                "    {\n"
                "        float temp = lowerBound;\n"
                "        lowerBound = upperBound;\n"
                "        upperBound = temp;\n"
                "    }\n"
                "    \n"
                "    val = val - lowerBound;\n"
                "    float rangeSize = upperBound - lowerBound;\n"
                "    if(rangeSize == 0)\n"
                "    {\n"
                "        return upperBound;\n"
                "    }\n"
                "    return val - (rangeSize * floor(val/rangeSize)) + lowerBound;\n"
                "}\n"
                "\n"
                "void main()\n"
                "{\n"
                "\n"
                "    vec2 constraintSize = abs(vec2(constrainX[1] - constrainX[0] , constrainY[1] - constrainY[0]));\n"
                "    vec2 texCoords = constraintSize * gl_TexCoord[0].st + vec2(constrainX[0], constrainY[0]) - textureScroll;\n"
                "    texCoords = vec2(boundBetween(texCoords.s, constrainX[0], constrainX[1]), boundBetween(texCoords.t, constrainY[0], constrainY[1]));\n"
                "    gl_FragColor = texture2D(texture, texCoords);\n"
                "}\n"
                "";

            GLSLLoader loader;
            shaderProgram = loader.createShader(vertexShaderSource, fragmentShaderSource);
        }

        void TexturedMode::preRender()
        {
            glUseProgram(shaderProgram);

            GLint textureUniform = glGetUniformLocation(shaderProgram, "texture");
            glActiveTexture(GL_TEXTURE0);
            glUniform1i(textureUniform, 0);
        }

        void TexturedMode::postRender()
        {
            glUseProgram(0);
        }
    }
}
