namespace windbreeze
{
    struct RenderData
    {
    };

    class Renderer2DBackend
    {
        public:
            virtual void setup() = 0;
            virtual void destroy() = 0;
            virtual void clear() = 0;
            virtual void setViewRect(float x, float y, float w, float h) = 0;
            virtual void setViewTransform(glm::mat2x2 transform) = 0;
            virtual void render(RenderData renderData);
    };
}
