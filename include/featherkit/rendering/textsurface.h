#pragma once
#include <texture-atlas.h>

namespace fea
{
    class TextSurface
    {
        public:
            TextSurface();
            ~TextSurface();
        private:
            texture_atlas_t* atlas;
            friend class Font;
    };
}
