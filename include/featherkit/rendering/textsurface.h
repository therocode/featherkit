#pragma once
#include <featherkit/freetype-gl/texture-atlas.h>
#include <featherkit/freetype-gl/texture-font.h>
#include <featherkit/rendering/drawable2d.h>
#include <featherkit/rendering/text.h>
#include <featherkit/rendering/font.h>
#include <unordered_map>

namespace fea
{

    class TextSurface : public Drawable2D
    {
        struct Writing
        {
            Writing(const std::wstring& t, const Font* f, const glm::vec2& p, const float s, const Colour& c);//
            const std::wstring text;
            const Font* font;
            const glm::vec2 penPosition;
            const float scale;
            const Colour colour;
        };

    public:
        TextSurface();
        ~TextSurface();
        void write(const std::string& text);
        void write(const std::wstring& text);
        void setPenFont(const Font& font);
        void setPenPosition(const glm::vec2 pos);
        void setPenScale(const float s);
        void setPenColour(const Colour& col);
        void setHorizontalAlign(const float coord);
        void newLine(const float distance, const float indentation = 0.0f);
        virtual RenderInfo getRenderInfo() const override;
        void clear();
    private:
        void rewrite();
        void addText(const std::wstring& text);
        void cacheFont(const Font& font);
        texture_atlas_t* atlas;
        const Font* currentFont;
        glm::vec2 pen;
        float scale;
        Colour colour;
        float horizontalAlign;
        uint32_t atlasSize;

        std::unordered_map<Font, texture_font_t*> fontCache;
        std::vector<Writing> writings;
    };
    /** @addtogroup Render2D
     *@{
     *  @class TextSurface
     *@}
     ***
     *  @class TextSurface
     *  @brief A drawable for text.
     *
     *  This drawable is similar to a piece of paper. Text can be written on it using the TextSurface::write method. All added text is appended to the current pen position and the pen position is advanced accordingly. The pen itself has states defining its colour, current font, and scale. When these attributes are set, all text written with the pen will be affected.
     *
     ***
     *  @fn void TextSurface::write(const std::string& text)
     *  @brief Write text at the current pen position.
     *
     *  The position of the pen is moved forward accordingly. The pen's current state determines the scale, font and colour of the text.
     *  @param text Text to write.
     ***
     *  @fn void TextSurface::write(const std::wstring& text)
     *  @brief Write text at the current pen position.
     *
     *  The position of the pen is moved forward accordingly. The pen's current state determines the scale, font and colour of the text.
     *  @param text Text to write.
     ***
     *  @fn void TextSurface::setPenFont(const Font& font)
     *  @brief Change the current font of the pen.
     *
     *  If the text is too grainy or has a lot of artifacts, try increasing the size of the font.
     *  @param font Font to use.
     ***
     *  @fn void TextSurface::setPenPosition(const glm::vec2 pos)
     *  @brief Set the current pen position.
     *  @param pos New position.
     ***
     *  @fn void TextSurface::setPenScale(const float s)
     *  @brief Set the current pen scale.
     *
     *  Scaling can make text appear grainy. If a higher resolution of the text is needed, increase the size of the font.
     *  @param s New scale.
     ***
     *  @fn void TextSurface::setPenColour(const Colour& col)
     *  @brief Set the current pen colour.
     *  @param col New colour.
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
