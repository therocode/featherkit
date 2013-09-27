#include <featherkit/rendering/textsurface.h>

namespace fea
{
    TextSurface::TextSurface()
    {
        atlas = texture_atlas_new( 512, 512, 1 );
    }

    TextSurface::~TextSurface()
    {
        texture_atlas_delete(atlas);
    }
}
