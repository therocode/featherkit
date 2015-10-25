template <typename Drawable>
void Renderer2D::queue(const Drawable& drawable)
{
    for(const auto& renderEntity : drawable.getRenderInfo())
    {
        mRenderQueue.push_back(renderEntity);
        mRenderQueue.back().mBlendMode = mCurrentBlendMode;
    }
}
