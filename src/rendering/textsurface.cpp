#include <fea/rendering/textsurface.hpp>
#include <fea/rendering/font.hpp>

std::wstring utf8_to_utf16(const std::string& utf8)
{
    std::vector<unsigned long> unicode;
    size_t i = 0;
    while (i < utf8.size())
    {
        unsigned long uni;
        size_t todo;
        bool error = false;
        unsigned char ch = utf8[i++];
        if (ch <= 0x7F)
        {
            uni = ch;
            todo = 0;
        }
        else if (ch <= 0xBF)
        {
            throw std::logic_error("not a UTF-8 string");
        }
        else if (ch <= 0xDF)
        {
            uni = ch&0x1F;
            todo = 1;
        }
        else if (ch <= 0xEF)
        {
            uni = ch&0x0F;
            todo = 2;
        }
        else if (ch <= 0xF7)
        {
            uni = ch&0x07;
            todo = 3;
        }
        else
        {
            throw std::logic_error("not a UTF-8 string");
        }
        for (size_t j = 0; j < todo; ++j)
        {
            if (i == utf8.size())
                throw std::logic_error("not a UTF-8 string");
            unsigned char ch = utf8[i++];
            if (ch < 0x80 || ch > 0xBF)
                throw std::logic_error("not a UTF-8 string");
            uni <<= 6;
            uni += ch & 0x3F;
        }
        if (uni >= 0xD800 && uni <= 0xDFFF)
            throw std::logic_error("not a UTF-8 string");
        if (uni > 0x10FFFF)
            throw std::logic_error("not a UTF-8 string");
        unicode.push_back(uni);
    }
    std::wstring utf16;
    for (size_t i = 0; i < unicode.size(); ++i)
    {
        unsigned long uni = unicode[i];
        if (uni <= 0xFFFF)
        {
            utf16 += (wchar_t)uni;
        }
        else
        {
            uni -= 0x10000;
            utf16 += (wchar_t)((uni >> 10) + 0xD800);
            utf16 += (wchar_t)((uni & 0x3FF) + 0xDC00);
        }
    }
    return utf16;
}

namespace fea
{
    TextSurface::Writing::Writing(const std::wstring& text, const Font* font, const glm::vec2& penPosition, const float scale, const Color& color)
        : mText(text), mFont(font), mPenPosition(penPosition), mScale(scale), mColor(color)
    {
    }
    
    TextSurface::TextSurface() : mScale(1.0f)
    {
        mAtlasSize = 64;
        mAtlas = texture_atlas_new(mAtlasSize, mAtlasSize, 1);
        mDrawMode = GL_TRIANGLES;
        mCurrentFont = nullptr;
    }

    TextSurface::~TextSurface()
    {
        if(mAtlas)
            texture_atlas_delete(mAtlas);
    }

    TextSurface::TextSurface(TextSurface&& other)
    {
        mAtlas = other.mAtlas;
        mCurrentFont = other.mCurrentFont;
        mPenPosition = other.mPenPosition;
        mScale = other.mScale;
        mColor = other.mColor;
        mHorizontalAlign = other.mHorizontalAlign;
        mAtlasSize = other.mAtlasSize;

        mFontCache = std::move(other.mFontCache);
        mWritings = std::move(other.mWritings);

        mLowBounds = other.mLowBounds;
        mHighBounds = other.mHighBounds;
        
        other.mAtlas = nullptr;
    }
    
    TextSurface& TextSurface::operator=(TextSurface&& other)
    {
        mAtlas = other.mAtlas;
        mCurrentFont = other.mCurrentFont;
        mPenPosition = other.mPenPosition;
        mScale = other.mScale;
        mColor = other.mColor;
        mHorizontalAlign = other.mHorizontalAlign;
        mAtlasSize = other.mAtlasSize;

        mFontCache = std::move(other.mFontCache);
        mWritings = std::move(other.mWritings);

        mLowBounds = other.mLowBounds;
        mHighBounds = other.mHighBounds;
        
        other.mAtlas = nullptr;

        return *this;
    }

    void TextSurface::write(const std::string& text)
    {
        //write(std::wstring(text.begin(), text.end()));
        write(utf8_to_utf16(text));
    }

    void TextSurface::write(const std::wstring& text)
    {
        mWritings.push_back(Writing(text, mCurrentFont, mPenPosition, mScale, mColor));
        addText(text);
    }
            
    void TextSurface::setPenFont(const Font& font)
    {
        cacheFont(font);
        mCurrentFont = &font;
    }

    void TextSurface::setPenPosition(const glm::vec2 position)
    {
        mPenPosition = position;
    }
    
    void TextSurface::setPenScale(const float scale)
    {
        mScale = scale;
    }
    
    void TextSurface::setPenColor(const Color& color)
    {
        mColor = color;
    }
    
    void TextSurface::setHorizontalAlign(const float coord)
    {
        mHorizontalAlign = coord;
    }

    void TextSurface::newLine(const float distance, const float indentation)
    {
        mPenPosition.x = mHorizontalAlign + indentation * mScale;
        mPenPosition.y += distance * mScale;
    }

