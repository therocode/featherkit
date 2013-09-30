#pragma once
#include <texture-atlas.h>
#include <featherkit/rendering/drawable2d.h>
#include <featherkit/rendering/text.h>

namespace fea
{
    class TextSurface : public Drawable2D
    {
        public:
            TextSurface();
            ~TextSurface();
            void write(const Text& text);
            void setPenPosition(const glm::vec2 pos);
            void setHorizontalAlign(const float coord);
            void newLine(const float distance);
            virtual RenderInfo getRenderInfo() const override;
        private:
            texture_atlas_t* atlas;
            friend class Font;
            glm::vec2 pen;
            float horizontalAlign;
    };
}
