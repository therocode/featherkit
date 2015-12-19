#include <fea/rendering/quad.hpp>
#include <fea/assert.hpp>

namespace fea
{
    Quad::Quad() : Quad(glm::vec2(1.0f, 1.0f))
    {

    }

    Quad::Quad(const glm::vec2& size):
        mHFlip(1.0f),
        mVFlip(1.0f),
        mTexture(nullptr),
        mSize(size)
    {
        FEA_ASSERT(size.x > 0.0f && size.y > 0.0f, "Size of quads must be bigger than zero in all dimensions! " + std::to_string(size.x) + " " + std::to_string(size.y) + " provided.");
        float xnum = size.x;
        float ynum = size.y;

        mVertices = {0.0f, 0.0f, 
                     0.0f, ynum, 
                     xnum, 0.0f, 
                     xnum, 0.0f, 
                     0.0f, ynum, 
                     xnum, ynum};

        glm::vec2 texCoordsX = glm::vec2(0.0f, 1.0f);
        glm::vec2 texCoordsY = glm::vec2(0.0f, 1.0f);

        mTexCoords =  {texCoordsX[0], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[1]};

        mVertexColors = {1.0f, 1.0f, 1.0f, 1.0f,
                         1.0f, 1.0f, 1.0f, 1.0f,
                         1.0f, 1.0f, 1.0f, 1.0f,
                         1.0f, 1.0f, 1.0f, 1.0f,
                         1.0f, 1.0f, 1.0f, 1.0f,
                         1.0f, 1.0f, 1.0f, 1.0f};

        mDrawMode = GL_TRIANGLES;
        mConstraints = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

        mRenderInfo.front().mUniforms.emplace("texture", Uniform{TEXTURE, 0u});
    }
    
    void Quad::setSize(const glm::vec2& size)
    {
        FEA_ASSERT(size.x > 0.0f && size.y > 0.0f, "Size of quads must be bigger than zero in all dimensions! " + std::to_string(size.x) + " " + std::to_string(size.y) + " provided.");
        float xnum = size.x;
        float ynum = size.y;

        mVertices = {0.0f, 0.0f, 
                     0.0f, ynum, 
                     xnum, 0.0f, 
                     xnum, 0.0f, 
                     0.0f, ynum, 
                     xnum, ynum};

        mSize = size;

        mVerticesDirty = true;
    }

    const glm::vec2& Quad::getSize() const
    {
        return mSize;
    }
    
    void Quad::setTexture(const Texture& tex)
    {
        mTexture = &tex;
        mUniformsDirty = true;
    }

    const Texture& Quad::getTexture() const
    {
        return *mTexture;
    }

    void Quad::setHFlip(bool enabled)
    {
        if(enabled)
            mHFlip = -1.0f;
        else
            mHFlip = 1.0f;

        glm::vec2 texCoordsX = glm::vec2(0.0f, 1.0f) * mHFlip;
        glm::vec2 texCoordsY = glm::vec2(0.0f, 1.0f) * mVFlip;

        mTexCoords =  {texCoordsX[0], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[1]};
                      
        mVerticesDirty = true;
    }

    void Quad::setVFlip(bool enabled)
    {
        if(enabled)
            mVFlip = -1.0f;
        else
            mVFlip = 1.0f;

        glm::vec2 texCoordsX = glm::vec2(0.0f, 1.0f) * mHFlip;
        glm::vec2 texCoordsY = glm::vec2(0.0f, 1.0f) * mVFlip;

        mTexCoords =  {texCoordsX[0], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[1], texCoordsY[0],
                      texCoordsX[0], texCoordsY[1],
                      texCoordsX[1], texCoordsY[1]};

        mVerticesDirty = true;
    }
    
    void Quad::updateRenderInfo(std::vector<RenderEntity>& renderInfo, bool updateVertices, bool updateUniforms) const
    {
        Drawable2D::updateRenderInfo(renderInfo, updateVertices, updateUniforms);
        RenderEntity& renderEntity = renderInfo.front();

        renderEntity.mElementAmount = mVertices.size() / 2; //this could be worked out correctly from drawmode. it must now be set in the child

        if(mUniformsDirty)
        {
            if(mTexture != nullptr)
            {
                renderEntity.mUniforms.at("texture") = Uniform{TEXTURE, getTexture().getId()};
            }

            renderEntity.mUniforms.at("constraints") = Uniform{VEC4, mConstraints};
        }
    }
}