    RenderInfo TextSurface::getRenderInfo() const
    {
        RenderInfo temp = Drawable2D::getRenderInfo();

        temp.mUniforms.push_back(Uniform("texture", TEXTURE, mAtlas->id));
        return temp;
    }
    
    void TextSurface::rewrite()
    {
        mVertices.clear();
        mTexCoords.clear();
        mVertexColors.clear();

        const glm::vec2 originalPosition = mPenPosition;
        const Font* originalFont = mCurrentFont;
        const float originalScale = mScale;
        const Color originalColor = mColor;

        for(auto& writing : mWritings)
        {
            mPenPosition = writing.mPenPosition;
            mCurrentFont = writing.mFont;
            cacheFont(*mCurrentFont);
            mScale = writing.mScale;
            mColor = writing.mColor;
            addText(writing.mText);
        }

        mPenPosition = originalPosition;
        mCurrentFont = originalFont;
        mScale = originalScale;
        mColor = originalColor;
    }

    void TextSurface::clear()
    {
        mVertices.clear();
        mTexCoords.clear();
        mVertexColors.clear();

        mWritings.clear();

        mLowBounds = glm::vec2();
        mHighBounds = glm::vec2();
    }
        
    glm::vec2 TextSurface::getSize()
    {
        return glm::vec2(mHighBounds.x - mLowBounds.x, mHighBounds.y - mLowBounds.y);
    }
            
    void TextSurface::addText(const std::wstring& text)
    {
        //void add_text( vertex_buffer_t * buffer, texture_font_t * font, wchar_t * text, vec4 * color, vec2 * pen )
        size_t i;
        //float r = color->red, g = color->green, b = color->blue, a = color->alpha;

        std::vector<float> verticesToAdd;
        std::vector<float> texCoordsToAdd;
        std::vector<float> colorsToAdd;
        glm::vec2 penTempPosition = mPenPosition;

        for(i = 0; i < text.size(); ++i )
        {
            texture_glyph_t* glyph = texture_font_get_glyph( mFontCache.at(*mCurrentFont), text[i] );

            if(glyph == nullptr)
            {
                mAtlasSize *= 2;
                texture_atlas_delete(mAtlas);
                mAtlas = texture_atlas_new(mAtlasSize, mAtlasSize, 1);

                for(auto font : mFontCache)
                {
                    texture_font_delete(font.second);
                }
                mFontCache.clear();

                rewrite();
                //addText(text); //don't think this is needed :D
                return;
            }

            float kerning = 0.0f;
            if( i > 0)
            {
                kerning = texture_glyph_get_kerning( glyph, text[i-1] );
            }
            penTempPosition.x += kerning * mScale;
            float x0  = ( penTempPosition.x + glyph->offset_x * mScale );
            float y0  = ( penTempPosition.y - glyph->offset_y * mScale);
            float x1  = ( x0 + glyph->width * mScale );
            float y1  = ( y0 + glyph->height * mScale);
            float s0 = glyph->s0;
            float t0 = glyph->t0;
            float s1 = glyph->s1;
            float t1 = glyph->t1;

            if(mLowBounds.x == mHighBounds.x)
            {
                 mLowBounds.x = x0;
                 mHighBounds.x = x1;
                 mLowBounds.y = y0;
                 mHighBounds.y = y1;
            }

            if(x0 < mLowBounds.x)
                mLowBounds.x = x0;
            if(x1 > mHighBounds.x)
                mHighBounds.x = x1;
            if(y0 < mLowBounds.y)
                mLowBounds.y = y0;
            if(y1 > mHighBounds.y)
                mHighBounds.y = y1;

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
            colorsToAdd.insert(colorsToAdd.end(), {mColor.r(), mColor.g(), mColor.b(), 1.0f,
                                mColor.r(), mColor.g(), mColor.b(), 1.0f,
                                mColor.r(), mColor.g(), mColor.b(), 1.0f,
                                mColor.r(), mColor.g(), mColor.b(), 1.0f,
                                mColor.r(), mColor.g(), mColor.b(), 1.0f,
                                mColor.r(), mColor.g(), mColor.b(), 1.0f});
            penTempPosition.x += glyph->advance_x * mScale;
        }

        mPenPosition = penTempPosition;
        mVertices.insert(mVertices.end(), verticesToAdd.begin(), verticesToAdd.end());
        mTexCoords.insert(mTexCoords.end(), texCoordsToAdd.begin(), texCoordsToAdd.end());
        mVertexColors.insert(mVertexColors.end(), colorsToAdd.begin(), colorsToAdd.end());
    }


    void TextSurface::cacheFont(const Font& font)
    {
        if(mFontCache.find(font) == mFontCache.end())
        {
            texture_font_t* created = texture_font_new(mAtlas, font.getPath().c_str(), font.getSize());
            if(created == nullptr)
            {
                throw std::logic_error("Error! Could not create font from file '" + font.getPath() + "' maybe the file does not exist?");
            }
            else
                mFontCache.emplace(font, created);
        }
    }
}
