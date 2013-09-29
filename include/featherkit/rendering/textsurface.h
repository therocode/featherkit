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
        private:
            texture_atlas_t* atlas;
            friend class Font;
    };
}
