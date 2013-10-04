#include <featherkit/rendering/textsurface.h>
#include <featherkit/rendering/font.h>
#include <iostream>

namespace fea
{
    Writing::Writing(const std::wstring& t, const Font* f, const glm::vec2& p, const float s) : text(t), font(f), penPosition(p), scale(s)
    {
    }
    
    TextSurface::TextSurface() : scale(1.0f)
    {
        atlasSize = 64;
        atlas = texture_atlas_new(atlasSize, atlasSize, 1);
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
        writings.push_back(Writing(text, currentFont, pen, scale));
        addText(text);
    }
            
    void TextSurface::setPenFont(const Font& font)
    {
        cacheFont(font);
        currentFont = &font;
    }

    void TextSurface::setPenPosition(const glm::vec2 pos)
    {
        pen = pos;
    }
    
    void TextSurface::setPenScale(const float s)
    {
        scale = s;
    }
    
    void TextSurface::setHorizontalAlign(const float coord)
    {
        horizontalAlign = coord;
    }

    void TextSurface::newLine(const float distance, const float indentation)
    {
        pen.x = horizontalAlign + indentation * scale;
        pen.y += distance * scale;
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
        const float originalScale = scale;

        for(auto& writing : writings)
        {
            pen = writing.penPosition;
            currentFont = writing.font;
            cacheFont(*currentFont);
            scale = writing.scale;
            addText(writing.text);
        }

        pen = originalPosition;
        currentFont = originalFont;
        scale = originalScale;
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

        std::vector<float> verticesToAdd;
        std::vector<float> texCoordsToAdd;
        glm::vec2 penTempPosition = pen;


        for(i = 0; i < text.size(); ++i )
        {
            texture_glyph_t* glyph = texture_font_get_glyph( fontCache.at(*currentFont), text[i] );

            if(glyph == nullptr)
            {
                atlasSize *= 2;
                texture_atlas_delete(atlas);
                atlas = texture_atlas_new(atlasSize, atlasSize, 1);

                for(auto font : fontCache)
                {
                    texture_font_delete(font.second);
                }
                fontCache.clear();

                rewrite();
                addText(text);
                return;
            }

            float kerning = 0.0f;
            if( i > 0)
            {
                kerning = texture_glyph_get_kerning( glyph, text[i-1] );
            }
            penTempPosition.x += kerning * scale;
            std::cout << "kerning was " << kerning << "\n";
            float x0  = ( penTempPosition.x + glyph->offset_x * scale );
            float y0  = ( penTempPosition.y - glyph->offset_y * scale);
            float x1  = ( x0 + glyph->width * scale );
            float y1  = ( y0 + glyph->height * scale);
            float s0 = glyph->s0;
            float t0 = glyph->t0;
            float s1 = glyph->s1;
            float t1 = glyph->t1;

            verticesToAdd.insert(verticesToAdd.end(), {x0, y0,
                    x0, y1,
                    x1, y1,
                    x0, y0,
                    x1, y1,
                    x1, y0});
            texCoordsToAdd.insert(texCoordsToAdd.end(), {s0, t0,
                    s0, t1,
                    s1, t1,
                    s0, t0,
                    s1, t1,
                    s1, t0});
            penTempPosition.x += glyph->advance_x * scale;
        }

        pen = penTempPosition;
        vertices.insert(vertices.end(), verticesToAdd.begin(), verticesToAdd.end());
        texCoords.insert(texCoords.end(), texCoordsToAdd.begin(), texCoordsToAdd.end());
    }


    void TextSurface::cacheFont(const Font& font)
    {
        if(fontCache.find(font) == fontCache.end())
        {
            texture_font_t* created = texture_font_new(atlas, font.getPath().c_str(), font.getSize());
            fontCache.emplace(font, created);
        }
    }
}
