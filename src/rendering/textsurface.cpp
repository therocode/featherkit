#include <featherkit/rendering/textsurface.h>
#include <featherkit/rendering/font.h>
#include <iostream>

namespace fea
{
    Writing::Writing(const std::wstring& t, const Font* f, const glm::vec2& p) : text(t), font(f), penPosition(p)
    {
    }
    
    TextSurface::TextSurface()
    {
        atlas = texture_atlas_new(512, 512, 1);
        drawMode = GL_TRIANGLES;
        currentFont = nullptr;
    }

    TextSurface::~TextSurface()
    {
        texture_atlas_delete(atlas);
    }

    void TextSurface::write(const std::string& text)
    {
        write(std::wstring(text.begin(), text.end()));
    }

    void TextSurface::write(const std::wstring& text)
    {
        writings.push_back(Writing(text, currentFont, pen));
        addText(text);
    }
            
    void TextSurface::setPenFont(const Font& font)
    {
        if(fontCache.find(font) == fontCache.end())
        {
            texture_font_t* created = texture_font_new(atlas, font.getPath().c_str(), font.getSize());
            fontCache.emplace(font, created);
        }
        currentFont = &font;
    }

    void TextSurface::setPenPosition(const glm::vec2 pos)
    {
        pen = pos;
    }
    
    void TextSurface::setHorizontalAlign(const float coord)
    {
        horizontalAlign = coord;
    }

    void TextSurface::newLine(const float distance, const float indentation)
    {
        pen.x = horizontalAlign + indentation;
        pen.y += distance;
    }

    RenderInfo TextSurface::getRenderInfo() const
    {
        RenderInfo temp = Drawable2D::getRenderInfo();
        std::hash<std::string> stringHasher;

        temp.uniforms.push_back(Uniform(stringHasher("texture"), TEXTURE, atlas->id));
        std::cout << "added the special surface texture with id " << atlas->id << "\n";
        return temp;
    }
    
    void TextSurface::rewrite()
    {
        clear();

        const glm::vec2 originalPosition = pen;
        const Font* originalFont = currentFont;

        for(auto& writing : writings)
        {
            pen = writing.penPosition;
            currentFont = writing.font;
            addText(writing.text);
        }

        pen = originalPosition;
        currentFont = originalFont;
    }

    void TextSurface::clear()
    {
        vertices.clear();
        texCoords.clear();
    }
            
    void TextSurface::addText(const std::wstring& text)
    {
        //void add_text( vertex_buffer_t * buffer, texture_font_t * font, wchar_t * text, vec4 * color, vec2 * pen )
        size_t i;
        //float r = color->red, g = color->green, b = color->blue, a = color->alpha;


        for(i = 0; i < text.size(); ++i )
        {
            texture_glyph_t* glyph = texture_font_get_glyph( fontCache.at(*currentFont), text[i] );

            if(glyph == nullptr)
            {
                //resize, empty font cache, redo writing, return; but hmmm the problem is that the pen won't be moved if you return
            }

            int kerning = 0;
            if( i > 0)
            {
                kerning = texture_glyph_get_kerning( glyph, text[i-1] );
            }
            pen.x += kerning;
            int x0  = (int)( pen.x + glyph->offset_x );
            int y0  = (int)( pen.y - glyph->offset_y );
            int x1  = (int)( x0 + glyph->width );
            int y1  = (int)( y0 + glyph->height );
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
