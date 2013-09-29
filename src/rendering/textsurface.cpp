#include <featherkit/rendering/textsurface.h>
#include <featherkit/rendering/font.h>

namespace fea
{
    TextSurface::TextSurface()
    {
        atlas = texture_atlas_new(512, 512, 1);
    }

    TextSurface::~TextSurface()
    {
        texture_atlas_delete(atlas);
    }

    void TextSurface::write(const Text& text)
    {

    //void add_text( vertex_buffer_t * buffer, texture_font_t * font, wchar_t * text, vec4 * color, vec2 * pen )
        size_t i;
        //float r = color->red, g = color->green, b = color->blue, a = color->alpha;

        glm::vec2 pen;

        for(i = 0; i < text.text.size(); ++i )
        {
                texture_glyph_t *glyph = texture_font_get_glyph( text.font->getInternalFont(), text.text[i] );
                if( glyph != NULL )
                {
                int kerning = 0;
                if( i > 0)
                {
                    kerning = texture_glyph_get_kerning( glyph, text.text[i-1] );
                }
                pen.x += kerning;
                int x0  = (int)( pen.x + glyph->offset_x );
                int y0  = (int)( pen.y + glyph->offset_y );
                int x1  = (int)( x0 + glyph->width );
                int y1  = (int)( y0 - glyph->height );
                float s0 = glyph->s0;
                float t0 = glyph->t0;
                float s1 = glyph->s1;
                float t1 = glyph->t1;

                vertices.insert(vertices.end(), {x0, y0,
                                                 x0, y1,
                                                 x1, y1,
                                                 x0, y0,
                                                 x1, y1,
                                                 x1, y0});
                texCoords.insert(texCoords.end(), {s0, t0,
                                                   s0, t1,
                                                   s1, t1,
                                                   s0, t0,
                                                   s1, t1,
                                                   s1, t0});
                pen.x += glyph->advance_x;
            }
        }
    }
}
