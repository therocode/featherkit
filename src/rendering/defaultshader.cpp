#include <featherkit/rendering/defaultshader.h>

namespace fea
{
    std::string DefaultShader::vertexSource = R"(
uniform mat4 projection;   
uniform vec2 camZoom;      
uniform vec2 camPosition;  
uniform mat2 camRotation;  
uniform vec2 halfViewSize; 

attribute vec4 vertex;
attribute vec2 texCoords;
uniform vec2 position;
uniform vec2 origin;
uniform float rotation;
uniform vec2 scaling;
uniform float parallax;

varying vec2 vTex;

void main()
{
    float sinRot = sin(rotation);
    float cosRot = cos(rotation);
    mat2 rotMat = mat2(cosRot, sinRot, -sinRot, cosRot);

    vec2 worldSpaceCoords = (rotMat * (scaling * vertex.xy - origin)) + position;
    vec2 transformedPoint = camRotation * (camZoom * (worldSpaceCoords - camPosition * parallax)) + halfViewSize;
    gl_Position = projection* vec4(transformedPoint.xy, vertex.zw);
    vTex = texCoords;
})";

    std::string DefaultShader::fragmentSource = R"(
//#ifdef EMSCRIPTEN
//precision mediump float;
//#else

//#endif
uniform sampler2D texture;
uniform vec4 constraints;
uniform vec3 colour;
uniform float opacity;
uniform vec2 textureScroll; //hmmmm

varying vec2 vTex;

float boundBetween(float val, float lowerBound, float upperBound)
{
    if(lowerBound > upperBound)
    {
        float temp = lowerBound;
        lowerBound = upperBound;
        upperBound = temp;
    }
    
    val = val - lowerBound;
    float rangeSize = upperBound - lowerBound;
    if(rangeSize == 0.0)
    {
        return upperBound;
    }
    return val - (rangeSize * floor(val/rangeSize)) + lowerBound;
}

void main()
{

    vec2 constraintSize = abs(vec2(constraints[1] - constraints[0] , constraints[3] - constraints[2]));
    vec2 texCoords = constraintSize * vTex.st + vec2(constraints[0], constraints[2]) - textureScroll;
    texCoords = vec2(boundBetween(texCoords.s, constraints[0], constraints[1]), boundBetween(texCoords.t, constraints[2], constraints[3]));
    gl_FragColor = texture2D(texture, texCoords) * vec4(colour, opacity);
})";
}
