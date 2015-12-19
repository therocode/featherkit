template <typename Drawable>
void Renderer2D::render(const Drawable& drawable)
{
    render(drawable, mDefaultShader);
}

template <typename Drawable>
void Renderer2D::render(const Drawable& drawable, const RenderTarget& target)
{
    render(drawable, target, mDefaultShader);
}

template <typename Drawable>
void Renderer2D::render(const Drawable& drawable, const Shader& shader)
{
    shader.activate();

    //can be cached
    shader.setUniform("camPosition", Uniform(VEC2, mCurrentViewport.getCamera().getPosition()));
    shader.setUniform("camZoom", Uniform(VEC2, mCurrentViewport.getCamera().getZoom()));
    glm::mat2x2 camRot = mCurrentViewport.getCamera().getRotationMatrix();
    shader.setUniform("camRotation", Uniform(MAT2X2, camRot));
    glm::vec2 halfViewSize = glm::vec2((float)mCurrentViewport.getSize().x / 2.0f, (float)mCurrentViewport.getSize().y / 2.0f);
    shader.setUniform("halfViewSize", Uniform(VEC2, halfViewSize));
    shader.setUniform("projection", Uniform(MAT4X4, mProjection));

    GLuint defaultTextureId = mDefaultTexture.getId();

    for(const auto& renderOperation : drawable.getRenderInfo())
    {
        shader.setUniform("texture", Uniform(TEXTURE, defaultTextureId)); //may be overriden
        setBlendModeGl(mCurrentBlendMode); //can be cached

        for(const auto& uniformIter : renderOperation.mUniforms)
        {
            shader.setUniform(uniformIter.first, uniformIter.second);
        }
        
        for(const auto& vertexAttributeIter : renderOperation.mVertexAttributes)
        {
            shader.setVertexAttribute(vertexAttributeIter.first, vertexAttributeIter.second.mAttributeFloatAmount, vertexAttributeIter.second.mData.data());
        }

        glDrawArrays(renderOperation.mDrawMode, 0, renderOperation.mElementAmount);
    }

    setBlendMode(ALPHA);  //needed?
    shader.deactivate();
}

template <typename Drawable>
void Renderer2D::render(const Drawable& drawable, const RenderTarget& target, const Shader& shader)
{
    glBindFramebuffer(GL_FRAMEBUFFER, target.getId());
    render(drawable, shader);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
