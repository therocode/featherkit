#pragma once
#include <featherkit/freetype-gl/texture-atlas.h>
#include <featherkit/freetype-gl/texture-font.h>
#include <featherkit/rendering/drawable2d.h>
#include <featherkit/rendering/font.h>
#include <unordered_map>

namespace fea
{

    class TextSurface : public Drawable2D
    {
        struct Writing
        {
            Writing(const std::u32string& text, const Font* font, const glm::vec2& penPosition, const float scale, const Color& color);//
            const std::u32string mText;
            const Font* mFont;
            const glm::vec2 mPenPosition;
            const float mScale;
            const Color mColor;
        };

    public:
        TextSurface();
        ~TextSurface();
        void write(const std::string& text);
        void write(const std::u32string& text);
        void setPenFont(const Font& font);
        void setPenPosition(const glm::vec2 position);
        void setPenScale(const float scale);
        void setPenColor(const Color& color);
        void setHorizontalAlign(const float coord);
        void newLine(const float distance, const float indentation = 0.0f);
        virtual RenderInfo getRenderInfo() const override;
        void clear();
    private:
        void rewrite();
        void addText(const std::u32string& text);
        void cacheFont(const Font& font);
        texture_atlas_t* mAtlas;
        const Font* mCurrentFont;
        glm::vec2 mPenPosition;
        float mScale;
        Color mColor;
        float mHorizontalAlign;
        uint32_t mAtlasSize;

        std::unordered_map<Font, texture_font_t*> mFontCache;
        std::vector<Writing> mWritings;
    };
    /** @addtogroup Render2D
     *@{
     *  @class TextSurface
     *@}
     ***
     *  @class TextSurface
     *  @brief A drawable for text.
     *
     *  This drawable is similar to a piece of paper. Text can be written on it using the TextSurface::write method. All added text is appended to the current pen position and the pen position is advanced accordingly. The pen itself has states defining its color, current font, and scale. When these attributes are set, all text written with the pen will be affected.
     *
     ***
     *  @fn void TextSurface::write(const std::string& text)
     *  @brief Write text at the current pen position.
     *
     *  The position of the pen is moved forward accordingly. The pen's current state determines the scale, font and color of the text.
     *  @param text Text to write.
     ***
     *  @fn void TextSurface::write(const std::u32string& text)
     *  @brief Write text at the current pen position.
     *
     *  The position of the pen is moved forward accordingly. The pen's current state determines the scale, font and color of the text.
     *  @param text Text to write.
     ***
     *  @fn void TextSurface::setPenFont(const Font& font)
     *  @brief Change the current font of the pen.
     *
     *  If the text is too grainy or has a lot of artifacts, try increasing the size of the font.
     *  @param font Font to use.
     ***
     *  @fn void TextSurface::setPenPosition(const glm::vec2 position)
     *  @brief Set the current pen position.
     *  @param position New position.
     ***
     *  @fn void TextSurface::setPenScale(const float scale)
     *  @brief Set the current pen scale.
     *
     *  Scaling can make text appear grainy. If a higher resolution of the text is needed, increase the size of the font.
     *  @param scale New scale.
     ***
     *  @fn void TextSurface::setPenColor(const Color& color)
     *  @brief Set the current pen color.
     *  @param color New color.
     ***
     *  @fn void TextSurface::setHorizontalAlign(const float coord)
     *  @brief Set the horizontal alignment for new text lines.
     *
     *  When a new line is issued using the TextSurface::newLine method, the pen is moved down under the current line, aligned to this value on the X axis.
     *  @param coord X coordinate to align to.
     ***
     *  @fn void TextSurface::newLine(const float distance, const float indentation = 0.0f)
     *  @brief Move the pen to a new line.
     *
     *  The pen is moved downwards with the amount given by the distance parameter. The X position of the pen will be set to the horizontal alignment given by TextSurface::setHorizontalAlign.
     *  @param distance Distance to move downwards. Can be negative.
     *  @param indentation Optional indentation to deviate from the horizontal alignment.
     ***
     *  @fn void TextSurface::clear()
     *  @brief Clear all text written on the text area.
     ***/
}
