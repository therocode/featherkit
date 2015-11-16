template <typename Drawable>
void Renderer2D::queue(const Drawable& drawable)
{
    for(auto& renderEntity : drawable.getRenderInfo())
    {
        mRenderQueue.push_back(std::move(renderEntity));
        mRenderQueue.back().mBlendMode = mCurrentBlendMode;
    }
}
